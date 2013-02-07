#ifndef _FMT_FORMAT_HPP_
#define _FMT_FORMAT_HPP_

#include <climits>
#include <stdexcept>
#include <string.h>

#include <fmt/flag.hpp>
#include <fmt/itoa.hpp>

namespace fmt {

class InvalidFormatString : public std::invalid_argument {
public:
  InvalidFormatString(const std::string& msg = "") : std::invalid_argument(msg) {}
};

struct StringRef {
  const char *begin;
  size_t      size;
};

struct Arg {
  union {
#if __WORDSIZE == 32
    uint32_t  u32;
    int32_t   i32;
#endif
    uint64_t  u64;
    int64_t   i64;
    double    d;
    StringRef s;
    void     *p;
  } value;

  enum class Type {
    S,
#if __WORDSIZE == 32
    U32,
    I32,
#endif
    U64,
    I64,
    D,
    P
  } type;
};

#if __WORDSIZE == 32
inline Arg to_arg(uint8_t o) {
  return { .value = { .u32 = o }, .type = Arg::Type::U32 };
}
inline Arg to_arg(int8_t o) {
  return { .value = { .i32 = o }, .type = Arg::Type::I32 };
}
inline Arg to_arg(uint16_t o) {
  return { .value = { .u32 = o }, .type = Arg::Type::U32 };
}
inline Arg to_arg(int16_t o) {
  return { .value = { .i32 = o }, .type = Arg::Type::I32 };
}
inline Arg to_arg(uint32_t o) {
  return { .value = { .u32 = o }, .type = Arg::Type::U32 };
}
inline Arg to_arg(int32_t o) {
  return { .value = { .i32 = o }, .type = Arg::Type::I32 };
}
#else
inline Arg to_arg(uint8_t o) {
  return { .value = { .u64 = o }, .type = Arg::Type::U64 };
}
inline Arg to_arg(int8_t o) {
  return { .value = { .i64 = o }, .type = Arg::Type::I64 };
}
inline Arg to_arg(uint16_t o) {
  return { .value = { .u64 = o }, .type = Arg::Type::U64 };
}
inline Arg to_arg(int16_t o) {
  return { .value = { .i64 = o }, .type = Arg::Type::I64 };
}
inline Arg to_arg(uint32_t o) {
  return { .value = { .u64 = o }, .type = Arg::Type::U64 };
}
inline Arg to_arg(int32_t o) {
  return { .value = { .i64 = o }, .type = Arg::Type::I64 };
}
#endif
inline Arg to_arg(uint64_t o) {
  return { .value = { .u64 = o }, .type = Arg::Type::U64 };
}
inline Arg to_arg(int64_t o) {
  return { .value = { .i64 = o }, .type = Arg::Type::I64 };
}
inline Arg to_arg(float o) {
  return { .value = { .d = o }, .type = Arg::Type::D };
}
inline Arg to_arg(double o) {
  return { .value = { .d = o }, .type = Arg::Type::D };
}

template<std::size_t size>
Arg to_arg(const char (&str)[size]) {
  Arg a;
  a.value.s = { static_cast<const char*>(str), size };
  a.type = Arg::Type::S;
  return std::move(a);
}

uint32_t vformat(char *buf, const char *fstr, uint32_t fstr_size, Arg *args, uint32_t args_size);

template<typename ...Args>
uint32_t format(char *buf, const char *format_str, Args&& ... args) {
  Arg arglist[] = { to_arg(std::forward<Args>(args))... };

  return vformat(buf, format_str, strlen(format_str), arglist, sizeof...(args));
}


};

#endif
