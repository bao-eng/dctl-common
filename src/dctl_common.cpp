#include "dctl_common.h"

float Vec2Distance(const Vec2 &v1, const Vec2 &v2) {
  float result =
      std::sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
  return result;
}

Dir NewDir(const Dir &cur_dir, const Input &inp) {
  if (((cur_dir == kUp) || (cur_dir == kDown)) && (inp.left != inp.right)) {
    if (inp.left) return kLeft;
    if (inp.right) return kRight;
  }
  if (((cur_dir == kLeft) || (cur_dir == kRight)) && (inp.up != inp.down)) {
    if (inp.up) return kUp;
    if (inp.down) return kDown;
  }
  return cur_dir;
}

Vec2 NewPos(Dir dir, float dist, Vec2 cur_pos) {
  switch (dir) {
    case kUp:
      return {cur_pos.x, cur_pos.y - dist};
      break;
    case kDown:
      return {cur_pos.x, cur_pos.y + dist};
      break;
    case kLeft:
      return {cur_pos.x - dist, cur_pos.y};
      break;
    case kRight:
      return {cur_pos.x + dist, cur_pos.y};
      break;
  }
  return cur_pos;
}

State NextState(const State &st, const std::unordered_map<int, Input> &inp,
                double dt, float speed, size_t max_length) {
  State ns;
  ns.sequence = st.sequence + 1;
  for (auto &i : st.snakes) {
    auto tmp = i;
    if (inp.find(i.player_id) != inp.end()) {
      auto newDir = NewDir(i.dir, inp.at(i.player_id));
      if (newDir != i.dir) {
        tmp.dir = newDir;
        tmp.tail.push_back(tmp.tail.back());
        if (tmp.tail.size() > max_length) {
          tmp.tail.pop_front();
        }
      }
    }
    tmp.tail.back() = NewPos(tmp.dir, dt * speed, tmp.tail.back());
    ns.snakes.push_back(tmp);
  }
  return ns;
}

// https://stackoverflow.com/a/14177062
bool IsIntersecting(const Vec2 &p1, const Vec2 &p2, const Vec2 &q1,
                    const Vec2 &q2) {
  return (((q1.x - p1.x) * (p2.y - p1.y) - (q1.y - p1.y) * (p2.x - p1.x)) *
              ((q2.x - p1.x) * (p2.y - p1.y) - (q2.y - p1.y) * (p2.x - p1.x)) <
          0) &&
         (((p1.x - q1.x) * (q2.y - q1.y) - (p1.y - q1.y) * (q2.x - q1.x)) *
              ((p2.x - q1.x) * (q2.y - q1.y) - (p2.y - q1.y) * (q2.x - q1.x)) <
          0);
}

Vec2 IntersectionPoint(const Vec2 &p1, const Vec2 &p2, const Vec2 &q1,
                       const Vec2 &q2) {
  Vec2 result;
  if ((p1.x == p2.x) && (q1.y == q2.y)) {
    result.x = p1.x;
    result.y = q1.y;
  } else if ((q1.x == q2.x) && (p1.y == p2.y)) {
    result.x = q1.x;
    result.y = p1.y;
  } else {
    throw std::invalid_argument("");
  }
  return result;
}

bool IsCrossing(const Snake &snake1, const Snake &snake2) {
  auto head1 = snake1.tail.rbegin();
  auto neck1 = snake1.tail.rbegin() + 1;
  if (IsIntersecting(*head1, *neck1, *snake2.tail.rbegin(),
                     *(snake2.tail.rbegin() + 1))) {
    auto p = IntersectionPoint(*head1, *neck1, *snake2.tail.rbegin(),
                               *(snake2.tail.rbegin() + 1));
    if (Vec2Distance(*head1, p) < Vec2Distance(*snake2.tail.rbegin(), p)) {
      return true;
    }
  } else if (snake2.tail.size() > 2) {
    for (auto it = snake2.tail.rbegin() + 2; it != snake2.tail.rend(); it++) {
      if (IsIntersecting(*head1, *neck1, *it, *(it - 1))) {
        return true;
      }
    }
  }
  return false;
}

State CheckCollisions(const State &st) {
  State ns;
  ns.sequence = st.sequence;
  auto valid = GetPlayers(st);
  for (auto &i : st.snakes) {
    for (auto &j : st.snakes) {
      if (IsCrossing(i, j)) {
        valid.erase(i.player_id);
      }
    }
  }
  for (auto &i : st.snakes) {
    if (valid.find(i.player_id) != valid.end()) {
      ns.snakes.push_back(i);
    }
  }
  return ns;
}

