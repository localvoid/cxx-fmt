
#line 1 "format-base.hpp.rl"
#ifndef _FMT_FORMAT_BASE_HPP_
#define _FMT_FORMAT_BASE_HPP_


#line 88 "format-base.hpp.rl"



#include <cstdint>

namespace fmt {

enum Flag : uint32_t {
  AlignLeft      = 1,
  AlignRight     = 1 << 1,
  AlignCentered  = 1 << 2,
  AlignNumeric   = 1 << 3,
  SignPlus       = 1 << 4,
  SignSpace      = 1 << 6,
  Localized      = 1 << 7,
  Char           = 1 << 9,
  Octal          = 1 << 10,
  Hex            = 1 << 11,
  UpperHex       = 1 << 12,
  Exponent       = 1 << 13,
  UpperExponent  = 1 << 14,
  Fixed          = 1 << 15,
  LargeExponent  = 1 << 16,
  Percentage     = 1 << 17,
  Prefixed       = 1 << 18,
  ZeroPadding    = 1 << 19,
  CommaSeparator = 1 << 20,
};



#line 40 "format-base.hpp"
static const int format_start = 8;
static const int format_first_final = 8;
static const int format_error = 0;

static const int format_en_main = 8;


#line 119 "format-base.hpp.rl"


template<typename T>
class FormatBase {
public:
  FormatBase() {}

  FormatBase(const char *fmt,
             std::size_t fmt_size)
      : p(fmt),
        pe(fmt + fmt_size),
        eof(pe) {}

  template<typename ...Args>
  void operator()(Args&& ... args) {
    for(;;) {
      
#line 66 "format-base.hpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr3:
#line 9 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_open_bracket(); }
#line 14 "format-base.hpp.rl"
	{ static_cast<T&>(*this).argument_error(); }
	goto st8;
tr4:
#line 10 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_argument(std::forward<Args>(args)...); }
	goto st8;
tr7:
#line 11 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_argument(p); }
#line 10 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_argument(std::forward<Args>(args)...); }
	goto st8;
tr34:
#line 13 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_precision(p); }
#line 10 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_argument(std::forward<Args>(args)...); }
	goto st8;
tr39:
#line 12 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_width(p); }
#line 10 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_argument(std::forward<Args>(args)...); }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 104 "format-base.hpp"
	if ( (*p) == 123 )
		goto st1;
	goto tr40;
tr40:
#line 7 "format-base.hpp.rl"
	{ static_cast<T&>(*this).mark(p); }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 116 "format-base.hpp"
	if ( (*p) == 123 )
		goto tr43;
	goto st9;
tr43:
#line 8 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_text(p); }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 128 "format-base.hpp"
	switch( (*p) ) {
		case 58: goto st3;
		case 123: goto tr3;
		case 125: goto tr4;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr1;
	goto tr0;
tr0:
#line 14 "format-base.hpp.rl"
	{ static_cast<T&>(*this).argument_error(); }
	goto st0;
#line 141 "format-base.hpp"
st0:
cs = 0;
	goto _out;
tr1:
#line 7 "format-base.hpp.rl"
	{ static_cast<T&>(*this).mark(p); }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 153 "format-base.hpp"
	switch( (*p) ) {
		case 58: goto tr6;
		case 125: goto tr7;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st2;
	goto tr0;
tr6:
#line 11 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_argument(p); }
	goto st3;
tr8:
#line 26 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::SignSpace); }
	goto st3;
tr9:
#line 44 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::Prefixed); }
	goto st3;
tr10:
#line 40 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::Percentage); }
	goto st3;
tr11:
#line 25 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::SignPlus); }
	goto st3;
tr12:
#line 46 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::CommaSeparator); }
	goto st3;
tr14:
#line 45 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::ZeroPadding); }
	goto st3;
tr15:
#line 19 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::AlignLeft); }
	goto st3;
tr16:
#line 21 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::AlignNumeric); }
	goto st3;
tr17:
#line 18 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::AlignRight); }
	goto st3;
tr18:
#line 36 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::UpperExponent); }
	goto st3;
tr19:
#line 37 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::Fixed); }
	goto st3;
tr20:
#line 38 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::LargeExponent); }
	goto st3;
tr21:
#line 39 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::UpperHex); }
	goto st3;
tr22:
#line 20 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::AlignCentered); }
	goto st3;
tr23:
#line 30 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::Char); }
	goto st3;
tr24:
#line 31 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::Exponent); }
	goto st3;
tr25:
#line 32 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::Fixed); }
	goto st3;
tr26:
#line 33 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::Localized); }
	goto st3;
tr27:
#line 34 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::Octal); }
	goto st3;
tr29:
#line 35 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(Flag::Hex); }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 249 "format-base.hpp"
	switch( (*p) ) {
		case 32: goto tr8;
		case 35: goto tr9;
		case 37: goto tr10;
		case 43: goto tr11;
		case 44: goto tr12;
		case 46: goto st4;
		case 48: goto tr14;
		case 60: goto tr15;
		case 61: goto tr16;
		case 62: goto tr17;
		case 69: goto tr18;
		case 70: goto tr19;
		case 71: goto tr20;
		case 88: goto tr21;
		case 94: goto tr22;
		case 99: goto tr23;
		case 101: goto tr24;
		case 102: goto tr25;
		case 110: goto tr26;
		case 111: goto tr27;
		case 119: goto st6;
		case 120: goto tr29;
		case 125: goto tr4;
	}
	goto tr0;
tr31:
#line 13 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_precision(p); }
	goto st4;
tr36:
#line 12 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_width(p); }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 288 "format-base.hpp"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr30;
	goto tr0;
tr30:
#line 7 "format-base.hpp.rl"
	{ static_cast<T&>(*this).mark(p); }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 300 "format-base.hpp"
	switch( (*p) ) {
		case 46: goto tr31;
		case 119: goto tr33;
		case 125: goto tr34;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st5;
	goto tr0;
tr33:
#line 13 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_precision(p); }
	goto st6;
tr38:
#line 12 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_width(p); }
	goto st6;
st6:
	if ( ++p == pe )
		goto _test_eof6;
case 6:
#line 321 "format-base.hpp"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr35;
	goto tr0;
tr35:
#line 7 "format-base.hpp.rl"
	{ static_cast<T&>(*this).mark(p); }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 333 "format-base.hpp"
	switch( (*p) ) {
		case 46: goto tr36;
		case 119: goto tr38;
		case 125: goto tr39;
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
#line 8 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_text(p); }
	break;
	case 1: 
	case 2: 
	case 3: 
	case 4: 
	case 5: 
	case 6: 
	case 7: 
#line 14 "format-base.hpp.rl"
	{ static_cast<T&>(*this).argument_error(); }
	break;
#line 371 "format-base.hpp"
	}
	}

	_out: {}
	}

#line 136 "format-base.hpp.rl"
      if (p == eof || cs == 
#line 380 "format-base.hpp"
0
#line 136 "format-base.hpp.rl"
)
        break;
    }
  }

protected:
  int cs;
  const char *p;
  const char *pe;
  const char *eof;
};


}

#endif
