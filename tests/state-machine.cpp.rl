%%{
  machine format;

  action Mark              { mark = fpc; }
  action EmitText          { emit_text(mark, fpc); }
  action EmitOpenBracket   { emit_open_bracket(); }
  action EmitArgument      { emit_argument(); }
  action CaptureArgument   { arg_.index = capture_integer(mark, fpc) + 1; }
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
  action ArgumentError     { }
  action EndError          { }

  include format_spec "../ragel/format-spec.rl";

}%%

#include <gtest/gtest.h>

#include <cstdint>
#include <iostream>
#include <vector>
#include <string.h>

#include <fmt/flag.hpp>

namespace {

using namespace fmt;

struct ArgOptions {
  ArgOptions() {}

  ArgOptions(uint32_t i, uint32_t w, uint32_t p, uint32_t f)
      : index(i), width(w), precision(p), flags(f) {}

  void reset() {
    index = 0;
    width = 0;
    precision = 0;
    flags = 0;
  }

  bool operator==(const ArgOptions& o) const {
    return ((index == o.index) &&
            (width == o.width) &&
            (precision == o.precision) &&
            (flags == o.flags));
  }

  uint32_t index = 0;
  uint32_t width = 0;
  uint32_t precision = 0;
  uint32_t flags = 0;
};

class Expectation {
public:
  enum class Type {
    Text,
    Arg
  };

  Expectation(ArgOptions o) {
    type_ = Type::Arg;
    arg_ = o;
  }

  Expectation(std::string s) {
    type_ = Type::Text;
    str_ = s;
  }

  void check(std::string s) {
    if (type_ != Type::Text)
      FAIL();
    else
      EXPECT_EQ(str_, s);
  }

  void check(ArgOptions o) {
    if (type_ != Type::Arg)
      FAIL();
    else
      EXPECT_EQ(arg_, o);
  }

protected:
  Type type_;
  std::string str_;
  ArgOptions arg_;
};


int capture_integer(const char *p, const char *fpc) {
  int i = 0;
  while (p != fpc) {
    i = i * 10 + (*p - '0');
    p++;
  }
  return i;
}

class FormatMock {
public:
  void operator()(const char *fstr) {
    int cs = 0;
    const char *p = fstr;
    const char *pe = &fstr[strlen(fstr)];
    const char *eof = pe;
    const char *mark = nullptr;

    for(;;) {
      %% write exec;
      if (p == eof || cs == %%{ write error; }%%)
        break;
    }
  }

  void check(std::string s) {
    if (expects_.size() <= expects_i_)
      FAIL();
    else
      expects_[expects_i_++].check(s);
  }

  void check(ArgOptions i) {
    if (expects_.size() <= expects_i_)
      FAIL();
    else
      expects_[expects_i_++].check(i);
  }

  void expect(std::string s) {
    expects_.emplace_back(s);
  }

  void expect(uint32_t index, uint32_t width, uint32_t precision, uint32_t flags) {
    expects_.emplace_back(ArgOptions(index, width, precision, flags));
  }


protected:
  void emit_text(const char *mark, const char *fpc) {
    check(std::string(mark, fpc - mark));
  }

  void emit_open_bracket() {
    check(std::string("{"));
  }

  void emit_argument() {
    check(arg_);
    arg_.reset();
  }

private:
  ArgOptions arg_;
  std::vector<Expectation> expects_;
  uint32_t expects_i_ = 0;
};


%% write data;

}


TEST(Format, basic_text) {
  FormatMock f;
  f.expect("Test");
  f("Test");
}

TEST(Format, open_bracket) {
  FormatMock f;
  f.expect("Test ");
  f.expect("{");
  f.expect(" Bracket");
  f("Test {{ Bracket");
}

TEST(Format, basic_arg) {
  FormatMock f;
  f.expect(0,0,0,0);
  f("{}");
}

TEST(Format, arg) {
  FormatMock f;
  f.expect("Test ");
  f.expect(0,0,0,0);
  f.expect(" Arg");
  f("Test {} Arg");
}

TEST(Format, indexed_arg) {
  FormatMock f;
  f.expect(2,0,0,0);
  f("{1}");
}

TEST(Format, multi_indexed_arg) {
  FormatMock f;
  f.expect(2,0,0,0);
  f.expect(" multiple ");
  f.expect(3,0,0,0);
  f.expect(" args ");
  f.expect(1,0,0,0);
  f("{1} multiple {2} args {0}");
}

TEST(Format, concat_args) {
  FormatMock f;
  f.expect(0,0,0,0);
  f.expect(0,0,0,0);
  f.expect(0,0,0,0);
  f("{}{}{}");
}

TEST(Format, args_width) {
  FormatMock f;
  f.expect(0, 10, 0, 0);
  f("{:w10}");
}

TEST(Format, args_precision) {
  FormatMock f;
  f.expect(0, 0, 20, 0);
  f("{:.20}");
}

TEST(Format, args_flags) {
  FormatMock f;
  f.expect(0, 0, 0, fmt::Flag::AlignLeft | fmt::Flag::SignPlus | fmt::Flag::Hex);
  f("{:<+x}");
}

TEST(Format, args_indexed_width_precision_flags) {
  FormatMock f;
  f.expect(4, 44, 20, fmt::Flag::Percentage | fmt::Flag::Comma);
  f("{3:%,w44.20}");
}
