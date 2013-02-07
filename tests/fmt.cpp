#include <stdio.h>
#include <string.h>
#include <cstdint>
#include <iostream>
#include <vector>

#include <fmt/format.hpp>

namespace {

class Value {
public:
  Value(int64_t n, uint32_t w, std::string pr, std::string fmt)
      : number(n), width(w), printf_fmt(pr), fmt_fmt(fmt) {}

  int64_t number;
  uint32_t width;
  std::string printf_fmt;
  std::string fmt_fmt;
};

void check(Value &v) {
  char b1[1024];
  char b2[1024];

  uint32_t s1;
  uint32_t s2;

  if (v.width > 0)
    s1 = sprintf(b1, v.printf_fmt.c_str(), v.width, v.number);
  else
    s1 = sprintf(b1, v.printf_fmt.c_str(), v.number);

  s2 = fmt::format(b2, v.fmt_fmt.c_str(), v.number);

  std::string str1(b1, s1);
  std::string str2(b2, s2);

  if (str1 != str2) {
    std::cerr << "FAIL: " << v.number << std::endl;
    std::cerr << "  width: " << v.width << std::endl;
    std::cerr << "  s1: " << str1 << std::endl;
    std::cerr << "  s2: " << str2 << std::endl;
    std::cerr << "pfmt: " << v.printf_fmt << std::endl;
    std::cerr << "ffmt: " << v.fmt_fmt << std::endl;
    std::cerr << std::endl;
  }
}

}

int main(int argc, char *argv[]) {
  std::vector<Value> values;
  std::string line;
  std::string fmt1;
  std::string fmt2;

  while (std::cin) {
    std::getline(std::cin, line);
    int64_t i = atol(line.c_str());
    std::getline(std::cin, line);
    uint32_t w = atoi(line.c_str());
    std::getline(std::cin, fmt1);
    std::getline(std::cin, fmt2);
    values.emplace_back(i, w, fmt1, fmt2);
  }
  values.pop_back();

  for (auto &v : values)
    check(v);

  return 0;
}
