#include <zmqpp/zmqpp.hpp>
#include "lib/json.hpp"

#include "lib/config.hpp"
#include "lib/logging.hpp"

using json = nlohmann::json;

json nodes;

int main(int argc, char *argv[]) {
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
  std::string dir = nodes["mappers"][node_name]["dir"];
  std::cout << "\tMapper" << std::endl;
  std::cout << "\tDirection: " << dir << std::endl;

  return 0;
}
