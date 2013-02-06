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
  struct Data : public FormatBase::Data {
    Arg options;
  };

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

  void capture_precision(Data &d, const char *fpc) {
    int i = capture_integer(d, fpc);
    d.options.set_precision(i);
  }
  void capture_width(Data &d, const char *fpc) {
    int i = capture_integer(d, fpc);
    d.options.set_width(i);
  }
  void capture_argument(Data &d, const char *fpc) {
    int i = capture_integer(d, fpc);
    d.options.set_index(i);
  }

  void set_flag(Data &d, fmt::Flag v) {
    d.options.set_flag(v);
  }

  void emit_text(Data &d, const char *end) {
    std::string s(d.mark, end - d.mark);
    check(s);
  }

  void emit_open_bracket(Data &d) {
    check(std::string("{"));
  }

  void emit_argument(Data &d) {
    check(d.options);
    d.options.reset();
  }

  void argument_error(Data &d) {
  }
  void end_error(Data &d) {
  }

  void operator()(const char *c) {
    FormatBase::operator()(c, strlen(c));
  }

private:
  std::vector<Expectation> expects_;
  uint32_t expects_i_ = 0;
};

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
  f.expect(-1,0,0,0);
  f("{}");
}

TEST(Format, arg) {
  FormatMock f;
  f.expect("Test ");
  f.expect(-1,0,0,0);
  f.expect(" Arg");
  f("Test {} Arg");
}

TEST(Format, indexed_arg) {
  FormatMock f;
  f.expect(1,0,0,0);
  f("{1}");
}

TEST(Format, multi_indexed_arg) {
  FormatMock f;
  f.expect(1,0,0,0);
  f.expect(" multiple ");
  f.expect(2,0,0,0);
  f.expect(" args ");
  f.expect(0,0,0,0);
  f("{1} multiple {2} args {0}");
}

TEST(Format, concat_args) {
  FormatMock f;
  f.expect(-1,0,0,0);
  f.expect(-1,0,0,0);
  f.expect(-1,0,0,0);
  f("{}{}{}");
}

TEST(Format, args_width) {
  FormatMock f;
  f.expect(-1, 10, 0, 0);
  f("{:w10}");
}

TEST(Format, args_precision) {
  FormatMock f;
  f.expect(-1, 0, 20, 0);
  f("{:.20}");
}

TEST(Format, args_flags) {
  FormatMock f;
  f.expect(-1, 0, 0, fmt::Flag::AlignCentered | fmt::Flag::SignPlus | fmt::Flag::Hex);
  f("{:^+x}");
}

TEST(Format, args_indexed_width_precision_flags) {
  FormatMock f;
  f.expect(3, 44, 20, fmt::Flag::Percentage | fmt::Flag::CommaSeparator);
  f("{3:%,w44.20}");
}
