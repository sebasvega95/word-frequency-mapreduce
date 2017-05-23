#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>

namespace logging {
void error(std::string);
void info(std::string);
void warn(std::string);
}  // namespace logging

void logging::error(std::string msg) {
  std::cout << "ERROR " << msg << std::endl;
}
void logging::info(std::string msg) {
  std::cout << "INFO  " << msg << std::endl;
}
void logging::warn(std::string msg) {
  std::cout << "WARN  " << msg << std::endl;
}

#endif
