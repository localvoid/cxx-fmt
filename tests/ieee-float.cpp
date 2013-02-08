#include <gtest/gtest.h>
#include <cstdint>
#include <fmt/ieee-float.hpp>

using namespace fmt;

TEST(IeeeFloat, Uint64Conversions) {
  uint64_t ordered = 0x0123456789ABCDEF;
  EXPECT_EQ(3512700564088504e-318, IeeeDouble(ordered).value());

  uint64_t min_double64 = 0x0000000000000001;
  EXPECT_EQ(5e-324, IeeeDouble(min_double64).value());

  uint64_t max_double64 = 0x7fefffffffffffff;
  EXPECT_EQ(1.7976931348623157e308, IeeeDouble(max_double64).value());
}

TEST(IeeeFloat, Uint32Conversions) {
  uint32_t ordered = 0x01234567;
  EXPECT_EQ(2.9988165487136453e-38f, IeeeSingle(ordered).value());

  uint32_t min_float32 = 0x00000001;
  EXPECT_EQ(1.4e-45f, IeeeSingle(min_float32).value());

  uint32_t max_float32 = 0x7f7fffff;
  EXPECT_EQ(3.4028234e38f, IeeeSingle(max_float32).value());
}

TEST(IeeeFloat, Double_IsDenormal) {
  uint64_t min_double64 = 0x0000000000000001;
  EXPECT_TRUE(IeeeDouble(min_double64).is_denormal());
  uint64_t bits = 0x000FFFFFFFFFFFFF;
  EXPECT_TRUE(IeeeDouble(bits).is_denormal());
  bits = 0x0010000000000000;
  EXPECT_TRUE(!IeeeDouble(bits).is_denormal());
}


TEST(IeeeFloat, Single_IsDenormal) {
  uint32_t min_float32 = 0x00000001;
  EXPECT_TRUE(IeeeSingle(min_float32).is_denormal());
  uint32_t bits = 0x007FFFFF;
  EXPECT_TRUE(IeeeSingle(bits).is_denormal());
  bits = 0x00800000;
  EXPECT_TRUE(!IeeeSingle(bits).is_denormal());
}

TEST(IeeeFloat, Double_IsSpecial) {
  EXPECT_TRUE(IeeeDouble(IeeeDouble::infinity()).is_special());
  EXPECT_TRUE(IeeeDouble(-IeeeDouble::infinity()).is_special());
  EXPECT_TRUE(IeeeDouble(IeeeDouble::nan()).is_special());
  uint64_t bits = 0xFFF1234500000000;
  EXPECT_TRUE(IeeeDouble(bits).is_special());
  // Denormals are not special:
  EXPECT_TRUE(!IeeeDouble(5e-324).is_special());
  EXPECT_TRUE(!IeeeDouble(-5e-324).is_special());
  // And some random numbers:
  EXPECT_TRUE(!IeeeDouble(0.0).is_special());
  EXPECT_TRUE(!IeeeDouble(-0.0).is_special());
  EXPECT_TRUE(!IeeeDouble(1.0).is_special());
  EXPECT_TRUE(!IeeeDouble(-1.0).is_special());
  EXPECT_TRUE(!IeeeDouble(1000000.0).is_special());
  EXPECT_TRUE(!IeeeDouble(-1000000.0).is_special());
  EXPECT_TRUE(!IeeeDouble(1e23).is_special());
  EXPECT_TRUE(!IeeeDouble(-1e23).is_special());
  EXPECT_TRUE(!IeeeDouble(1.7976931348623157e308).is_special());
  EXPECT_TRUE(!IeeeDouble(-1.7976931348623157e308).is_special());
}


