#include "dctl_raylib.h"

void DrawLineExRoundEnd(Vec2 start_pos, Vec2 end_pos, float thick,
                        Color color) {
  DrawLineEx({start_pos.x, start_pos.y}, {end_pos.x, end_pos.y}, thick, color);
  DrawCircleV({start_pos.x, start_pos.y}, thick / 2, color);
  DrawCircleV({end_pos.x, end_pos.y}, thick / 2, color);
}

void DrawLineExSquareEnd(Vec2 start_pos, Vec2 end_pos, float thick,
                         Color color) {
  Vector2 v1{start_pos.x, start_pos.y};
  Vector2 v2{end_pos.x, end_pos.y};
  Vector2 center = Vector2Lerp(v1, v2, 0.5);
  auto len = Vector2Distance(v1,v2)+thick;
  auto dir = Vector2Normalize(Vector2Subtract(v1,v2));
  auto half = Vector2Scale(dir,len/2);
  v1= Vector2Add(center, half);
  v2= Vector2Subtract(center, half);
  DrawLineEx(v1, v2, thick, color);
}

void Draw(const State &st, const float map_width, const float map_height,
          const float scale, const float head_diameter,
          const float tail_width) {
  ClearBackground(BLACK);
  for (auto i = 0; i < map_width; i++) {
    for (auto j = 0; j < map_height; j++) {
      DrawPixel((i + 1) * scale, (j + 1) * scale, GRAY);
    }
  }
  for (auto &s : st.snakes) {
    auto &curTail = s.tail;
    Color curColor{s.color.r, s.color.g, s.color.b, s.color.a};
    float thick = tail_width * scale;
    for (auto it = curTail.begin(); it != curTail.end() - 1; it++) {
      DrawLineExSquareEnd({it->x * scale, it->y * scale},
                 {(it + 1)->x * scale, (it + 1)->y * scale}, thick, curColor);
    }
    DrawCircle(curTail.back().x * scale, curTail.back().y * scale,
               (head_diameter / 2) * scale, curColor);
  }
}
