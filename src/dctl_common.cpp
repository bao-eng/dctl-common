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

std::vector<char> PackInputPack(const InputPack &inpp) {
  flatbuffers::FlatBufferBuilder builder;
  std::vector<dctl::flat_msg::Input> input_vector;
  for (auto i : inpp.vec) {
    input_vector.emplace_back(i.sequence, i.player_id, i.left, i.right, i.up,
                              i.down);
  }
  auto inputs = builder.CreateVectorOfStructs(input_vector);
  auto input_pack = dctl::flat_msg::CreateInputPack(builder, inputs);
  auto msg = dctl::flat_msg::CreateMessage(
      builder, dctl::flat_msg::Any_InputPack, input_pack.Union());

  builder.Finish(msg);
  std::vector<char> serialized(builder.GetBufferPointer(),
                               builder.GetBufferPointer() + builder.GetSize());
  return serialized;
}

InputPack UnpackInputPack(const dctl::flat_msg::InputPack *inpp_flat) {
  InputPack inpp;
  auto inputs_vec = inpp_flat->inputs();
  for (unsigned int i = 0; i < inputs_vec->size(); i++) {
    inpp.vec.emplace_back(
        inputs_vec->Get(i)->sequence(), inputs_vec->Get(i)->player_id(),
        inputs_vec->Get(i)->left(), inputs_vec->Get(i)->right(),
        inputs_vec->Get(i)->up(), inputs_vec->Get(i)->down());
  }
  return inpp;
}

std::vector<char> PackState(const State &st) {
  flatbuffers::FlatBufferBuilder builder;
  std::vector<flatbuffers::Offset<dctl::flat_msg::Snake>> snakes_vector;

  for (auto &s : st.snakes) {
    std::vector<dctl::flat_msg::Vec2> tail_vector;
    for (auto &i : s.tail) {
      tail_vector.emplace_back(i.x, i.y);
    }
    auto tail = builder.CreateVectorOfStructs(tail_vector);

    dctl::flat_msg::Dir dir;
    switch (s.dir) {
      case kUp:
        dir = dctl::flat_msg::Dir_Up;
        break;
      case kDown:
        dir = dctl::flat_msg::Dir_Down;
        break;
      case kLeft:
        dir = dctl::flat_msg::Dir_Left;
        break;
      case kRight:
        dir = dctl::flat_msg::Dir_Right;
        break;
      default:
        break;
    }

    dctl::flat_msg::Color colorF{s.color.r, s.color.g, s.color.b};

    auto snake_buf =
        dctl::flat_msg::CreateSnake(builder, s.player_id, tail, dir, &colorF);
    snakes_vector.push_back(snake_buf);
  }

  auto snakes_buf = builder.CreateVector(snakes_vector);

  auto state = dctl::flat_msg::CreateState(builder, st.sequence, snakes_buf);

  auto msg = dctl::flat_msg::CreateMessage(builder, dctl::flat_msg::Any_State,
                                           state.Union());

  builder.Finish(msg);

  std::vector<char> serialized(builder.GetBufferPointer(),
                               builder.GetBufferPointer() + builder.GetSize());
  return serialized;
};

State UnpackState(const dctl::flat_msg::State *state_flat) {
  State state;
  auto snakes_vec = state_flat->snakes();
  state.sequence = state_flat->sequence();
  for (unsigned int i = 0; i < snakes_vec->size(); i++) {
    Snake snake;
    snake.player_id = snakes_vec->Get(i)->player_id();
    auto color = snakes_vec->Get(i)->color();
    snake.color = {color->r(), color->g(), color->b(), 255};
    Dir dir;
    switch (snakes_vec->Get(i)->dir()) {
      case dctl::flat_msg::Dir_Up:
        dir = kUp;
        break;
      case dctl::flat_msg::Dir_Down:
        dir = kDown;
        break;
      case dctl::flat_msg::Dir_Left:
        dir = kLeft;
        break;
      case dctl::flat_msg::Dir_Right:
        dir = kRight;
        break;
      default:
        break;
    }
    snake.dir = dir;
    for (unsigned int j = 0; j < snakes_vec->Get(i)->tail()->size(); j++) {
      snake.tail.push_back({snakes_vec->Get(i)->tail()->Get(j)->x(),
                            snakes_vec->Get(i)->tail()->Get(j)->y()});
    }
    state.snakes.push_back(snake);
  }
  return state;
};

std::vector<char> PackRequest(const std::string &name) {
  flatbuffers::FlatBufferBuilder builder;
  auto name_flat = builder.CreateString(name);
  auto request = dctl::flat_msg::CreateRequest(builder, name_flat);
  auto msg = dctl::flat_msg::CreateMessage(builder, dctl::flat_msg::Any_Request,
                                           request.Union());
  builder.Finish(request);
  std::vector<char> serialized(builder.GetBufferPointer(),
                               builder.GetBufferPointer() + builder.GetSize());
  return serialized;
}

Request UnpackRequest(const dctl::flat_msg::Request *req_flat) {
  Request req{req_flat->name()->str()};
  return req;
}

std::vector<char> PackReply(int player_id, const Settings &st) {
  flatbuffers::FlatBufferBuilder builder;
  auto settings = dctl::flat_msg::Settings(
      st.max_players, st.map_width, st.map_height, st.speed, st.dt,
      st.max_length, st.head_diameter, st.tail_width);
  auto reply = dctl::flat_msg::CreateReply(builder, player_id, &settings);
  auto msg = dctl::flat_msg::CreateMessage(builder, dctl::flat_msg::Any_Reply,
                                           reply.Union());
  builder.Finish(reply);
  std::vector<char> serialized(builder.GetBufferPointer(),
                               builder.GetBufferPointer() + builder.GetSize());
  return serialized;
}

Reply UnpackReply(const dctl::flat_msg::Reply *rep_flat) {
  auto setts = rep_flat->settings();
  Settings settings(setts->max_clients(), setts->map_width(),
                    setts->map_height(), setts->speed(), setts->dt(),
                    setts->max_length(), setts->head_diameter(),
                    setts->tail_width());
  Reply rep{rep_flat->player_id(), settings};
  return rep;
}

std::variant<Request, Reply, InputPack, State> UnpackMessage(
    const std::vector<char> &buf) {
  auto message = dctl::flat_msg::GetMessage(buf.data());
  switch (message->msg_type()) {
    case dctl::flat_msg::Any_Request: {
      return UnpackRequest(message->msg_as_Request());
      break;
    }
    case dctl::flat_msg::Any_Reply: {
      return UnpackReply(message->msg_as_Reply());
      break;
    }
    case dctl::flat_msg::Any_InputPack: {
      return UnpackInputPack(message->msg_as_InputPack());
      break;
    }
    case dctl::flat_msg::Any_State: {
      return UnpackState(message->msg_as_State());
      break;
    }
    default:
      break;
  }
  return {};
}
