
#line 1 "format.cpp.rl"

#line 31 "format.cpp.rl"


#include <cstdint>
#include <iostream>
#include <string.h>

#include <fmt/format.hpp>

namespace {

using namespace fmt;

struct ArgOptions {
  void reset() {
    index = 0;
    width = 0;
    precision = 0;
    flags = 0;
  }

  uint32_t index = 0;
  uint32_t width = 0;
  uint32_t precision = 0;
  uint32_t flags = 0;
};

int capture_integer(const char *p, const char *fpc) {
  int i = 0;
  while (p != fpc) {
    i = i * 10 + (*p - '0');
    p++;
  }
  return i;
}

class Format {
public:
  Format(char *buf, Arg *args, uint32_t args_size)
      : buf_(buf), args_(args), args_size_(args_size) {}


  uint32_t operator()(const char *fstr, uint32_t fstr_size) {
    int cs = 0;
    const char *p = fstr;
    const char *pe = &fstr[fstr_size];
    const char *eof = pe;
    const char *mark = nullptr;

    for(;;) {
      
#line 56 "format.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr3:
#line 6 "format.cpp.rl"
	{ emit_open_bracket(); }
	goto st8;
tr4:
#line 7 "format.cpp.rl"
	{ emit_argument(); }
	goto st8;
tr7:
#line 8 "format.cpp.rl"
	{ arg_.index = capture_integer(mark, p); }
#line 7 "format.cpp.rl"
	{ emit_argument(); }
	goto st8;
tr27:
#line 10 "format.cpp.rl"
	{ arg_.precision = capture_integer(mark, p); }
#line 7 "format.cpp.rl"
	{ emit_argument(); }
	goto st8;
tr31:
#line 9 "format.cpp.rl"
	{ arg_.width = capture_integer(mark, p); }
#line 7 "format.cpp.rl"
	{ emit_argument(); }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 92 "format.cpp"
	if ( (*p) == 123 )
		goto st1;
	goto tr32;
tr32:
#line 4 "format.cpp.rl"
	{ mark = p; }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 104 "format.cpp"
	if ( (*p) == 123 )
		goto tr35;
	goto st9;
tr35:
#line 5 "format.cpp.rl"
	{ emit_text(mark, p); }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 116 "format.cpp"
	switch( (*p) ) {
		case 58: goto st3;
		case 123: goto tr3;
		case 125: goto tr4;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr1;
	goto tr0;
tr0:
#line 26 "format.cpp.rl"
	{ throw InvalidFormatString("argument_error()"); }
	goto st0;
#line 129 "format.cpp"
st0:
cs = 0;
	goto _out;
tr1:
#line 4 "format.cpp.rl"
	{ mark = p; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 141 "format.cpp"
	switch( (*p) ) {
		case 58: goto tr6;
		case 125: goto tr7;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st2;
	goto tr0;
tr6:
#line 8 "format.cpp.rl"
	{ arg_.index = capture_integer(mark, p); }
	goto st3;
tr8:
#line 14 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::SignSpace; }
	goto st3;
tr9:
#line 23 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::Prefixed; }
	goto st3;
tr10:
#line 22 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::Percentage; }
	goto st3;
tr11:
#line 13 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::SignPlus; }
	goto st3;
tr12:
#line 25 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::Comma; }
	goto st3;
tr14:
#line 24 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::ZeroPadding; }
	goto st3;
tr15:
#line 11 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::AlignLeft; }
	goto st3;
tr16:
#line 12 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::AlignRight; }
	goto st3;
tr17:
#line 21 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::UpperExponent; }
	goto st3;
tr18:
#line 20 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::LargeExponent; }
	goto st3;
tr19:
#line 19 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::UpperHex; }
	goto st3;
tr20:
#line 15 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::Char; }
	goto st3;
tr21:
#line 16 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::Exponent; }
	goto st3;
tr22:
#line 17 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::Fixed; }
	goto st3;
tr24:
#line 18 "format.cpp.rl"
	{ arg_.flags |= fmt::Flag::Hex; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 217 "format.cpp"
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
#line 9 "format.cpp.rl"
	{ arg_.width = capture_integer(mark, p); }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 247 "format.cpp"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr25;
	goto tr0;
tr25:
#line 4 "format.cpp.rl"
	{ mark = p; }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 259 "format.cpp"
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
#line 4 "format.cpp.rl"
	{ mark = p; }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 280 "format.cpp"
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
#line 5 "format.cpp.rl"
	{ emit_text(mark, p); }
	break;
	case 1: 
	case 2: 
	case 3: 
	case 4: 
	case 5: 
	case 6: 
	case 7: 
#line 26 "format.cpp.rl"
	{ throw InvalidFormatString("argument_error()"); }
	break;
#line 317 "format.cpp"
	}
	}

	_out: {}
	}

#line 81 "format.cpp.rl"
      if (p == eof || cs == 
#line 326 "format.cpp"
0
#line 81 "format.cpp.rl"
)
        break;
    }
    return size_;
  }

protected:
  void emit_text(const char *mark, const char *fpc) {
    uint32_t size = fpc - mark;
    memcpy(&buf_[size_], mark, size);
    size_ += size;
  }

  void emit_open_bracket() {
    buf_[size_] = '{';
    size_ += 1;
  }

  void emit_argument() {
    uint32_t index;

    if (arg_.index == 0) {
      if (index_ == -1)
        throw InvalidFormatString("Invalid indexing behaviour");
      index = index_++;
    } else {
      if (index_ > 0)
        throw InvalidFormatString("Invalid indexing behaviour");
      if (index_ == 0)
        index_ = -1;
      index = index_ - 1;
    }

    if (index >= args_size_)
      throw InvalidFormatString("Argument index is out of range");

    char *c = &buf_[size_];
    const Arg *a = &args_[index];

    switch (a->type) {
    case Arg::Type::S:
      size_ += a->value.s.size;
      memcpy(c, a->value.s.begin, a->value.s.size);
      break;
    #if __WORDSIZE == 32
    case Arg::Type::U32:
      if (d.arg_options.flags & (Flag::Hex | Flag::UpperHex))
        size_ += itoa_hex(a->value.u32, arg_.width, arg_.flags, c);
      else
        size_ += itoa(a->value.u32, arg_.width, arg_.flags, c);
      break;
    case Arg::Type::I32:
      if (d.arg_options.flags & (Flag::Hex | Flag::UpperHex))
        size_ += itoa_hex(a->value.u32, arg_.width, arg_.flags, c);
      else
        size_ += itoa(a->value.i32, arg_.width, arg_.flags, c);
      break;
    #endif
    case Arg::Type::U64:
      if (arg_.flags & (Flag::Hex | Flag::UpperHex))
        size_ += itoa_hex(a->value.u64, arg_.width, arg_.flags, c);
      else
        size_ += itoa(a->value.i64, arg_.width, arg_.flags, c);
      break;
    case Arg::Type::I64:
      if (arg_.flags & (Flag::Hex | Flag::UpperHex))
        size_ += itoa_hex(a->value.u64, arg_.width, arg_.flags, c);
      else
        size_ += itoa(a->value.i64, arg_.width, arg_.flags, c);
      break;
    case Arg::Type::D:
      size_ += dtoa(a->value.d, arg_.width, arg_.precision, arg_.flags, c);
      break;
    case Arg::Type::P:
      size_ += itoa_hex(reinterpret_cast<uint64_t>(a->value.p), arg_.width, arg_.flags, c);
      break;
    }

    arg_.reset();
  }

private:
  ArgOptions arg_;
  char      *buf_;
  Arg       *args_;
  uint32_t   args_size_;
  uint32_t   size_ = 0;
  int32_t    index_ = 0;
};



#line 421 "format.cpp"
static const int format_start = 8;
static const int format_first_final = 8;
static const int format_error = 0;

static const int format_en_main = 8;


#line 173 "format.cpp.rl"

}

uint32_t fmt::vformat(char *buf, const char *fstr, uint32_t fstr_size, Arg *args, uint32_t args_size) {
  Format f(buf, args, args_size);
  return f(fstr, fstr_size);
}