State CheckBounds(const State &st, float map_width, float map_height) {
  State ns;
  ns.sequence = st.sequence;
  for (auto &i : st.snakes) {
    if ((i.tail.back().x > 0) && (i.tail.back().x < map_width) &&
        (i.tail.back().y > 0) && (i.tail.back().y < map_height)) {
      ns.snakes.push_back(i);
    }
  }
  return ns;
}

std::unordered_set<int> GetPlayers(const State &st) {
  std::unordered_set<int> result;
  for (auto &i : st.snakes) {
    result.insert(i.player_id);
  }
  return result;
}

std::vector<char> PackInput(const Input &inp) {
  flatbuffers::FlatBufferBuilder builder;
  auto input =
      dctl::flat_input::CreateInput(builder, inp.sequence, inp.player_id,
                                    inp.left, inp.right, inp.up, inp.down);
  builder.Finish(input);
  std::vector<char> result(builder.GetBufferPointer(),
                           builder.GetBufferPointer() + builder.GetSize());
  return result;
}

Input UnpackInput(const std::vector<char> &buf) {
  Input result;
  auto input = dctl::flat_input::GetInput(buf.data());
  result.sequence = input->sequence();
  result.player_id = input->player_id();
  result.left = input->left();
  result.right = input->right();
  result.up = input->up();
  result.down = input->down();
  return result;
}

std::vector<char> PackState(const State &st) {
  flatbuffers::FlatBufferBuilder builder;
  std::vector<flatbuffers::Offset<dctl::flat_state::Snake>> snakes_vector;

  for (auto &s : st.snakes) {
    std::vector<dctl::flat_state::Vec2> tail_vector;
    for (auto &i : s.tail) {
      dctl::flat_state::Vec2 point{i.x, i.y};
      tail_vector.emplace_back(point);
    }
    auto tail = builder.CreateVectorOfStructs(tail_vector);

    dctl::flat_state::Dir dir;
    switch (s.dir) {
      case kUp:
        dir = dctl::flat_state::Dir_Up;
        break;
      case kDown:
        dir = dctl::flat_state::Dir_Down;
        break;
      case kLeft:
        dir = dctl::flat_state::Dir_Left;
        break;
      case kRight:
        dir = dctl::flat_state::Dir_Right;
        break;
      default:
        break;
    }

    dctl::flat_state::Color colorF{s.color.r, s.color.g, s.color.b};

    auto snakeBuf =
        dctl::flat_state::CreateSnake(builder, s.player_id, tail, dir, &colorF);
    snakes_vector.push_back(snakeBuf);
  }

  auto snakesBuf = builder.CreateVector(snakes_vector);

  auto state = dctl::flat_state::CreateState(builder, st.sequence, snakesBuf);

  builder.Finish(state);

  std::vector<char> result(builder.GetSize());
  std::vector<char> serialized(builder.GetBufferPointer(),
                               builder.GetBufferPointer() + builder.GetSize());

  memcpy(result.data(), builder.GetBufferPointer(), result.size());
  return result;
};

State UnpackState(const std::vector<char> &buf) {
  State result;
  auto state = dctl::flat_state::GetState(buf.data());
  auto snakesVec = state->snakes();
  result.sequence = state->sequence();
  for (unsigned int i = 0; i < snakesVec->size(); i++) {
    Snake tmp;
    tmp.player_id = snakesVec->Get(i)->player_id();
    auto color = snakesVec->Get(i)->color();
    tmp.color = {color->r(), color->g(), color->b(), 255};
    Dir dir;
    switch (snakesVec->Get(i)->dir()) {
      case dctl::flat_state::Dir_Up:
        dir = kUp;
        break;
      case dctl::flat_state::Dir_Down:
        dir = kDown;
        break;
      case dctl::flat_state::Dir_Left:
        dir = kLeft;
        break;
      case dctl::flat_state::Dir_Right:
        dir = kRight;
        break;
      default:
        break;
    }
    tmp.dir = dir;
    for (unsigned int j = 0; j < snakesVec->Get(i)->tail()->size(); j++) {
      tmp.tail.push_back({snakesVec->Get(i)->tail()->Get(j)->x(),
                          snakesVec->Get(i)->tail()->Get(j)->y()});
    }
    result.snakes.push_back(tmp);
  }
  return result;
};
