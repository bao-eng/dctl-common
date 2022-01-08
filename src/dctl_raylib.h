#pragma once

#include "raylib.h"
#include "raymath.h"

#include "dctl_common.h"

void DrawLineExRoundEnd(Vec2 start_pos, Vec2 end_pos, float thick, Color color);

void DrawLineExSquareEnd(Vec2 start_pos, Vec2 end_pos, float thick, Color color);

void Draw(const State &st, const float map_width, const float map_height,
          const float scale, const float head_diameter, const float tail_width);
