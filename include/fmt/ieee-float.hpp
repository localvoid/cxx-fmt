#ifndef _IEEE_FLOAT_HPP_
#define _IEEE_FLOAT_HPP_

#include <string.h>

namespace fmt {

template<class Dest, class Source>
inline Dest bit_cast(const Source& source) {
  static_assert((sizeof(Dest) == sizeof(Source)), "(sizeof(Dest) == sizeof(Source)");

  Dest dest;
  memmove(&dest, &source, sizeof(dest));
  return dest;
}

template <class Dest, class Source>
inline Dest bit_cast(Source* source) {
  return bit_cast<Dest>(reinterpret_cast<uintptr_t>(source));
}


template<typename T>
class IeeeFloatTraits {};


template<typename T>
class IeeeFloat {
public:
  using traits = IeeeFloatTraits<T>;

public:
  IeeeFloat() : d_(0) {}
  explicit IeeeFloat(typename traits::type v) : d_(bit_cast<typename traits::uint_type>(v)) {}
  explicit IeeeFloat(typename traits::uint_type v) : d_(v) {}

  typename traits::uint_type as_uint() const {
    return d_;
  }

  // Returns the next greater double. Returns +infinity on input +infinity.
  typename traits::type next() const {
    if (d_ == traits::Infinity) {
      return IeeeFloat(traits::Infinity).value();
    }
    if (sign() < 0 && significand() == 0) {
      // -0.0
      return 0.0;
    }
    if (sign() < 0) {
      return IeeeFloat(d_ - 1).value();
    } else {
      return IeeeFloat(d_ + 1).value();
    }
  }

  typename traits::type prev() const {
    if (d_ == (traits::Infinity | traits::Sign_Mask)) {
      return -IeeeFloat::infinity();
    }
    if (sign() < 0) {
      return IeeeFloat(d_ + 1).value();
    } else {
      if (significand() == 0) return -0.0;
      return IeeeFloat(d_ - 1).value();
    }
  }

  int exponent() const {
    if (is_denormal()) {
      return traits::Denormal_Exponent;
    }

    typename traits::uint_type d = as_uint();
    int biased_e = static_cast<int>((d & traits::Exponent_Mask) >> traits::Physical_Significand_Size);
    return biased_e - traits::Exponent_Bias;
  }

  typename traits::uint_type significand() const {
    typename traits::uint_type d = as_uint();
    typename traits::uint_type signif = d & traits::Significand_Mask;
    if (!is_denormal()) {
      return signif + traits::Hidden_Bit;
    } else {
      return signif;
    }
  }

  bool is_denormal() const {
    typename traits::uint_type d = as_uint();
    return (d & traits::Exponent_Mask) == 0;
  }

  // We consider denormals not to be special.
  // Hence only Infinity and NaN are special.
  bool is_special() const {
    typename traits::uint_type d = as_uint();
    return (d & traits::Exponent_Mask) == traits::Exponent_Mask;
  }

  bool is_nan() const {
    typename traits::uint_type d = as_uint();
    return ((d & traits::Exponent_Mask) == traits::Exponent_Mask) &&
      ((d & traits::Significand_Mask) != 0);
  }

  bool is_infinite() const {
    typename traits::uint_type d = as_uint();
    return ((d & traits::Exponent_Mask) == traits::Exponent_Mask) &&
      ((d & traits::Significand_Mask) == 0);
  }

  int sign() const {
    typename traits::uint_type d = as_uint();
    return (d & traits::Sign_Mask) == 0? 1: -1;
  }

  typename traits::type value() const {
    return bit_cast<typename traits::type>(d_);
  }

  static typename traits::type infinity() {
    return IeeeFloat(traits::Infinity).value();
  }
  static typename traits::type nan() {
    return IeeeFloat(traits::Nan).value();
  }


private:
  typename traits::uint_type d_;
};


template<>
class IeeeFloatTraits<double> {
public:
  static constexpr uint64_t Sign_Mask        = 0x8000000000000000U;
  static constexpr uint64_t Exponent_Mask    = 0x7FF0000000000000UL;
  static constexpr uint64_t Significand_Mask = 0x000FFFFFFFFFFFFFU;
  static constexpr uint64_t Hidden_Bit       = 0x0010000000000000U;
  static constexpr int Physical_Significand_Size = 52;  // Excludes the hidden bit.
  static constexpr int Significand_Size = 53;

  using uint_type = uint64_t;
  using type = double;

  static constexpr int Exponent_Bias = 0x3FF + Physical_Significand_Size;
  static constexpr int Denormal_Exponent = -Exponent_Bias + 1;
  static constexpr int Max_Exponent = 0x7FF - Exponent_Bias;
  static constexpr uint64_t Infinity = 0x7FF0000000000000U;
  static constexpr uint64_t Nan      = 0x7FF8000000000000U;
};

template<>
class IeeeFloatTraits<float> {
public:
  static constexpr uint32_t Sign_Mask        = 0x80000000U;
  static constexpr uint32_t Exponent_Mask    = 0x7F800000U;
  static constexpr uint32_t Significand_Mask = 0x007FFFFFU;
  static constexpr uint32_t Hidden_Bit       = 0x00800000U;
  static constexpr int Physical_Significand_Size = 23;  // Excludes the hidden bit.
  static constexpr int Significand_Size = 24;

  using uint_type = uint32_t;
  using type = float;

  static constexpr int Exponent_Bias = 0x7F + Physical_Significand_Size;
  static constexpr int Denormal_Exponent = -Exponent_Bias + 1;
  static constexpr int Max_Exponent = 0xFF - Exponent_Bias;
  static constexpr uint32_t Infinity = 0x7F800000U;
  static constexpr uint32_t Nan      = 0x7FC00000U;
};


using IeeeSingle = IeeeFloat<float>;
using IeeeDouble = IeeeFloat<double>;

}

#endif
