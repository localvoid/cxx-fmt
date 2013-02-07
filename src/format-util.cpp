#include <climits>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fmt/format.hpp>

using namespace fmt;

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: format [FORMAT_STRING] [ARGS...]" << std::endl;
    std::cout << "Args syntax: TYPE:VALUE" << std::endl;
    std::cout << "Available types: u32, i32, u64, i64, str, f64, ptr" << std::endl;
    return 0;
  }

  std::string fmt_str(argv[1], strlen(argv[1]));
  Arg args[16];
  uint32_t args_size = 0;

  for (int i = 2; i < argc; i++) {
    char *c = argv[i];
    size_t c_len = strlen(c);
    if (c_len > 5) {
      Arg *a = &args[i - 2];
      if (!strncmp(c, "u32:", 4)) {
#if __WORD_SIZE == 32
        a->type = Arg::Type::U32;
        a->value.u32 = strtoul(c+4, nullptr, 10);
#else
        a->type = Arg::Type::U64;
        a->value.u64 = strtoul(c+4, nullptr, 10);
#endif
      } else if (!strncmp(c, "i32:", 4)) {
#if __WORD_SIZE == 32
        a->type = Arg::Type::I32;
        a->value.i32 = strtol(c+4, nullptr, 10);
#else
        a->type = Arg::Type::I64;
        a->value.i64 = strtol(c+4, nullptr, 10);
#endif
      } else if (!strncmp(c, "u64:", 4)) {
        a->type = Arg::Type::U64;
        a->value.u64 = strtoull(c+4, nullptr, 10);
      } else if (!strncmp(c, "i64:", 4)) {
        a->type = Arg::Type::I64;
        a->value.i64 = strtoll(c+4, nullptr, 10);
      } else if (!strncmp(c, "str:", 4)) {
        a->type = Arg::Type::S;
        a->value.s.begin = c+4;
        a->value.s.size = c_len-4;
      } else if (!strncmp(c, "f64:", 4)) {
        a->type = Arg::Type::D;
        a->value.d = strtod(c+4, nullptr);
      } else if (!strncmp(c, "ptr:", 4)) {
        a->type = Arg::Type::P;
        a->value.p = reinterpret_cast<void*>(strtoul(c+4, nullptr, 16));
      } else {
        std::cout << "Invalid argument: " << c << std::endl;
        return 1;
      }
    } else {
      std::cout << "Invalid argument: " << c << std::endl;
      return 1;
    }
    args_size++;
  }

  std::cout << "FORMAT_STRING: " << fmt_str << std::endl;
  std::cout << "ARGS:" << std::endl;
  for (uint32_t i = 0; i < args_size; i++) {
    Arg *a = &args[i];
    std::cout << "  ";
    switch (a->type) {
    case Arg::Type::S:
      std::cout << std::string(a->value.s.begin, a->value.s.size);
      break;
#if __WORD_SIZE == 32
    case Arg::Type::U32:
      std::cout << a->value.u32;
      break;
    case Arg::Type::I32:
      std::cout << a->value.i32;
      break;
#endif
    case Arg::Type::U64:
      std::cout << a->value.u64;
      break;
    case Arg::Type::I64:
      std::cout << a->value.i64;
      break;
    case Arg::Type::D:
      std::cout << a->value.d;
      break;
    case Arg::Type::P:
      std::cout << a->value.p;
      break;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  try {
    char buf[1024];
    uint32_t size = fmt::vformat(buf, fmt_str.c_str(), fmt_str.size(), args, args_size);
    std::cout << std::string(buf, size) << std::endl;
    return 0;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
    return 2;
  }
}
