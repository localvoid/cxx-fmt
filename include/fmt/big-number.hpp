#ifndef _FMT_BIG_NUMBER_HPP_
#define _FMT_BIG_NUMBER_HPP_

#include <array>
#include <cstdint.h>
#include <climits>

namespace fmt {

class BigNumber {
public:
  BigNumber() : used_ = 0 {
    for (auto &d : digits_) {
      d = 0;
    }
  }

private:
#if __WORD_SIZE == 32
  using Digit = uint32_t;
  using DoubleDigit = uint64_t;
#else
  using Digit = uint64_t;
  using DoubleDigit = unsigned __int64_t;
#endif

  static constexpr int Max_Significant_Bits = 128 * 32;
  static constexpr int Digit_Size = sizeof(Digit);
  static constexpr int Digit_Capacity = Max_Significant_Bits / Digit_Size;

  std::array<Digit, Digit_Capacity> digits_;
  int32_t used_;
};

}

#endif
