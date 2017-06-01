#include <zmqpp/zmqpp.hpp>
#include "lib/json.hpp"

#include "lib/config.hpp"
#include "lib/dispatcher.hpp"
#include "lib/logging.hpp"

using json = nlohmann::json;

json nodes;

json receive_freqs(zmqpp::socket& socket) {
  int num_mappers = nodes["mappers"].size();
  json freq;
  while (num_mappers-- > 0) {
    json message = dispatcher::receive(socket);
    for (json::iterator it = message.begin(); it != message.end(); ++it) {
      std::string word = it.key();
      int word_freq = it.value();
      int existing_freq = (freq[word] == nullptr) ? 0 : (int)freq[word];
      freq[word] = existing_freq + word_freq;
    }
  }
  return freq;
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " node-id" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string node_name = argv[1];
  nodes = config::load_config();

  if (nodes["reducers"][node_name] == nullptr) {
    logging::error("\"" + node_name + "\" not in config file");
    exit(EXIT_FAILURE);
  }

  logging::info(node_name);
  std::string my_ip = nodes["reducers"][node_name]["ip"];
  std::string my_port = nodes["reducers"][node_name]["port"];
  std::string my_dir = my_ip + ":" + my_port;
  std::cout << "\tReducer" << std::endl;
  std::cout << "\tDirection: " << my_dir << std::endl;

  zmqpp::context ctx;
  zmqpp::socket mappers_socket(ctx, zmqpp::socket_type::pull);
  mappers_socket.bind("tcp://*:" + my_port);

  json freq = receive_freqs(mappers_socket);
  std::cout << std::setw(2) << freq << std::endl;

  return 0;
}
