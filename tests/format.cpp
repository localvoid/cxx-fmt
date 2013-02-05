#include <list>
#include <gtest/gtest.h>
#include <fmt/format-base.hpp>
#include <string.h>

namespace {

class Arg {
public:
  Arg() {
    reset();
  }

  Arg(int32_t index, int32_t width, int32_t precision, int32_t flags)
      : index_(index), width_(width), precision_(precision), flags_(flags) {}

  void reset() {
    index_ = -1;
    width_ = 0;
    precision_ = 0;
    flags_ = 0;
  }

  void set_index(int32_t i) {
    index_ = i;
  }

  void set_width(int32_t i) {
    width_ = i;
  }

  void set_precision(int32_t i) {
    precision_ = i;
  }

  void set_flag(fmt::Flag i) {
    flags_ |= i;
  }

  bool operator==(const Arg& o) const {
    return ((index_ == o.index_) &&
            (width_ == o.width_) &&
            (precision_ == o.precision_) &&
            (flags_ == o.flags_));
  }

private:
  int32_t index_ = -1;
  int32_t width_ = 0;
  int32_t precision_ = 0;
  int32_t flags_ = 0;
};

class Expectation {
public:
  enum class Type {
    Text,
    Arg
  };

  Expectation(Arg o) {
    type_ = Type::Arg;
    arg_options_ = o;
  }

  Expectation(std::string s) {
    type_ = Type::Text;
    string_value_ = s;
  }

  void check(std::string s) {
    if (type_ != Type::Text) {
      FAIL();
    } else {
      EXPECT_EQ(string_value_, s);
    }
  }

  void check(Arg o) {
    if (type_ != Type::Arg) {
      FAIL();
    } else {
      EXPECT_EQ(arg_options_, o);
    }
  }

protected:
  Type type_;
  std::string string_value_;
  Arg arg_options_;
};


class FormatMock : public fmt::FormatBase<FormatMock> {
public:
  FormatMock(const char *s) {
    p = s;
    pe = p + strlen(s);
    eof = pe;
  }


  void expect(std::string s) {
    expects_.emplace_back(s);
  }

  void expect(int32_t index, int32_t width, int32_t precision, int32_t flags) {
    expects_.emplace_back(Arg(index, width, precision, flags));
  }

  void check(std::string s) {
    if (expects_.size() <= expects_i_) {
      FAIL();
    } else {
      auto e = expects_[expects_i_++];
      e.check(s);
    }
  }

  void check(Arg i) {
    if (expects_.size() <= expects_i_) {
      FAIL();
    } else {
      auto e = expects_[expects_i_++];
      e.check(i);
    }
  }

  void mark(const char *fpc) {
    mark_ = fpc;
  }

  int capture_integer(const char *fpc) {
    int i = 0;
    const char *xp = mark_;

    while (xp != fpc) {
      i = i * 10 + (*xp - '0');
      xp++;
    }
    return i;
  }

  void capture_precision(const char *fpc) {
    int i = capture_integer(fpc);
    options_.set_precision(i);
  }
  void capture_width(const char *fpc) {
    int i = capture_integer(fpc);
    options_.set_width(i);
  }
  void capture_argument(const char *fpc) {
    int i = capture_integer(fpc);
    options_.set_index(i);
  }

  void set_flag(fmt::Flag v) {
    options_.set_flag(v);
  }

  void emit_text(const char *end) {
    std::string s(mark_, end - mark_);
    check(s);
  }

  void emit_open_bracket() {
    check(std::string("{"));
  }

  void emit_argument() {
    check(options_);
    options_.reset();
  }

  void argument_error() {
  }
  void end_error() {
  }

protected:
  const char *mark_;
  Arg options_;
  std::vector<Expectation> expects_;
  uint32_t expects_i_ = 0;
};

}

TEST(Format, basic_text) {
  FormatMock f("Test");
  f.expect("Test");
  f();
}

TEST(Format, open_bracket) {
  FormatMock f("Test {{ Bracket");
  f.expect("Test ");
  f.expect("{");
  f.expect(" Bracket");
  f();
}

TEST(Format, basic_arg) {
  FormatMock f("{}");
  f.expect(-1,0,0,0);
  f();
}

TEST(Format, arg) {
  FormatMock f("Test {} Arg");
  f.expect("Test ");
  f.expect(-1,0,0,0);
  f.expect(" Arg");
  f();
}

TEST(Format, indexed_arg) {
  FormatMock f("{1}");
  f.expect(1,0,0,0);
  f();
}

TEST(Format, multi_indexed_arg) {
  FormatMock f("{1} multiple {2} args {0}");
  f.expect(1,0,0,0);
  f.expect(" multiple ");
  f.expect(2,0,0,0);
  f.expect(" args ");
  f.expect(0,0,0,0);
  f();
}

TEST(Format, concat_args) {
  FormatMock f("{}{}{}");
  f.expect(-1,0,0,0);
  f.expect(-1,0,0,0);
  f.expect(-1,0,0,0);
  f();
}

TEST(Format, args_width) {
  FormatMock f("{:w10}");
  f.expect(-1, 10, 0, 0);
  f();
}

TEST(Format, args_precision) {
  FormatMock f("{:.20}");
  f.expect(-1, 0, 20, 0);
  f();
}

TEST(Format, args_flags) {
  FormatMock f("{:^+x}");
  f.expect(-1, 0, 0, fmt::Flag::AlignCentered | fmt::Flag::SignPlus | fmt::Flag::Hex);
  f();
}

TEST(Format, args_indexed_width_precision_flags) {
  FormatMock f("{3:%0w44.20}");
  f.expect(3, 44, 20, fmt::Flag::Percentage | fmt::Flag::ZeroPadding);
  f();
}
