#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <iostream>
#include <vector>

#include <fmt/itoa.hpp>

namespace {

uint32_t valid_itoa(int32_t n, uint32_t width, uint32_t flags, char *b) {
  char fmt[8];
  uint32_t p = 0;
  fmt[p++] = '%';
  if (flags & fmt::Flag::SignPlus)    fmt[p++] = '+';
  if (flags & fmt::Flag::SignSpace)   fmt[p++] = ' ';
  if (flags & fmt::Flag::AlignLeft)   fmt[p++] = '-';
  if (flags & fmt::Flag::ZeroPadding) fmt[p++] = '0';
  if (width > 0)                      fmt[p++] = '*';
  fmt[p++] = 'd';
  fmt[p] = '\0';

  if (width > 0)
    return sprintf(b, fmt, width, n);
  else
    return sprintf(b, fmt, n);
}

class Value {
public:
  Value(int32_t n, uint32_t w, uint32_t f)
      : number(n), width(w), flags(f) {}

  int32_t number;
  uint32_t width;
  uint32_t flags;
};

void check(int32_t number, uint32_t width, uint32_t flags) {
  char b1[64];
  char b2[64];

  uint32_t s1 = fmt::itoa(number, width, flags, b1);
  uint32_t s2 = valid_itoa(number, width, flags, b2);

  std::string str1(b1, s1);
  std::string str2(b2, s2);

  if (str1 != str2) {
    std::cerr << "FAIL: " << number << " w:" << width << " f:" << flags << std::endl;
    std::cerr << "  s1: " << str1 << std::endl;
    std::cerr << "  s2: " << str2 << std::endl;
  }
}

}

int main(int argc, char *argv[]) {
  std::vector<Value> values;
  std::string line;

  while (std::cin) {
    std::getline(std::cin, line);
    int32_t n = atoi(line.c_str());
    std::getline(std::cin, line);
    uint32_t w = atoi(line.c_str());
    std::getline(std::cin, line);
    uint32_t f = atoi(line.c_str());
    values.emplace_back(n, w, f);
  }

  for (auto &v : values)
    check(v.number, v.width, v.flags);

  return 0;
}
