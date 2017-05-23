#include <zmqpp/zmqpp.hpp>
#include "lib/json.hpp"

#include "lib/config.hpp"
#include "lib/logging.hpp"

using json = nlohmann::json;

json nodes;

int main(int argc, char *argv[]) {
  nodes = config::load_config();

  if (nodes["partitioner"] == nullptr) {
    logging::error("Partitioner not in config file");
    exit(EXIT_FAILURE);
  }

  std::string dir = nodes["partitioner"]["dir"];
  logging::info("Partitioner");
  std::cout << "\tDirection: " << dir << std::endl;

  return 0;
}
