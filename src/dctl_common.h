#pragma once

#include <cmath>
#include <deque>
#include <iterator>
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
  Input()
      : sequence(0),
        player_id(0),
        left(false),
        right(false),
        up(false),
        down(false) {}
  Input(uint32_t sequence, int player_id, bool left, bool right, bool up,
        bool down)
      : sequence(sequence),
        player_id(player_id),
        left(left),
        right(right),
        up(up),
        down(down) {}
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

struct Settings {
  size_t max_players;
  float map_width;
  float map_height;
  float speed;
  double dt;
  size_t max_length;
  float head_diameter;
  float tail_width;
  Settings(size_t max_players, float map_width, float map_height, float speed,
           double dt, size_t max_length, float head_diameter,
           float tail_width)
      : max_players(max_players),
        map_width(map_width),
        map_height(map_height),
        speed(speed),
        dt(dt),
        max_length(max_length),
        head_diameter(head_diameter),
        tail_width(tail_width) {}
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

std::vector<char> PackInput(const std::vector<Input> &inp_vec);

std::vector<Input> UnpackInput(const std::vector<char> &buf);

std::vector<char> PackState(const State &st);

State UnpackState(const std::vector<char> &buf);
