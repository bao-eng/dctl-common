#pragma once

#include <stdint.h>

#include <deque>
#include <unordered_map>
#include <vector>

#include "raylib.h"
#include "raymath.h"

enum Dir { kNone, kUp, kDown, kLeft, kRight };

struct Input {
  uint32_t sequence;
  int player_id;
  bool left;
  bool right;
  bool up;
  bool down;
};

struct Snake {
  int player_id;
  std::deque<Vector2> tail;
  Dir dir;
  Color color;
};

struct State {
  uint32_t sequence;
  std::vector<Snake> snakes;
};

struct StateInput {
  State state;
  std::unordered_map<int, Input> players_inputs;
};

Dir NewDir(const Dir &cur_dir, const Input &inp);

Vector2 NewPos(Dir dir, float dist, Vector2 cur_pos);

bool IsIntersecting(const Vector2 &p1, const Vector2 &p2, const Vector2 &q1,
                    const Vector2 &q2);

bool IsSelfIntersecting(const Snake &snake);

bool IsCrossing(const Snake &snake1, const Snake &snake2);

void DrawLineExRoundEnd(Vector2 start_pos, Vector2 end_pos, float thick,
                              Color color);
void Draw(const State &st, const float map_width, const float map_height, const float scale);