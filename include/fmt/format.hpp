#ifndef _FMT_FORMAT_HPP_
#define _FMT_FORMAT_HPP_

#include <stdexcept>
#include <string>
#include <fmt/format-base.hpp>

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
    uint32_t  u32;
    int32_t   i32;
    uint64_t  u64;
    int64_t   i64;
    float     f;
    double    d;
    StringRef s;
    void     *p;
  } value;

  enum class Type {
    S,
    U32,
    I32,
    U64,
    I64,
    F,
    D,
    P
  } type;
};

Arg to_arg(uint8_t o) {
  return { .value = { .u32 = o }, .type = Arg::Type::U32 };
}
Arg to_arg(int8_t o) {
  return { .value = { .i32 = o }, .type = Arg::Type::I32 };
}
Arg to_arg(uint16_t o) {
  return { .value = { .u32 = o }, .type = Arg::Type::U32 };
}
Arg to_arg(int16_t o) {
  return { .value = { .i32 = o }, .type = Arg::Type::I32 };
}
Arg to_arg(uint32_t o) {
  return { .value = { .u32 = o }, .type = Arg::Type::U32 };
}
Arg to_arg(int32_t o) {
  return { .value = { .i32 = o }, .type = Arg::Type::I32 };
}
Arg to_arg(uint64_t o) {
  return { .value = { .u64 = o }, .type = Arg::Type::U64 };
}
Arg to_arg(int64_t o) {
  return { .value = { .i64 = o }, .type = Arg::Type::I64 };
}
Arg to_arg(float o) {
  return { .value = { .f = o }, .type = Arg::Type::F };
}
Arg to_arg(double o) {
  return { .value = { .d = o }, .type = Arg::Type::D };
}

template<std::size_t size>
Arg to_arg(const char (&str)[size]) {
  Arg a;
  a.value.s = { static_cast<const char*>(str), size };
  a.type = Arg::Type::S;
  return std::move(a);
}


class ArgOptions {
public:
  void reset() {
    index = 0;
    width = 0;
    precision = 0;
    flags = 0;
  }

  uint32_t index = 0;
  uint32_t width = 0;
  uint32_t precision = 0;
  uint32_t flags = 0;
};

class Format : public FormatBase<Format> {
public:
  Format(std::string &f) : FormatBase(f.c_str(), f.size()) {}

  void mark(const char *fpc) {
    mark_ = fpc;
  }

  int capture_integer(const char *fpc) {
    int i = 0;
    const char *xp = mark_;

    while (xp != fpc) {
      i = i * 10 + (*xp - '0');
      xp++;
    }
    return i;
  }

  void capture_precision(const char *fpc) {
    arg_options_.precision = capture_integer(fpc);
  }

  void capture_width(const char *fpc) {
    arg_options_.width = capture_integer(fpc);
  }

  void capture_argument(const char *fpc) {
    arg_options_.index = capture_integer(fpc) + 1;
  }

  void set_flag(fmt::Flag v) {
    arg_options_.flags |= v;
  }

  void emit_text(const char *end) {
    std::cout << std::string(mark_, end - mark_);
  }

  void emit_open_bracket() {
    std::cout << std::string("{");
  }

  void emit_argument(const Arg *args, size_t args_size) {
    uint32_t index;

    if (arg_options_.index == 0) {
      index = arg_index_++;
    } else {
      if (arg_index_ != 0) {
        throw InvalidFormatString("Invalid indexing behaviour");
      }
      index = arg_options_.index;
    }

    if (index >= args_size) {
      throw InvalidFormatString("Argument index is out of range");
    }

    const Arg *a = &args[index];
    switch (a->type) {
    case Arg::Type::S:
      std::cout << std::string(a->value.s.begin, a->value.s.size);
      break;
    case Arg::Type::U32:
      std::cout << a->value.u32;
      break;
    case Arg::Type::I32:
      std::cout << a->value.i32;
      break;
    case Arg::Type::U64:
      std::cout << a->value.u64;
      break;
    case Arg::Type::I64:
      std::cout << a->value.i64;
      break;
    case Arg::Type::F:
      std::cout << a->value.f;
      break;
    case Arg::Type::D:
      std::cout << a->value.d;
      break;
    case Arg::Type::P:
      std::cout << a->value.p;
      break;
    }

    arg_options_.reset();
  }

  void argument_error() {
    throw InvalidFormatString("argument_error()");
  }

  void end_error() {
    throw InvalidFormatString("end_error()");
  }

private:
  const char *mark_;
  ArgOptions arg_options_;
  uint32_t arg_index_ = 0;
};

};

#endif
