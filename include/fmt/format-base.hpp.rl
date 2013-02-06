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
      '<' @{ static_cast<T&>(*this).set_flag(data, Flag::AlignLeft); }
    | '>' @{ static_cast<T&>(*this).set_flag(data, Flag::AlignRight); }
  );

  sign = (
      '+' @{ static_cast<T&>(*this).set_flag(data, Flag::SignPlus); }
    | ' ' @{ static_cast<T&>(*this).set_flag(data, Flag::SignSpace); }
  );

  type = (
      'c' @{ static_cast<T&>(*this).set_flag(data, Flag::Char); }
    | 'e' @{ static_cast<T&>(*this).set_flag(data, Flag::Exponent); }
    | 'f' @{ static_cast<T&>(*this).set_flag(data, Flag::Fixed); }
    | 'x' @{ static_cast<T&>(*this).set_flag(data, Flag::Hex); }
    | 'E' @{ static_cast<T&>(*this).set_flag(data, Flag::UpperExponent); }
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

  options = (
    ':'
    flags*
    width?
    precision?
  );

  argid = digit+ >Mark %CaptureArgument;

  field = (
      argid
    | argid options
    | options
  );

  text = [^{]+ >Mark %EmitText;
  open_bracket = '{' '{' @EmitOpenBracket;
  argument = '{' field? $!ArgumentError '}' @EmitArgument;

  main := (
      text
    | open_bracket
    | argument
  )**;

}%%


#include <cstdint>
#include <utility>

namespace fmt {

enum Flag : uint32_t {
  AlignLeft      = 1,
  AlignRight     = 1 << 1,
  SignPlus       = 1 << 2,
  SignSpace      = 1 << 3,
  Char           = 1 << 4,
  Hex            = 1 << 5,
  UpperHex       = 1 << 6,
  Exponent       = 1 << 7,
  UpperExponent  = 1 << 8,
  Fixed          = 1 << 9,
  LargeExponent  = 1 << 10,
  Percentage     = 1 << 11,
  Prefixed       = 1 << 12,
  ZeroPadding    = 1 << 13,
  CommaSeparator = 1 << 14
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
