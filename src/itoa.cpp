#include <string.h>
#include <cstdint>
#include <cstdlib>
#include <algorithm>

#include <fmt/itoa.hpp>

namespace {

const char hex_lower_digits[] = "0123456789abcdef";
const char hex_upper_digits[] = "0123456789ABCDEF";


const uint64_t powers_of_10_u64[] = {
  0,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
  10000000,
  100000000,
  1000000000,
  10000000000,
  100000000000,
  1000000000000,
  10000000000000,
  100000000000000,
  1000000000000000,
  10000000000000000,
  100000000000000000,
  1000000000000000000,
  10000000000000000000U
};

const uint32_t powers_of_10_u32[] = {
  0,
  10,
  100,
  1000,
  10000,
  100000,
  1000000,
  10000000,
  100000000,
  1000000000
};

const char digit_pairs[201] = {
  "00010203040506070809"
  "10111213141516171819"
  "20212223242526272829"
  "30313233343536373839"
  "40414243444546474849"
  "50515253545556575859"
  "60616263646566676869"
  "70717273747576777879"
  "80818283848586878889"
  "90919293949596979899"
};

inline unsigned long bsrq(unsigned long mask) {
  unsigned long result;
  asm volatile("bsrq %1,%0" : "=r" (result) : "rm" (mask));
  return result;
}

inline unsigned int bsrl(unsigned int mask) {
  unsigned int result;
  asm volatile("bsrl %1,%0" : "=r" (result) : "rm" (mask));
  return result;
}

inline uint32_t digits10(uint64_t n) {
  uint32_t t = (bsrq(n | 1) + 1) * 1233 >> 12;
  return t - (n < powers_of_10_u64[t]) + 1;
}

inline uint32_t digits10(uint32_t n) {
  uint32_t t = (bsrl(n | 1) + 1) * 1233 >> 12;
  return t - (n < powers_of_10_u32[t]) + 1;
}

inline uint32_t digits16(uint64_t n) {
  return (bsrq(n | 1) + 1) / 4;
}

inline uint32_t digits16(uint32_t n) {
  return (bsrl(n | 1) + 1) / 4;
}

}

uint32_t fmt::itoa(int64_t n, uint32_t width, uint32_t flags, char *b) {
  int32_t sign = -(n<0);
  uint64_t v = (n^sign)-sign;
  char *c;

  uint32_t size = digits10(v);

  uint32_t inc = -sign;
  if (flags & (Flag::SignPlus | Flag::SignSpace)) {
    inc |= 1;
  }
  size += inc;

  if (width > size) {
    if (flags & Flag::AlignLeft) {
      c = &b[size - 1];
      std::fill(b + size, b + width, ' ');
    } else {
      c = &b[width-1];

      const char f = (flags & Flag::ZeroPadding) ? '0' : ' ';
      std::fill(b, b + width - size + 1, f);
    }
    size = width;


  } else {
    c = &b[size-1];
  }


  while (v >= 100) {
    auto const r = v % 100;
    v /= 100;
    memcpy(c-1, digit_pairs+2*r, 2);
    c -= 2;
  }
  if (v < 10) {
    *c-- = '0' + v;
  } else {
    memcpy(c-1, digit_pairs+2*v, 2);
    c -= 2;
  }

  if (flags & Flag::ZeroPadding) c = b;

  if (sign)                         *c = '-';
  else if (flags & Flag::SignPlus)  *c = '+';
  else if (flags & Flag::SignSpace) *c = ' ';

  return size;
}

uint32_t fmt::itoa(uint64_t v, uint32_t width, uint32_t flags, char *b) {
  char *c;
  uint32_t size = digits10(v);

  if (flags & (Flag::SignPlus | Flag::SignSpace)) {
    size += 1;
  }

  if (width > size) {
    if (flags & Flag::AlignLeft) {
      c = &b[size - 1];
      std::fill(b + size, b + width, ' ');
    } else {
      c = &b[width-1];

      const char f = (flags & Flag::ZeroPadding) ? '0' : ' ';
      std::fill(b, b + width - size + 1, f);
    }
    size = width;


  } else {
    c = &b[size-1];
  }


  while (v >= 100) {
    auto const r = v % 100;
    v /= 100;
    memcpy(c-1, digit_pairs+2*r, 2);
    c -= 2;
  }
  if (v < 10) {
    *c-- = '0' + v;
  } else {
    memcpy(c-1, digit_pairs+2*v, 2);
    c -= 2;
  }

  if (flags & Flag::ZeroPadding) c = b;

  if (flags & Flag::SignPlus)       *c = '+';
  else if (flags & Flag::SignSpace) *c = ' ';

  return size;
}

