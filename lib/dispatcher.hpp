#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <zmqpp/zmqpp.hpp>
#include "json.hpp"

using json = nlohmann::json;

namespace dispatcher {
void send(json&, zmqpp::socket&);
json receive(zmqpp::socket&);
}  // namespace dispatcher

void dispatcher::send(json& msg, zmqpp::socket& s) {
  zmqpp::message ans;
  ans << msg.dump();
  s.send(ans);
}

json dispatcher::receive(zmqpp::socket& s) {
  zmqpp::message m;
  s.receive(m);
  std::string msg;
  m >> msg;
  return json::parse(msg);
}

#endif
