%%{
  machine format;

  action Mark              { mark = fpc; }
  action EmitText          { emit_text(mark, fpc); }
  action EmitOpenBracket   { emit_open_bracket(); }
  action EmitArgument      { emit_argument(); }
  action CaptureArgument   { arg_.index = capture_integer(mark, fpc); }
  action CaptureWidth      { arg_.width = capture_integer(mark, fpc); }
  action CapturePrecision  { arg_.precision = capture_integer(mark, fpc); }
  action FlagAlignLeft     { arg_.flags |= fmt::Flag::AlignLeft; }
  action FlagAlignRight    { arg_.flags |= fmt::Flag::AlignRight; }
  action FlagSignPlus      { arg_.flags |= fmt::Flag::SignPlus; }
  action FlagSignSpace     { arg_.flags |= fmt::Flag::SignSpace; }
  action FlagChar          { arg_.flags |= fmt::Flag::Char; }
  action FlagExponent      { arg_.flags |= fmt::Flag::Exponent; }
  action FlagFixed         { arg_.flags |= fmt::Flag::Fixed; }
  action FlagHex           { arg_.flags |= fmt::Flag::Hex; }
  action FlagUpperHex      { arg_.flags |= fmt::Flag::UpperHex; }
  action FlagLargeExponent { arg_.flags |= fmt::Flag::LargeExponent; }
  action FlagUpperExponent { arg_.flags |= fmt::Flag::UpperExponent; }
  action FlagPercentage    { arg_.flags |= fmt::Flag::Percentage; }
  action FlagPrefixed      { arg_.flags |= fmt::Flag::Prefixed; }
  action FlagZeroPadding   { arg_.flags |= fmt::Flag::ZeroPadding; }
  action FlagComma         { arg_.flags |= fmt::Flag::Comma; }
  action ArgumentError     { throw InvalidFormatString("argument_error()"); }
  action EndError          { throw InvalidFormatString("end_error()"); }

  include format_spec "../ragel/format-spec.rl";

}%%

#include <cstdint>
#include <iostream>
#include <string.h>

#include <fmt/format.hpp>

namespace {

using namespace fmt;

struct ArgOptions {
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

int capture_integer(const char *p, const char *fpc) {
  int i = 0;
  while (p != fpc) {
    i = i * 10 + (*p - '0');
    p++;
  }
  return i;
}

class Format {
public:
  Format(char *buf, Arg *args, uint32_t args_size)
      : buf_(buf), args_(args), args_size_(args_size) {}


  uint32_t operator()(const char *fstr, uint32_t fstr_size) {
    int cs = 0;
    const char *p = fstr;
    const char *pe = &fstr[fstr_size];
    const char *eof = pe;
    const char *mark = nullptr;

    for(;;) {
      %% write exec;
      if (p == eof || cs == %%{ write error; }%%)
        break;
    }
    return size_;
  }

protected:
  void emit_text(const char *mark, const char *fpc) {
    uint32_t size = fpc - mark;
    memcpy(&buf_[size_], mark, size);
    size_ += size;
  }

  void emit_open_bracket() {
    buf_[size_] = '{';
    size_ += 1;
  }

  void emit_argument() {
    uint32_t index;

    if (arg_.index == 0) {
      if (index_ == -1)
        throw InvalidFormatString("Invalid indexing behaviour");
      index = index_++;
    } else {
      if (index_ > 0)
        throw InvalidFormatString("Invalid indexing behaviour");
      if (index_ == 0)
        index_ = -1;
      index = index_ - 1;
    }

    if (index >= args_size_)
      throw InvalidFormatString("Argument index is out of range");

    char *c = &buf_[size_];
    const Arg *a = &args_[index];

    switch (a->type) {
    case Arg::Type::S:
      size_ += a->value.s.size;
      memcpy(c, a->value.s.begin, a->value.s.size);
      break;
    #if __WORDSIZE == 32
    case Arg::Type::U32:
      if (d.arg_options.flags & (Flag::Hex | Flag::UpperHex))
        size_ += itoa_hex(a->value.u32, arg_.width, arg_.flags, c);
      else
        size_ += itoa(a->value.u32, arg_.width, arg_.flags, c);
      break;
    case Arg::Type::I32:
      if (d.arg_options.flags & (Flag::Hex | Flag::UpperHex))
        size_ += itoa_hex(a->value.u32, arg_.width, arg_.flags, c);
      else
        size_ += itoa(a->value.i32, arg_.width, arg_.flags, c);
      break;
    #endif
    case Arg::Type::U64:
      if (arg_.flags & (Flag::Hex | Flag::UpperHex))
        size_ += itoa_hex(a->value.u64, arg_.width, arg_.flags, c);
      else
        size_ += itoa(a->value.i64, arg_.width, arg_.flags, c);
      break;
    case Arg::Type::I64:
      if (arg_.flags & (Flag::Hex | Flag::UpperHex))
        size_ += itoa_hex(a->value.u64, arg_.width, arg_.flags, c);
      else
        size_ += itoa(a->value.i64, arg_.width, arg_.flags, c);
      break;
    case Arg::Type::D:
      size_ += dtoa(a->value.d, arg_.width, arg_.precision, arg_.flags, c);
      break;
    case Arg::Type::P:
      size_ += itoa_hex(reinterpret_cast<uint64_t>(a->value.p), arg_.width, arg_.flags, c);
      break;
    }

    arg_.reset();
  }

private:
  ArgOptions arg_;
  char      *buf_;
  Arg       *args_;
  uint32_t   args_size_;
  uint32_t   size_ = 0;
  int32_t    index_ = 0;
};


%% write data;

}

uint32_t fmt::vformat(char *buf, const char *fstr, uint32_t fstr_size, Arg *args, uint32_t args_size) {
  Format f(buf, args, args_size);
  return f(fstr, fstr_size);
}
