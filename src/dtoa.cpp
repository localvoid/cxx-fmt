#include <stdio.h>
#include <cstdint>

#include <fmt/itoa.hpp>


uint32_t fmt::dtoa(double n, uint32_t width, uint32_t precision, uint32_t flags, char *b) {
  char fmt[8];
  uint32_t p = 0;
  fmt[p++] = '%';

  if (flags & fmt::Flag::SignPlus)    fmt[p++] = '+';
  if (flags & fmt::Flag::SignSpace)   fmt[p++] = ' ';
  if (flags & fmt::Flag::AlignLeft)   fmt[p++] = '-';
  if (flags & fmt::Flag::ZeroPadding) fmt[p++] = '0';
  if (width > 0)                      fmt[p++] = '*';
  if (precision > 0)                  fmt[p++] = '.';

  if (flags & fmt::Flag::Exponent)           fmt[p++] = 'e';
  else if (flags & fmt::Flag::UpperExponent) fmt[p++] = 'E';
  else                                       fmt[p++] = 'f';

  fmt[p] = '\0';

  if (width > 0) {
    if (precision > 0)
      return sprintf(b, fmt, width, precision, n);
    else
      return sprintf(b, fmt, width, n);
  } else {
    if (precision > 0)
      return sprintf(b, fmt, precision, n);
    else
      return sprintf(b, fmt, n);
  }
}
