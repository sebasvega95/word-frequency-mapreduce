#include <zmqpp/zmqpp.hpp>
#include "lib/json.hpp"

#include "lib/config.hpp"
#include "lib/dispatcher.hpp"
#include "lib/file.hpp"
#include "lib/logging.hpp"

using json = nlohmann::json;

json nodes;

void send_text_to_mappers(std::string& filename, int num_mappers) {
  std::vector<std::string> text = file::read_word_chunks(filename, num_mappers);

  zmqpp::context ctx;
  int i = 0;
  for (auto& mapper : nodes["mappers"]) {
    std::string ip = mapper["ip"];
    std::string port = mapper["port"];
    std::string dir = ip + ":" + port;
    zmqpp::socket mapper_socket(ctx, zmqpp::socket_type::push);
    mapper_socket.connect("tcp://" + dir);

    json message;
    message["number"] = i;
    message["text"] = text[i];
    logging::info("Sending text #" + std::to_string(i) + " to mapper in " +
                  dir);
    dispatcher::send(message, mapper_socket);
    i++;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " file" << std::endl;
    exit(EXIT_FAILURE);
  }

  nodes = config::load_config();

  if (nodes["partitioner"] == nullptr) {
    logging::error("Partitioner not in config file");
    exit(EXIT_FAILURE);
  }

  std::string my_ip = nodes["partitioner"]["ip"];
  std::string my_port = nodes["partitioner"]["port"];
  std::string my_dir = my_ip + ":" + my_port;
  logging::info("Partitioner");
  std::cout << "\tDirection: " << my_dir << std::endl;

  std::string filename = argv[1];
  int num_mappers = nodes["mappers"].size();
  send_text_to_mappers(filename, num_mappers);

  return 0;
}
