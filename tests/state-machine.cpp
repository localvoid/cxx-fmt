
#line 1 "state-machine.cpp.rl"

#line 31 "state-machine.cpp.rl"


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
      
#line 105 "state-machine.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr3:
#line 6 "state-machine.cpp.rl"
	{ emit_open_bracket(); }
	goto st8;
tr4:
#line 7 "state-machine.cpp.rl"
	{ emit_argument(); }
	goto st8;
tr7:
#line 8 "state-machine.cpp.rl"
	{ arg_.index = capture_integer(mark, p) + 1; }
#line 7 "state-machine.cpp.rl"
	{ emit_argument(); }
	goto st8;
tr27:
#line 10 "state-machine.cpp.rl"
	{ arg_.precision = capture_integer(mark, p); }
#line 7 "state-machine.cpp.rl"
	{ emit_argument(); }
	goto st8;
tr31:
#line 9 "state-machine.cpp.rl"
	{ arg_.width = capture_integer(mark, p); }
#line 7 "state-machine.cpp.rl"
	{ emit_argument(); }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 141 "state-machine.cpp"
	if ( (*p) == 123 )
		goto st1;
	goto tr32;
tr32:
#line 4 "state-machine.cpp.rl"
	{ mark = p; }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 153 "state-machine.cpp"
	if ( (*p) == 123 )
		goto tr35;
	goto st9;
tr35:
#line 5 "state-machine.cpp.rl"
	{ emit_text(mark, p); }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 165 "state-machine.cpp"
	switch( (*p) ) {
		case 58: goto st3;
		case 123: goto tr3;
		case 125: goto tr4;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr1;
	goto tr0;
tr0:
#line 26 "state-machine.cpp.rl"
	{ }
	goto st0;
#line 178 "state-machine.cpp"
st0:
cs = 0;
	goto _out;
tr1:
#line 4 "state-machine.cpp.rl"
	{ mark = p; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 190 "state-machine.cpp"
	switch( (*p) ) {
		case 58: goto tr6;
		case 125: goto tr7;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st2;
	goto tr0;
tr6:
#line 8 "state-machine.cpp.rl"
	{ arg_.index = capture_integer(mark, p) + 1; }
	goto st3;
tr8:
#line 14 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::SignSpace; }
	goto st3;
tr9:
#line 23 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::Prefixed; }
	goto st3;
tr10:
#line 22 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::Percentage; }
	goto st3;
tr11:
#line 13 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::SignPlus; }
	goto st3;
tr12:
#line 25 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::Comma; }
	goto st3;
tr14:
#line 24 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::ZeroPadding; }
	goto st3;
tr15:
#line 11 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::AlignLeft; }
	goto st3;
tr16:
#line 12 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::AlignRight; }
	goto st3;
tr17:
#line 21 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::UpperExponent; }
	goto st3;
tr18:
#line 20 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::LargeExponent; }
	goto st3;
tr19:
#line 19 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::UpperHex; }
	goto st3;
tr20:
#line 15 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::Char; }
	goto st3;
tr21:
#line 16 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::Exponent; }
	goto st3;
tr22:
#line 17 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::Fixed; }
	goto st3;
tr24:
#line 18 "state-machine.cpp.rl"
	{ arg_.flags |= fmt::Flag::Hex; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 266 "state-machine.cpp"
	switch( (*p) ) {
		case 32: goto tr8;
		case 35: goto tr9;
		case 37: goto tr10;
		case 43: goto tr11;
		case 44: goto tr12;
		case 46: goto st4;
		case 48: goto tr14;
		case 60: goto tr15;
		case 62: goto tr16;
		case 69: goto tr17;
		case 71: goto tr18;
		case 88: goto tr19;
		case 99: goto tr20;
		case 101: goto tr21;
		case 102: goto tr22;
		case 119: goto st6;
		case 120: goto tr24;
		case 125: goto tr4;
	}
	goto tr0;
tr29:
#line 9 "state-machine.cpp.rl"
	{ arg_.width = capture_integer(mark, p); }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 296 "state-machine.cpp"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr25;
	goto tr0;
tr25:
#line 4 "state-machine.cpp.rl"
	{ mark = p; }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 308 "state-machine.cpp"
	if ( (*p) == 125 )
		goto tr27;
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st5;
	goto tr0;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr28;
	goto tr0;
tr28:
#line 4 "state-machine.cpp.rl"
	{ mark = p; }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 329 "state-machine.cpp"
	switch( (*p) ) {
		case 46: goto tr29;
		case 125: goto tr31;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st7;
	goto tr0;
	}
	_test_eof8: cs = 8; goto _test_eof; 
	_test_eof9: cs = 9; goto _test_eof; 
	_test_eof1: cs = 1; goto _test_eof; 
	_test_eof2: cs = 2; goto _test_eof; 
	_test_eof3: cs = 3; goto _test_eof; 
	_test_eof4: cs = 4; goto _test_eof; 
	_test_eof5: cs = 5; goto _test_eof; 
	_test_eof6: cs = 6; goto _test_eof; 
	_test_eof7: cs = 7; goto _test_eof; 

	_test_eof: {}
	if ( p == eof )
	{
	switch ( cs ) {
	case 9: 
#line 5 "state-machine.cpp.rl"
	{ emit_text(mark, p); }
	break;
	case 1: 
	case 2: 
	case 3: 
	case 4: 
	case 5: 
	case 6: 
	case 7: 
#line 26 "state-machine.cpp.rl"
	{ }
	break;
#line 366 "state-machine.cpp"
	}
	}

	_out: {}
	}

#line 130 "state-machine.cpp.rl"
      if (p == eof || cs == 
#line 375 "state-machine.cpp"
0
#line 130 "state-machine.cpp.rl"
)
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



#line 428 "state-machine.cpp"
static const int format_start = 8;
static const int format_first_final = 8;
static const int format_error = 0;

static const int format_en_main = 8;


#line 180 "state-machine.cpp.rl"

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