uint32_t fmt::itoa(int32_t n, uint32_t width, uint32_t flags, char *b) {
  int32_t sign = -(n<0);
  uint32_t v = (n^sign)-sign;
  char *c;

  uint32_t size = digits10(v);

  uint32_t inc = -sign;
  if (flags & (Flag::SignPlus | Flag::SignSpace)) {
    inc |= 1;
  }
  size += inc;

  if (width > size) {
    if (flags & Flag::AlignLeft) {
      c = &b[size - 1];
      std::fill(b + size, b + width, ' ');
    } else {
      c = &b[width-1];

      const char f = (flags & Flag::ZeroPadding) ? '0' : ' ';
      std::fill(b, b + width - size + 1, f);
    }
    size = width;


  } else {
    c = &b[size-1];
  }


  while (v >= 100) {
    auto const r = v % 100;
    v /= 100;
    memcpy(c-1, digit_pairs+2*r, 2);
    c -= 2;
  }
  if (v < 10) {
    *c-- = '0' + v;
  } else {
    memcpy(c-1, digit_pairs+2*v, 2);
    c -= 2;
  }

  if (flags & Flag::ZeroPadding) c = b;

  if (sign)                         *c = '-';
  else if (flags & Flag::SignPlus)  *c = '+';
  else if (flags & Flag::SignSpace) *c = ' ';

  return size;
}

uint32_t fmt::itoa(uint32_t v, uint32_t width, uint32_t flags, char *b) {
  char *c;
  uint32_t size = digits10(v);

  if (flags & (Flag::SignPlus | Flag::SignSpace)) {
    size += 1;
  }

  if (width > size) {
    if (flags & Flag::AlignLeft) {
      c = &b[size - 1];
      std::fill(b + size, b + width, ' ');
    } else {
      c = &b[width-1];

      const char f = (flags & Flag::ZeroPadding) ? '0' : ' ';
      std::fill(b, b + width - size + 1, f);
    }
    size = width;


  } else {
    c = &b[size-1];
  }


  while (v >= 100) {
    auto const r = v % 100;
    v /= 100;
    memcpy(c-1, digit_pairs+2*r, 2);
    c -= 2;
  }
  if (v < 10) {
    *c-- = '0' + v;
  } else {
    memcpy(c-1, digit_pairs+2*v, 2);
    c -= 2;
  }

  if (flags & Flag::ZeroPadding) c = b;

  if (flags & Flag::SignPlus)       *c = '+';
  else if (flags & Flag::SignSpace) *c = ' ';

  return size;
}

uint32_t fmt::itoa_hex(uint32_t v, uint32_t width, uint32_t flags, char *b) {
  char *c;
  uint32_t size = digits16(v);

  if (flags & Flag::Prefixed)
    size += 2;

  if (width > size) {
    if (flags & Flag::AlignLeft) {
      c = &b[size - 1];
      std::fill(b + size, b + width, ' ');
    } else {
      c = &b[width-1];

      const char f = (flags & Flag::ZeroPadding) ? '0' : ' ';
      std::fill(b, b + width - size + 1, f);
    }
    size = width;
  } else {
    c = &b[size-1];
  }

  const char *digits = (flags & Flag::UpperHex) ? hex_upper_digits : hex_lower_digits;

  while (v >= 16) {
    auto const r = v % 16;
    v /= 16;
    *c-- = digits[r];
  }

  if (flags & Flag::ZeroPadding) c = b;

  if (flags & Flag::Prefixed) {
    c[0] = '0';
    c[1] = 'x';
  }

  return size;
}

uint32_t fmt::itoa_hex(uint64_t v, uint32_t width, uint32_t flags, char *b) {
  char *c;
  uint32_t size = digits16(v);

  if (flags & Flag::Prefixed)
    size += 2;

  if (width > size) {
    if (flags & Flag::AlignLeft) {
      c = &b[size - 1];
      std::fill(b + size, b + width, ' ');
    } else {
      c = &b[width-1];

      const char f = (flags & Flag::ZeroPadding) ? '0' : ' ';
      std::fill(b, b + width - size + 1, f);
    }
    size = width;
  } else {
    c = &b[size-1];
  }

  const char *digits = (flags & Flag::UpperHex) ? hex_upper_digits : hex_lower_digits;

  while (v >= 16) {
    auto const r = v % 16;
    v /= 16;
    *c-- = digits[r];
  }

  if (flags & Flag::ZeroPadding) c = b;

  if (flags & Flag::Prefixed) {
    c[0] = '0';
    c[1] = 'x';
  }

  return size;
}
