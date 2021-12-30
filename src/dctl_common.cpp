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

// https://stackoverflow.com/a/14177062
bool isIntersecting(const Vector2 &p1, const Vector2 &p2, const Vector2 &q1,
                    const Vector2 &q2) {
  return (((q1.x - p1.x) * (p2.y - p1.y) - (q1.y - p1.y) * (p2.x - p1.x)) *
              ((q2.x - p1.x) * (p2.y - p1.y) - (q2.y - p1.y) * (p2.x - p1.x)) <
          0) &&
         (((p1.x - q1.x) * (q2.y - q1.y) - (p1.y - q1.y) * (q2.x - q1.x)) *
              ((p2.x - q1.x) * (q2.y - q1.y) - (p2.y - q1.y) * (q2.x - q1.x)) <
          0);
}

bool IsSelfIntersecting(const Snake &snake) {
  if (snake.tail.size() > 4) {
    auto head = snake.tail.rbegin();
    auto neck = snake.tail.rbegin() + 1;
    for (auto it = snake.tail.rbegin() + 2; it != snake.tail.rend(); it++) {
      if (isIntersecting(*head, *neck, *it, *(it - 1))) {
        return true;
      }
    }
  }
  return false;
}

bool IsCrossing(const Snake &s1, const Snake &s2) {
  
}
