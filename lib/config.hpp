#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <fstream>
#include <iostream>

#include "json.hpp"
#include "logging.hpp"

using json = nlohmann::json;

namespace config {
json load_config();
}

json config::load_config() {
  std::ifstream config_file("config.json");
  json config;

  if (!config_file) {
    logging::error("No config found");
    exit(EXIT_FAILURE);
  }

  try {
    config_file >> config;
    logging::info("Loaded config file");
    return config;
  } catch (nlohmann::detail::parse_error error) {
    logging::error("Invalid config file");
    exit(EXIT_FAILURE);
  }
}

#endif
