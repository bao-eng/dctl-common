// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_DCTLREQUEST_DCTL_FLAT_REQUEST_H_
#define FLATBUFFERS_GENERATED_DCTLREQUEST_DCTL_FLAT_REQUEST_H_

#include "flatbuffers/flatbuffers.h"

namespace dctl {
namespace flat_request {

struct Request;
struct RequestBuilder;

struct Request FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef RequestBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
};

struct RequestBuilder {
  typedef Request Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(Request::VT_NAME, name);
  }
  explicit RequestBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<Request> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<Request>(end);
    return o;
  }
};

inline flatbuffers::Offset<Request> CreateRequest(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  RequestBuilder builder_(_fbb);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<Request> CreateRequestDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return dctl::flat_request::CreateRequest(
      _fbb,
      name__);
}

inline const dctl::flat_request::Request *GetRequest(const void *buf) {
  return flatbuffers::GetRoot<dctl::flat_request::Request>(buf);
}

inline const dctl::flat_request::Request *GetSizePrefixedRequest(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<dctl::flat_request::Request>(buf);
}

inline const char *RequestIdentifier() {
  return "REQ_";
}

inline bool RequestBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, RequestIdentifier());
}

inline bool VerifyRequestBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<dctl::flat_request::Request>(RequestIdentifier());
}

inline bool VerifySizePrefixedRequestBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<dctl::flat_request::Request>(RequestIdentifier());
}

inline const char *RequestExtension() {
  return "request";
}

inline void FinishRequestBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<dctl::flat_request::Request> root) {
  fbb.Finish(root, RequestIdentifier());
}

inline void FinishSizePrefixedRequestBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<dctl::flat_request::Request> root) {
  fbb.FinishSizePrefixed(root, RequestIdentifier());
}

}  // namespace flat_request
}  // namespace dctl

#endif  // FLATBUFFERS_GENERATED_DCTLREQUEST_DCTL_FLAT_REQUEST_H_
