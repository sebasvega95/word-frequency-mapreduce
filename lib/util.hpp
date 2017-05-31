#ifndef UTIL_HPP
#define UTIL_HPP

#include <algorithm>
#include <string>

namespace util {
void uppercaserer(std::string&);
void remove_punct(std::string&);
}  // namespace util

void util::uppercaserer(std::string& str) {
  std::transform(str.begin(), str.end(), str.begin(), tolower);
}

void util::remove_punct(std::string& str) {
  str.erase(std::remove_if(str.begin(), str.end(), ispunct), str.end());
}

#endif
