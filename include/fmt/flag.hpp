#ifndef _FMT_FLAG_HPP_
#define _FMT_FLAG_HPP_

namespace fmt {

enum Flag : uint32_t {
  AlignLeft     = 1,
  AlignRight    = 1 << 1,
  SignPlus      = 1 << 2,
  SignSpace     = 1 << 3,
  Char          = 1 << 4,
  Hex           = 1 << 5,
  UpperHex      = 1 << 6,
  Exponent      = 1 << 7,
  UpperExponent = 1 << 8,
  Fixed         = 1 << 9,
  LargeExponent = 1 << 10,
  Percentage    = 1 << 11,
  Prefixed      = 1 << 12,
  ZeroPadding   = 1 << 13,
  Comma         = 1 << 14
};

}

#endif
