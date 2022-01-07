#pragma once

#include <stdint.h>

#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "raylib.h"
#include "raymath.h"

#include "dctl_input_generated.h"
#include "dctl_state_generated.h"

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

State NextState(const State &st, const std::unordered_map<int, Input> &inp,
                double dt, float speed, size_t max_length);

bool IsIntersecting(const Vector2 &p1, const Vector2 &p2, const Vector2 &q1,
                    const Vector2 &q2);

bool IsCrossing(const Snake &snake1, const Snake &snake2);

State CheckCollisions(const State &st);

State CheckBounds(const State &st, float map_width, float map_height);

std::unordered_set<int> GetPlayers(const State &st);

void DrawLineExRoundEnd(Vector2 start_pos, Vector2 end_pos, float thick,
                        Color color);
void Draw(const State &st, const float map_width, const float map_height,
          const float scale, const float head_diameter, const float tail_width);

std::vector<char> PackInput(const Input &inp);

Input UnpackInput(const std::vector<char> &buf);

std::vector<char> PackState(const State &st);

State UnpackState(const std::vector<char> &buf);
