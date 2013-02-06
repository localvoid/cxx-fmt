#ifndef _FMT_FORMAT_HPP_
#define _FMT_FORMAT_HPP_

#include <stdexcept>
#include <string>
#include <fmt/format-base.hpp>
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
  struct Data : public FormatBase::Data {
    ArgOptions arg_options;
    int32_t arg_index = 0;
  };

  void capture_precision(Data &d, const char *fpc) {
    d.arg_options.precision = capture_integer(d, fpc);
  }

  void capture_width(Data &d, const char *fpc) {
    d.arg_options.width = capture_integer(d, fpc);
  }

  void capture_argument(Data &d, const char *fpc) {
    d.arg_options.index = capture_integer(d, fpc) + 1;
  }

  void set_flag(Data &d, fmt::Flag v) {
    d.arg_options.flags |= v;
  }

  void emit_text(Data &d, const char *end) {
    std::cout << std::string(d.mark, end - d.mark);
  }

  void emit_open_bracket(Data &d) {
    std::cout << std::string("{");
  }

  void emit_argument(Data &d, const Arg *args, size_t args_size) {
    uint32_t index;

    if (d.arg_options.index == 0) {
      if (d.arg_index == -1) {
        throw InvalidFormatString("Invalid indexing behaviour");
      }
      index = d.arg_index++;
    } else {
      if (d.arg_index > 0) {
        throw InvalidFormatString("Invalid indexing behaviour");
      }
      if (d.arg_index == 0) {
        d.arg_index = -1;
      }
      index = d.arg_options.index - 1;
    }

    if (index >= args_size) {
      throw InvalidFormatString("Argument index is out of range");
    }

    char tmp_buf[32];
    uint32_t size;

    const Arg *a = &args[index];
    switch (a->type) {
    case Arg::Type::S:
      std::cout << std::string(a->value.s.begin, a->value.s.size);
      break;
    case Arg::Type::U32:
      size = itoa(a->value.u32, d.arg_options.width, d.arg_options.flags, tmp_buf);
      std::cout << std::string(tmp_buf, size);
      break;
    case Arg::Type::I32:
      size = itoa(a->value.i32, d.arg_options.width, d.arg_options.flags, tmp_buf);
      std::cout << std::string(tmp_buf, size);
      break;
    case Arg::Type::U64:
      size = itoa(a->value.i64, d.arg_options.width, d.arg_options.flags, tmp_buf);
      std::cout << std::string(tmp_buf, size);
      break;
    case Arg::Type::I64:
      size = itoa(a->value.u64, d.arg_options.width, d.arg_options.flags, tmp_buf);
      std::cout << std::string(tmp_buf, size);
      break;
    case Arg::Type::F:
      size = dtoa(a->value.f, d.arg_options.width, d.arg_options.precision, d.arg_options.flags, tmp_buf);
      std::cout << std::string(tmp_buf, size);
      break;
    case Arg::Type::D:
      size = dtoa(a->value.d, d.arg_options.width, d.arg_options.precision, d.arg_options.flags, tmp_buf);
      std::cout << std::string(tmp_buf, size);
      break;
    case Arg::Type::P:
      size = itoa_hex(reinterpret_cast<uint64_t>(a->value.p), d.arg_options.width, d.arg_options.flags, tmp_buf);
      std::cout << std::string(tmp_buf, size);
      break;
    }

    d.arg_options.reset();
  }

  void argument_error(Data &d) {
    throw InvalidFormatString("argument_error()");
  }

  void end_error(Data &d) {
    throw InvalidFormatString("end_error()");
  }
};

};

#endif
