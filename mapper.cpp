#include <zmqpp/zmqpp.hpp>
#include "lib/json.hpp"

#include "lib/config.hpp"
#include "lib/dispatcher.hpp"
#include "lib/logging.hpp"
#include "lib/util.hpp"

using json = nlohmann::json;

json nodes;

std::string receive_text(zmqpp::socket& socket) {
  json message = dispatcher::receive(socket);
  int text_num = message["number"];
  std::string text = message["text"];

  logging::info("Received text #" + std::to_string(text_num));
  return text;
}

json count_words(std::string& text) {
  json freq;
  std::stringstream words(text);
  std::string word;

  while (words >> word) {
    util::uppercaserer(word);
    util::remove_punct(word);
    int freq_word = (freq[word] == nullptr) ? 0 : (int)freq[word];
    freq[word] = freq_word + 1;
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

  if (nodes["mappers"][node_name] == nullptr) {
    logging::error("\"" + node_name + "\" not in config file");
    exit(EXIT_FAILURE);
  }

  logging::info(node_name);
  std::string my_ip = nodes["mappers"][node_name]["ip"];
  std::string my_port = nodes["mappers"][node_name]["port"];
  std::string my_dir = my_ip + ":" + my_port;
  std::cout << "\tMapper" << std::endl;
  std::cout << "\tDirection: " << my_dir << std::endl;

  zmqpp::context ctx;
  zmqpp::socket partitioner_socket(ctx, zmqpp::socket_type::pull);
  partitioner_socket.bind("tcp://*:" + my_port);

  std::string text = receive_text(partitioner_socket);
  json freq = count_words(text);

  std::cout << std::setw(2) << freq << std::endl;

  return 0;
}
