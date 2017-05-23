#ifndef FILE_HPP
#define FILE_HPP

#include <cctype>
#include <fstream>
#include <string>
#include <vector>

namespace file {
bool exists(std::string&);
size_t size(std::string&);
int read_until_word(std::string&, std::string&, size_t, size_t);
std::vector<std::string> read_word_chunks(std::string&, size_t);
}  // namespace file

bool file::exists(std::string& filename) {
  std::ifstream fin(filename);
  bool ok = fin.good();
  fin.close();

  return ok;
}

size_t file::size(std::string& filename) {
  std::ifstream fin(filename);
  if (!fin) {
    return 0;
  }

  fin.seekg(0, fin.end);
  size_t length = fin.tellg();
  fin.close();

  return length;
}

int file::read_until_word(std::string& filename, std::string& str,
                          size_t offset, size_t num_chars) {
  std::ifstream fin(filename);
  if (!fin) {
    return -1;
  }

  fin.seekg(offset);
  fin.seekg(num_chars, fin.cur);

  char c;
  while (!isspace(c = fin.peek()) && c != EOF) {
    fin.seekg(1, fin.cur);
    num_chars++;
  }

  fin.seekg(offset);
  str.resize(num_chars, ' ');
  fin.read(&str[0], num_chars);
  offset = fin.tellg();
  fin.close();

  return offset;
}

std::vector<std::string> file::read_word_chunks(std::string& filename,
                                                size_t num_chunks) {
  size_t filesize = file::size(filename);
  size_t num_chars = filesize / num_chunks;
  std::vector<std::string> words;
  int offset = 0;
  do {
    std::string str;
    offset = file::read_until_word(filename, str, offset, num_chars);
    words.push_back(str);
  } while (offset != -1);
  return words;
}

#endif
