#pragma once

#include <cmath>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "dctl_input_generated.h"
#include "dctl_state_generated.h"

struct Vec2 {
  float x;
  float y;
};

struct Col {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};

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
  std::deque<Vec2> tail;
  Dir dir;
  Col color;
};

struct State {
  uint32_t sequence;
  std::vector<Snake> snakes;
};

struct StateInput {
  State state;
  std::unordered_map<int, Input> players_inputs;
};

float Vec2Distance(const Vec2 &v1, const Vec2 &v2);

Dir NewDir(const Dir &cur_dir, const Input &inp);

Vec2 NewPos(Dir dir, float dist, Vec2 cur_pos);

State NextState(const State &st, const std::unordered_map<int, Input> &inp,
                double dt, float speed, size_t max_length);

bool IsIntersecting(const Vec2 &p1, const Vec2 &p2, const Vec2 &q1,
                    const Vec2 &q2);

bool IsCrossing(const Snake &snake1, const Snake &snake2);

State CheckCollisions(const State &st);

State CheckBounds(const State &st, float map_width, float map_height);

std::unordered_set<int> GetPlayers(const State &st);

std::vector<char> PackInput(const Input &inp);

Input UnpackInput(const std::vector<char> &buf);

std::vector<char> PackState(const State &st);

State UnpackState(const std::vector<char> &buf);
