#ifndef _FMT_FORMAT_BASE_HPP_
#define _FMT_FORMAT_BASE_HPP_

%%{
  machine format;

  action Mark             { static_cast<T&>(*this).mark(fpc); }
  action EmitText         { static_cast<T&>(*this).emit_text(fpc); }
  action EmitOpenBracket  { static_cast<T&>(*this).emit_open_bracket(); }
  action EmitArgument     { static_cast<T&>(*this).emit_argument(std::forward<Args>(args)...); }
  action CaptureArgument  { static_cast<T&>(*this).capture_argument(fpc); }
  action CaptureWidth     { static_cast<T&>(*this).capture_width(fpc); }
  action CapturePrecision { static_cast<T&>(*this).capture_precision(fpc); }
  action ArgumentError    { static_cast<T&>(*this).argument_error(); }
  action EndError         { static_cast<T&>(*this).end_error(); }

  align = (
      '>' @{ static_cast<T&>(*this).set_flag(Flag::AlignRight); }
    | '<' @{ static_cast<T&>(*this).set_flag(Flag::AlignLeft); }
    | '^' @{ static_cast<T&>(*this).set_flag(Flag::AlignCentered); }
    | '=' @{ static_cast<T&>(*this).set_flag(Flag::AlignNumeric); }
  );

  sign = (
      '+' @{ static_cast<T&>(*this).set_flag(Flag::SignPlus); }
    | ' ' @{ static_cast<T&>(*this).set_flag(Flag::SignSpace); }
  );

  type = (
      'c' @{ static_cast<T&>(*this).set_flag(Flag::Char); }
    | 'e' @{ static_cast<T&>(*this).set_flag(Flag::Exponent); }
    | 'f' @{ static_cast<T&>(*this).set_flag(Flag::Fixed); }
    | 'n' @{ static_cast<T&>(*this).set_flag(Flag::Localized); }
    | 'o' @{ static_cast<T&>(*this).set_flag(Flag::Octal); }
    | 'x' @{ static_cast<T&>(*this).set_flag(Flag::Hex); }
    | 'E' @{ static_cast<T&>(*this).set_flag(Flag::UpperExponent); }
    | 'F' @{ static_cast<T&>(*this).set_flag(Flag::Fixed); }
    | 'G' @{ static_cast<T&>(*this).set_flag(Flag::LargeExponent); }
    | 'X' @{ static_cast<T&>(*this).set_flag(Flag::UpperHex); }
    | '%' @{ static_cast<T&>(*this).set_flag(Flag::Percentage); }
  );

  misc = (
      '#' @{ static_cast<T&>(*this).set_flag(Flag::Prefixed); }
    | '0' @{ static_cast<T&>(*this).set_flag(Flag::ZeroPadding); }
    | ',' @{ static_cast<T&>(*this).set_flag(Flag::CommaSeparator); }
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
  argument = '{' field? $^ArgumentError '}' @EmitArgument;

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
  FormatBase() {}

  FormatBase(const char *fmt,
             std::size_t fmt_size)
      : p(fmt),
        pe(fmt + fmt_size),
        eof(pe) {}

  template<typename ...Args>
  void operator()(Args&& ... args) {
    for(;;) {
      %% write exec;
      if (p == eof || cs == %%{ write error; }%%)
        break;
    }
  }

protected:
  int cs;
  const char *p;
  const char *pe;
  const char *eof;
};


}

#endif
