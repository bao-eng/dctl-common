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
bool IsIntersecting(const Vector2 &p1, const Vector2 &p2, const Vector2 &q1,
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
      if (IsIntersecting(*head, *neck, *it, *(it - 1))) {
        return true;
      }
    }
  }
  return false;
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
                     *(snake1.tail.rbegin() + 1))) {
    auto p = IntersectionPoint(*head1, *neck1, *snake2.tail.rbegin(),
                               *(snake1.tail.rbegin() + 1));
    if (Vector2Distance(*head1, p) <
        Vector2Distance(*snake2.tail.rbegin(), p)) {
      return true;
    }
  }
  if (snake2.tail.size() > 2) {
    for (auto it = snake2.tail.rbegin() + 2; it != snake2.tail.rend(); it++) {
      if (IsIntersecting(*head1, *neck1, *it, *(it - 1))) {
        return true;
      }
    }
  }
  return false;
}
