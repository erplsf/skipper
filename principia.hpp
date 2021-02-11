#pragma once

#include <map>
#include <set>
#include <string>
#include <tuple>
#include <vector>

#include <krpc/decoder.hpp>
#include <krpc/encoder.hpp>
#include <krpc/error.hpp>
#include <krpc/event.hpp>
#include <krpc/object.hpp>
#include <krpc/service.hpp>
#include <krpc/stream.hpp>

namespace krpc {
namespace services {

class Principia : public Service {
 public:
  explicit Principia(Client* client);

  bool available();

  ::krpc::Stream<bool> available_stream();

  ::krpc::schema::ProcedureCall available_call();
};

}  // namespace services

namespace services {

inline Principia::Principia(Client* client):
  Service(client) {
}

inline bool Principia::available() {
  std::string _data = this->_client->invoke("Principia", "Available");
  bool _result;
  decoder::decode(_result, _data, this->_client);
  return _result;
}

inline ::krpc::Stream<bool> Principia::available_stream() {
  return ::krpc::Stream<bool>(this->_client, this->_client->build_call("Principia", "Available"));
}

inline ::krpc::schema::ProcedureCall Principia::available_call() {
  return this->_client->build_call("Principia", "Available");
}
}  // namespace services

}  // namespace krpc
