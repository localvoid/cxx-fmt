#ifndef _FMT_FORMAT_BASE_HPP_
#define _FMT_FORMAT_BASE_HPP_

%%{
  machine format;

  action Mark             { static_cast<T&>(*this).mark(data, fpc); }
  action EmitText         { static_cast<T&>(*this).emit_text(data, fpc); }
  action EmitOpenBracket  { static_cast<T&>(*this).emit_open_bracket(data); }
  action EmitArgument     { static_cast<T&>(*this).emit_argument(data, std::forward<Args>(args)...); }
  action CaptureArgument  { static_cast<T&>(*this).capture_argument(data, fpc); }
  action CaptureWidth     { static_cast<T&>(*this).capture_width(data, fpc); }
  action CapturePrecision { static_cast<T&>(*this).capture_precision(data, fpc); }
  action ArgumentError    { static_cast<T&>(*this).argument_error(data); }
  action EndError         { static_cast<T&>(*this).end_error(data); }

  align = (
      '>' @{ static_cast<T&>(*this).set_flag(data, Flag::AlignRight); }
    | '<' @{ static_cast<T&>(*this).set_flag(data, Flag::AlignLeft); }
    | '^' @{ static_cast<T&>(*this).set_flag(data, Flag::AlignCentered); }
    | '=' @{ static_cast<T&>(*this).set_flag(data, Flag::AlignNumeric); }
  );

  sign = (
      '+' @{ static_cast<T&>(*this).set_flag(data, Flag::SignPlus); }
    | ' ' @{ static_cast<T&>(*this).set_flag(data, Flag::SignSpace); }
  );

  type = (
      'c' @{ static_cast<T&>(*this).set_flag(data, Flag::Char); }
    | 'e' @{ static_cast<T&>(*this).set_flag(data, Flag::Exponent); }
    | 'f' @{ static_cast<T&>(*this).set_flag(data, Flag::Fixed); }
    | 'n' @{ static_cast<T&>(*this).set_flag(data, Flag::Localized); }
    | 'o' @{ static_cast<T&>(*this).set_flag(data, Flag::Octal); }
    | 'x' @{ static_cast<T&>(*this).set_flag(data, Flag::Hex); }
    | 'E' @{ static_cast<T&>(*this).set_flag(data, Flag::UpperExponent); }
    | 'F' @{ static_cast<T&>(*this).set_flag(data, Flag::Fixed); }
    | 'G' @{ static_cast<T&>(*this).set_flag(data, Flag::LargeExponent); }
    | 'X' @{ static_cast<T&>(*this).set_flag(data, Flag::UpperHex); }
    | '%' @{ static_cast<T&>(*this).set_flag(data, Flag::Percentage); }
  );

  misc = (
      '#' @{ static_cast<T&>(*this).set_flag(data, Flag::Prefixed); }
    | '0' @{ static_cast<T&>(*this).set_flag(data, Flag::ZeroPadding); }
    | ',' @{ static_cast<T&>(*this).set_flag(data, Flag::CommaSeparator); }
  );

  flags = (
      align
    | sign
    | type
    | misc
  );

  width = 'w' digit+ >Mark %CaptureWidth;
  precision = '.' digit+ >Mark %CapturePrecision;

  compound_options = (
      width
    | precision
  );

  options = (
    ':'
    flags*
    compound_options*
  );

  argid = digit+ >Mark %CaptureArgument;

  field = (
      argid
    | argid options
    | options
  );

  text = [^{]+ >Mark %EmitText;
  open_bracket = '{' '{' @EmitOpenBracket;
  argument = '{' field? <^ArgumentError '}' @EmitArgument;

  main := (
      text
    | open_bracket
    | argument
  )**;

}%%


#include <cstdint>

namespace fmt {

enum Flag : uint32_t {
  AlignLeft      = 1,
  AlignRight     = 1 << 1,
  AlignCentered  = 1 << 2,
  AlignNumeric   = 1 << 3,
  SignPlus       = 1 << 4,
  SignSpace      = 1 << 6,
  Localized      = 1 << 7,
  Char           = 1 << 9,
  Octal          = 1 << 10,
  Hex            = 1 << 11,
  UpperHex       = 1 << 12,
  Exponent       = 1 << 13,
  UpperExponent  = 1 << 14,
  Fixed          = 1 << 15,
  LargeExponent  = 1 << 16,
  Percentage     = 1 << 17,
  Prefixed       = 1 << 18,
  ZeroPadding    = 1 << 19,
  CommaSeparator = 1 << 20,
};


%% write data;


template<typename T>
class FormatBase {
public:
  struct Data {
    int cs = 0;
    const char *p;
    const char *pe;
    const char *eof;
    const char *mark;
  };

  void mark(Data &d, const char *fpc) {
    d.mark = fpc;
  }

  int capture_integer(Data &d, const char *fpc) {
    int i = 0;
    const char *p = d.mark;

    while (p != fpc) {
      i = i * 10 + (*p - '0');
      p++;
    }
    return i;
  }


  template<typename ...Args>
  void operator()(const char *fmt, size_t fmt_size, Args&& ... args) {
    typename T::Data data;

    data.p = fmt;
    data.pe = fmt + fmt_size;
    data.eof = data.pe;
    data.mark = nullptr;

    %% variable cs  data.cs;
    %% variable p   data.p;
    %% variable pe  data.pe;
    %% variable eof data.eof;

    for(;;) {
      %% write exec;
      if (data.p == data.eof || data.cs == %%{ write error; }%%)
        break;
    }
  }
};


}

#endif
