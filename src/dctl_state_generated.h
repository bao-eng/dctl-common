// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_DCTLSTATE_DCTL_FLAT_STATE_H_
#define FLATBUFFERS_GENERATED_DCTLSTATE_DCTL_FLAT_STATE_H_

#include "flatbuffers/flatbuffers.h"

namespace dctl {
namespace flat_state {

struct Vec2;

struct Color;

struct Snake;
struct SnakeBuilder;

struct State;
struct StateBuilder;

enum Dir : int8_t {
  Dir_None = 0,
  Dir_Up = 1,
  Dir_Down = 2,
  Dir_Left = 3,
  Dir_Right = 4,
  Dir_MIN = Dir_None,
  Dir_MAX = Dir_Right
};

inline const Dir (&EnumValuesDir())[5] {
  static const Dir values[] = {
    Dir_None,
    Dir_Up,
    Dir_Down,
    Dir_Left,
    Dir_Right
  };
  return values;
}

inline const char * const *EnumNamesDir() {
  static const char * const names[6] = {
    "None",
    "Up",
    "Down",
    "Left",
    "Right",
    nullptr
  };
  return names;
}

inline const char *EnumNameDir(Dir e) {
  if (flatbuffers::IsOutRange(e, Dir_None, Dir_Right)) return "";
  const size_t index = static_cast<size_t>(e);
  return EnumNamesDir()[index];
}

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Vec2 FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;

 public:
  Vec2()
      : x_(0),
        y_(0) {
  }
  Vec2(float _x, float _y)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
};
FLATBUFFERS_STRUCT_END(Vec2, 8);

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(1) Color FLATBUFFERS_FINAL_CLASS {
 private:
  uint8_t r_;
  uint8_t g_;
  uint8_t b_;

 public:
  Color()
      : r_(0),
        g_(0),
        b_(0) {
  }
  Color(uint8_t _r, uint8_t _g, uint8_t _b)
      : r_(flatbuffers::EndianScalar(_r)),
        g_(flatbuffers::EndianScalar(_g)),
        b_(flatbuffers::EndianScalar(_b)) {
  }
  uint8_t r() const {
    return flatbuffers::EndianScalar(r_);
  }
  uint8_t g() const {
    return flatbuffers::EndianScalar(g_);
  }
  uint8_t b() const {
    return flatbuffers::EndianScalar(b_);
  }
};
FLATBUFFERS_STRUCT_END(Color, 3);

struct Snake FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef SnakeBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PLAYER_ID = 4,
    VT_TAIL = 6,
    VT_DIR = 8,
    VT_COLOR = 10
  };
  int32_t player_id() const {
    return GetField<int32_t>(VT_PLAYER_ID, 0);
  }
  const flatbuffers::Vector<const dctl::flat_state::Vec2 *> *tail() const {
    return GetPointer<const flatbuffers::Vector<const dctl::flat_state::Vec2 *> *>(VT_TAIL);
  }
  dctl::flat_state::Dir dir() const {
    return static_cast<dctl::flat_state::Dir>(GetField<int8_t>(VT_DIR, 0));
  }
  const dctl::flat_state::Color *color() const {
    return GetStruct<const dctl::flat_state::Color *>(VT_COLOR);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_PLAYER_ID) &&
           VerifyOffset(verifier, VT_TAIL) &&
           verifier.VerifyVector(tail()) &&
           VerifyField<int8_t>(verifier, VT_DIR) &&
           VerifyField<dctl::flat_state::Color>(verifier, VT_COLOR) &&
           verifier.EndTable();
  }
};

struct SnakeBuilder {
  typedef Snake Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_player_id(int32_t player_id) {
    fbb_.AddElement<int32_t>(Snake::VT_PLAYER_ID, player_id, 0);
  }
  void add_tail(flatbuffers::Offset<flatbuffers::Vector<const dctl::flat_state::Vec2 *>> tail) {
    fbb_.AddOffset(Snake::VT_TAIL, tail);
  }
  void add_dir(dctl::flat_state::Dir dir) {
    fbb_.AddElement<int8_t>(Snake::VT_DIR, static_cast<int8_t>(dir), 0);
  }
  void add_color(const dctl::flat_state::Color *color) {
    fbb_.AddStruct(Snake::VT_COLOR, color);
  }
  explicit SnakeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Snake> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Snake>(end);
    return o;
  }
};

