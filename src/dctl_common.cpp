#include "dctl_common.h"

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

Vector2 NewPos(Dir dir, float dist, Vector2 cur_pos) {
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
bool IsIntersecting(const Vector2 &p1, const Vector2 &p2, const Vector2 &q1,
                    const Vector2 &q2) {
  return (((q1.x - p1.x) * (p2.y - p1.y) - (q1.y - p1.y) * (p2.x - p1.x)) *
              ((q2.x - p1.x) * (p2.y - p1.y) - (q2.y - p1.y) * (p2.x - p1.x)) <
          0) &&
         (((p1.x - q1.x) * (q2.y - q1.y) - (p1.y - q1.y) * (q2.x - q1.x)) *
              ((p2.x - q1.x) * (q2.y - q1.y) - (p2.y - q1.y) * (q2.x - q1.x)) <
          0);
}

Vector2 IntersectionPoint(const Vector2 &p1, const Vector2 &p2,
                          const Vector2 &q1, const Vector2 &q2) {
  Vector2 result;
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
    if (Vector2Distance(*head1, p) <
        Vector2Distance(*snake2.tail.rbegin(), p)) {
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

void DrawLineExRoundEnd(Vector2 start_pos, Vector2 end_pos, float thick,
                        Color color) {
  DrawLineEx(start_pos, end_pos, thick, color);
  DrawCircleV(start_pos, thick / 2, color);
  DrawCircleV(end_pos, thick / 2, color);
}

void Draw(const State &st, const float map_width, const float map_height,
          const float scale) {
  ClearBackground(BLACK);
  for (auto i = 0; i < map_width; i++) {
    for (auto j = 0; j < map_height; j++) {
      DrawPixel((i + 1) * scale, (j + 1) * scale, GRAY);
    }
  }
  for (auto &s : st.snakes) {
    auto &curTail = s.tail;
    auto &curColor = s.color;
    size_t thick = (size_t)std::round((float)scale / 1.5);
    for (auto it = curTail.begin(); it != curTail.end() - 1; it++) {
      DrawLineExRoundEnd(
          {it->x * (float)scale, it->y * (float)scale},
          {(it + 1)->x * (float)scale, (it + 1)->y * (float)scale}, thick,
          curColor);
    }
    DrawCircle(curTail.back().x * (float)scale, curTail.back().y * (float)scale,
               (float)scale / 2, curColor);
  }
}
