// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_DCTLREPLY_DCTL_FLAT_SETTINGS_H_
#define FLATBUFFERS_GENERATED_DCTLREPLY_DCTL_FLAT_SETTINGS_H_

#include "flatbuffers/flatbuffers.h"

namespace dctl {
namespace flat_settings {

struct Settings;

struct Reply;
struct ReplyBuilder;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(8) Settings FLATBUFFERS_FINAL_CLASS {
 private:
  uint32_t max_clients_;
  float map_width_;
  float map_height_;
  float speed_;
  double dt_;
  uint32_t max_length_;
  float head_diameter_;
  float tail_width_;
  int32_t padding0__;

 public:
  Settings()
      : max_clients_(0),
        map_width_(0),
        map_height_(0),
        speed_(0),
        dt_(0),
        max_length_(0),
        head_diameter_(0),
        tail_width_(0),
        padding0__(0) {
    (void)padding0__;
  }
  Settings(uint32_t _max_clients, float _map_width, float _map_height, float _speed, double _dt, uint32_t _max_length, float _head_diameter, float _tail_width)
      : max_clients_(flatbuffers::EndianScalar(_max_clients)),
        map_width_(flatbuffers::EndianScalar(_map_width)),
        map_height_(flatbuffers::EndianScalar(_map_height)),
        speed_(flatbuffers::EndianScalar(_speed)),
        dt_(flatbuffers::EndianScalar(_dt)),
        max_length_(flatbuffers::EndianScalar(_max_length)),
        head_diameter_(flatbuffers::EndianScalar(_head_diameter)),
        tail_width_(flatbuffers::EndianScalar(_tail_width)),
        padding0__(0) {
    (void)padding0__;
  }
  uint32_t max_clients() const {
    return flatbuffers::EndianScalar(max_clients_);
  }
  float map_width() const {
    return flatbuffers::EndianScalar(map_width_);
  }
  float map_height() const {
    return flatbuffers::EndianScalar(map_height_);
  }
  float speed() const {
    return flatbuffers::EndianScalar(speed_);
  }
  double dt() const {
    return flatbuffers::EndianScalar(dt_);
  }
  uint32_t max_length() const {
    return flatbuffers::EndianScalar(max_length_);
  }
  float head_diameter() const {
    return flatbuffers::EndianScalar(head_diameter_);
  }
  float tail_width() const {
    return flatbuffers::EndianScalar(tail_width_);
  }
};
FLATBUFFERS_STRUCT_END(Settings, 40);

struct Reply FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef ReplyBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_PLAYER_ID = 4,
    VT_SETTINGS = 6
  };
  uint32_t player_id() const {
    return GetField<uint32_t>(VT_PLAYER_ID, 0);
  }
  const dctl::flat_settings::Settings *settings() const {
    return GetStruct<const dctl::flat_settings::Settings *>(VT_SETTINGS);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint32_t>(verifier, VT_PLAYER_ID) &&
           VerifyField<dctl::flat_settings::Settings>(verifier, VT_SETTINGS) &&
           verifier.EndTable();
  }
};

struct ReplyBuilder {
  typedef Reply Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_player_id(uint32_t player_id) {
    fbb_.AddElement<uint32_t>(Reply::VT_PLAYER_ID, player_id, 0);
  }
  void add_settings(const dctl::flat_settings::Settings *settings) {
    fbb_.AddStruct(Reply::VT_SETTINGS, settings);
  }
  explicit ReplyBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Reply> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Reply>(end);
    return o;
  }
};

inline flatbuffers::Offset<Reply> CreateReply(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint32_t player_id = 0,
    const dctl::flat_settings::Settings *settings = 0) {
  ReplyBuilder builder_(_fbb);
  builder_.add_settings(settings);
  builder_.add_player_id(player_id);
  return builder_.Finish();
}

inline const dctl::flat_settings::Reply *GetReply(const void *buf) {
  return flatbuffers::GetRoot<dctl::flat_settings::Reply>(buf);
}

inline const dctl::flat_settings::Reply *GetSizePrefixedReply(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<dctl::flat_settings::Reply>(buf);
}

inline const char *ReplyIdentifier() {
  return "REP_";
}

inline bool ReplyBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, ReplyIdentifier());
}

inline bool VerifyReplyBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<dctl::flat_settings::Reply>(ReplyIdentifier());
}

inline bool VerifySizePrefixedReplyBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<dctl::flat_settings::Reply>(ReplyIdentifier());
}

inline const char *ReplyExtension() {
  return "reply";
}

inline void FinishReplyBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<dctl::flat_settings::Reply> root) {
  fbb.Finish(root, ReplyIdentifier());
}

inline void FinishSizePrefixedReplyBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<dctl::flat_settings::Reply> root) {
  fbb.FinishSizePrefixed(root, ReplyIdentifier());
}

}  // namespace flat_settings
}  // namespace dctl

#endif  // FLATBUFFERS_GENERATED_DCTLREPLY_DCTL_FLAT_SETTINGS_H_