TEST(IeeeFloat, Single_IsSpecial) {
  EXPECT_TRUE(IeeeSingle(IeeeSingle::infinity()).is_special());
  EXPECT_TRUE(IeeeSingle(-IeeeSingle::infinity()).is_special());
  EXPECT_TRUE(IeeeSingle(IeeeSingle::nan()).is_special());
  uint32_t bits = 0xFFF12345;
  EXPECT_TRUE(IeeeSingle(bits).is_special());
  // Denormals are not special:
  EXPECT_TRUE(!IeeeSingle(1.4e-45f).is_special());
  EXPECT_TRUE(!IeeeSingle(-1.4e-45f).is_special());
  // And some random numbers:
  EXPECT_TRUE(!IeeeSingle(0.0f).is_special());
  EXPECT_TRUE(!IeeeSingle(-0.0f).is_special());
  EXPECT_TRUE(!IeeeSingle(1.0f).is_special());
  EXPECT_TRUE(!IeeeSingle(-1.0f).is_special());
  EXPECT_TRUE(!IeeeSingle(1000000.0f).is_special());
  EXPECT_TRUE(!IeeeSingle(-1000000.0f).is_special());
  EXPECT_TRUE(!IeeeSingle(1e23f).is_special());
  EXPECT_TRUE(!IeeeSingle(-1e23f).is_special());
  EXPECT_TRUE(!IeeeSingle(1.18e-38f).is_special());
  EXPECT_TRUE(!IeeeSingle(-1.18e-38f).is_special());
}


TEST(IeeeFloat, Double_is_infinite) {
  EXPECT_TRUE(IeeeDouble(IeeeDouble::infinity()).is_infinite());
  EXPECT_TRUE(IeeeDouble(-IeeeDouble::infinity()).is_infinite());
  EXPECT_TRUE(!IeeeDouble(IeeeDouble::nan()).is_infinite());
  EXPECT_TRUE(!IeeeDouble(0.0).is_infinite());
  EXPECT_TRUE(!IeeeDouble(-0.0).is_infinite());
  EXPECT_TRUE(!IeeeDouble(1.0).is_infinite());
  EXPECT_TRUE(!IeeeDouble(-1.0).is_infinite());
  EXPECT_TRUE(!IeeeDouble(0x0000000000000001UL).is_infinite());
}


TEST(IeeeFloat, Single_is_infinite) {
  EXPECT_TRUE(IeeeSingle(IeeeSingle::infinity()).is_infinite());
  EXPECT_TRUE(IeeeSingle(-IeeeSingle::infinity()).is_infinite());
  EXPECT_TRUE(!IeeeSingle(IeeeSingle::nan()).is_infinite());
  EXPECT_TRUE(!IeeeSingle(0.0f).is_infinite());
  EXPECT_TRUE(!IeeeSingle(-0.0f).is_infinite());
  EXPECT_TRUE(!IeeeSingle(1.0f).is_infinite());
  EXPECT_TRUE(!IeeeSingle(-1.0f).is_infinite());
  EXPECT_TRUE(!IeeeSingle(0x00000001U).is_infinite());
}


TEST(IeeeFloat, Double_is_nan) {
  EXPECT_TRUE(IeeeDouble(IeeeDouble::nan()).is_nan());
  EXPECT_TRUE(IeeeDouble(0xFFFFFFFF00000001U).is_nan());
  EXPECT_TRUE(!IeeeDouble(IeeeDouble::infinity()).is_nan());
  EXPECT_TRUE(!IeeeDouble(-IeeeDouble::infinity()).is_nan());
  EXPECT_TRUE(!IeeeDouble(0.0).is_nan());
  EXPECT_TRUE(!IeeeDouble(-0.0).is_nan());
  EXPECT_TRUE(!IeeeDouble(1.0).is_nan());
  EXPECT_TRUE(!IeeeDouble(-1.0).is_nan());
  EXPECT_TRUE(!IeeeDouble(0x0000000000000001UL).is_nan());
}


