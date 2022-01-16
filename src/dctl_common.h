#pragma once

#include <cmath>
#include <deque>
#include <iterator>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

#include "dctl_message_generated.h"

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

struct InputPack {
  std::deque<Input> vec;
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
  Settings()
      : max_players(0),
        map_width(0),
        map_height(0),
        speed(0),
        dt(0),
        max_length(0),
        head_diameter(0),
        tail_width(0) {}
  Settings(size_t max_players, float map_width, float map_height, float speed,
           double dt, size_t max_length, float head_diameter, float tail_width)
      : max_players(max_players),
        map_width(map_width),
        map_height(map_height),
        speed(speed),
        dt(dt),
        max_length(max_length),
        head_diameter(head_diameter),
        tail_width(tail_width) {}
};

struct Request {
  std::string name;
};

struct Reply {
  int player_id;
  Settings settings;
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

std::vector<char> PackInputPack(const InputPack &inpp);

InputPack UnpackInputPack(const dctl::flat_msg::InputPack *inpp_flat);

std::vector<char> PackState(const State &st);

State UnpackState(const dctl::flat_msg::State *state_flat);

std::vector<char> PackRequest(const std::string &name);

Request UnpackRequest(const dctl::flat_msg::Request *req_flat);

std::vector<char> PackReply(int player_id, const Settings &st);

Reply UnpackReply(dctl::flat_msg::Reply &rep_flat);

std::variant<Request, Reply, InputPack, State> UnpackMessage(
    const std::vector<char> &buf);