inline flatbuffers::Offset<Snake> CreateSnake(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t player_id = 0,
    flatbuffers::Offset<flatbuffers::Vector<const dctl::flat_state::Vec2 *>> tail = 0,
    dctl::flat_state::Dir dir = dctl::flat_state::Dir_None,
    const dctl::flat_state::Color *color = 0) {
  SnakeBuilder builder_(_fbb);
  builder_.add_color(color);
  builder_.add_tail(tail);
  builder_.add_player_id(player_id);
  builder_.add_dir(dir);
  return builder_.Finish();
}

inline flatbuffers::Offset<Snake> CreateSnakeDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t player_id = 0,
    const std::vector<dctl::flat_state::Vec2> *tail = nullptr,
    dctl::flat_state::Dir dir = dctl::flat_state::Dir_None,
    const dctl::flat_state::Color *color = 0) {
  auto tail__ = tail ? _fbb.CreateVectorOfStructs<dctl::flat_state::Vec2>(*tail) : 0;
  return dctl::flat_state::CreateSnake(
      _fbb,
      player_id,
      tail__,
      dir,
      color);
}

struct State FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef StateBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_SEQUENCE = 4,
    VT_SNAKES = 6
  };
  uint32_t sequence() const {
    return GetField<uint32_t>(VT_SEQUENCE, 0);
  }
  const flatbuffers::Vector<flatbuffers::Offset<dctl::flat_state::Snake>> *snakes() const {
    return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<dctl::flat_state::Snake>> *>(VT_SNAKES);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_SEQUENCE) &&
           VerifyOffset(verifier, VT_SNAKES) &&
           verifier.VerifyVector(snakes()) &&
           verifier.VerifyVectorOfTables(snakes()) &&
           verifier.EndTable();
  }
};

struct StateBuilder {
  typedef State Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_sequence(uint32_t sequence) {
    fbb_.AddElement<uint32_t>(State::VT_SEQUENCE, sequence, 0);
  }
  void add_snakes(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<dctl::flat_state::Snake>>> snakes) {
    fbb_.AddOffset(State::VT_SNAKES, snakes);
  }
  explicit StateBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<State> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<State>(end);
    return o;
  }
};

inline flatbuffers::Offset<State> CreateState(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t sequence = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<dctl::flat_state::Snake>>> snakes = 0) {
  StateBuilder builder_(_fbb);
  builder_.add_snakes(snakes);
  builder_.add_sequence(sequence);
  return builder_.Finish();
}

inline flatbuffers::Offset<State> CreateStateDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t sequence = 0,
    const std::vector<flatbuffers::Offset<dctl::flat_state::Snake>> *snakes = nullptr) {
  auto snakes__ = snakes ? _fbb.CreateVector<flatbuffers::Offset<dctl::flat_state::Snake>>(*snakes) : 0;
  return dctl::flat_state::CreateState(
      _fbb,
      sequence,
      snakes__);
}

inline const dctl::flat_state::State *GetState(const void *buf) {
  return flatbuffers::GetRoot<dctl::flat_state::State>(buf);
}

inline const dctl::flat_state::State *GetSizePrefixedState(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<dctl::flat_state::State>(buf);
}

inline const char *StateIdentifier() {
  return "STAT";
}

inline bool StateBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, StateIdentifier());
}

inline bool VerifyStateBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<dctl::flat_state::State>(StateIdentifier());
}

inline bool VerifySizePrefixedStateBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<dctl::flat_state::State>(StateIdentifier());
}

inline const char *StateExtension() {
  return "state";
}

inline void FinishStateBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<dctl::flat_state::State> root) {
  fbb.Finish(root, StateIdentifier());
}

inline void FinishSizePrefixedStateBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<dctl::flat_state::State> root) {
  fbb.FinishSizePrefixed(root, StateIdentifier());
}

}  // namespace flat_state
}  // namespace dctl

#endif  // FLATBUFFERS_GENERATED_DCTLSTATE_DCTL_FLAT_STATE_H_