TEST(IeeeFloat, Single_is_nan) {
  EXPECT_TRUE(IeeeSingle(IeeeSingle::nan()).is_nan());
  EXPECT_TRUE(IeeeSingle(0xFFFFF001U).is_nan());
  EXPECT_TRUE(!IeeeSingle(IeeeSingle::infinity()).is_nan());
  EXPECT_TRUE(!IeeeSingle(-IeeeSingle::infinity()).is_nan());
  EXPECT_TRUE(!IeeeSingle(0.0f).is_nan());
  EXPECT_TRUE(!IeeeSingle(-0.0f).is_nan());
  EXPECT_TRUE(!IeeeSingle(1.0f).is_nan());
  EXPECT_TRUE(!IeeeSingle(-1.0f).is_nan());
  uint32_t min_float32 = 0x00000001;
  EXPECT_TRUE(!IeeeSingle(min_float32).is_nan());
}


TEST(IeeeFloat, Double_Sign) {
  EXPECT_EQ(1, IeeeDouble(1.0).sign());
  EXPECT_EQ(1, IeeeDouble(IeeeDouble::infinity()).sign());
  EXPECT_EQ(-1, IeeeDouble(-IeeeDouble::infinity()).sign());
  EXPECT_EQ(1, IeeeDouble(0.0).sign());
  EXPECT_EQ(-1, IeeeDouble(-0.0).sign());
  uint64_t min_double64 = 0x0000000000000001;
  EXPECT_EQ(1, IeeeDouble(min_double64).sign());
}


TEST(IeeeFloat, Single_Sign) {
  EXPECT_EQ(1, IeeeSingle(1.0f).sign());
  EXPECT_EQ(1, IeeeSingle(IeeeSingle::infinity()).sign());
  EXPECT_EQ(-1, IeeeSingle(-IeeeSingle::infinity()).sign());
  EXPECT_EQ(1, IeeeSingle(0.0f).sign());
  EXPECT_EQ(-1, IeeeSingle(-0.0f).sign());
  uint32_t min_float32 = 0x00000001;
  EXPECT_EQ(1, IeeeSingle(min_float32).sign());
}

TEST(IeeeFloat, NextDouble) {
  EXPECT_EQ(4e-324, IeeeDouble(0.0).next());
  EXPECT_EQ(0.0, IeeeDouble(-0.0).next());
  EXPECT_EQ(-0.0, IeeeDouble(-4e-324).next());
  EXPECT_TRUE(IeeeDouble(IeeeDouble(-0.0).next()).sign() > 0);
  EXPECT_TRUE(IeeeDouble(IeeeDouble(-4e-324).next()).sign() < 0);
  IeeeDouble d0(-4e-324);
  IeeeDouble d1(d0.next());
  IeeeDouble d2(d1.next());
  EXPECT_EQ(-0.0, d1.value());
  EXPECT_TRUE(d1.sign() < 0);
  EXPECT_EQ(0.0, d2.value());
  EXPECT_TRUE(d2.sign() > 0);
  EXPECT_EQ(4e-324, d2.next());
  EXPECT_EQ(-1.7976931348623157e308, IeeeDouble(-IeeeDouble::infinity()).next());
  EXPECT_EQ(IeeeDouble::infinity(),
           IeeeDouble(0x7fefffffffffffffUL).next());
}


TEST(IeeeFloat, PreviousDouble) {
  EXPECT_EQ(0.0, IeeeDouble(4e-324).prev());
  EXPECT_EQ(-0.0, IeeeDouble(0.0).prev());
  EXPECT_TRUE(IeeeDouble(IeeeDouble(0.0).prev()).sign() < 0);
  EXPECT_EQ(-4e-324, IeeeDouble(-0.0).prev());
  IeeeDouble d0(4e-324);
  IeeeDouble d1(d0.prev());
  IeeeDouble d2(d1.prev());
  EXPECT_EQ(0.0, d1.value());
  EXPECT_TRUE(d1.sign() > 0);
  EXPECT_EQ(-0.0, d2.value());
  EXPECT_TRUE(d2.sign() < 0);
  EXPECT_EQ(-4e-324, d2.prev());
  EXPECT_EQ(1.7976931348623157e308, IeeeDouble(IeeeDouble::infinity()).prev());
  EXPECT_EQ(-IeeeDouble::infinity(),
           IeeeDouble(0xffefffffffffffffUL).prev());
}
