
#line 1 "format-base.hpp.rl"
#ifndef _FMT_FORMAT_BASE_HPP_
#define _FMT_FORMAT_BASE_HPP_


#line 82 "format-base.hpp.rl"



#include <cstdint>

namespace fmt {

enum Flag : uint32_t {
  AlignRight     = 1,
  AlignCentered  = 1 << 1,
  SignPlus       = 1 << 2,
  SignSpace      = 1 << 3,
  Char           = 1 << 4,
  Hex            = 1 << 5,
  UpperHex       = 1 << 6,
  Exponent       = 1 << 7,
  UpperExponent  = 1 << 8,
  Fixed          = 1 << 9,
  LargeExponent  = 1 << 10,
  Percentage     = 1 << 11,
  Prefixed       = 1 << 12,
  CommaSeparator = 1 << 13,
};



#line 35 "format-base.hpp"
static const int format_start = 8;
static const int format_first_final = 8;
static const int format_error = 0;

static const int format_en_main = 8;


#line 108 "format-base.hpp.rl"


template<typename T>
class FormatBase {
public:
  struct Data {
    int cs = 0;
    const char *p;
    const char *pe;
    const char *eof;
    const char *mark;
  };

  void mark(Data &d, const char *fpc) {
    d.mark = fpc;
  }

  int capture_integer(Data &d, const char *fpc) {
    int i = 0;
    const char *p = d.mark;

    while (p != fpc) {
      i = i * 10 + (*p - '0');
      p++;
    }
    return i;
  }


  template<typename ...Args>
  void operator()(const char *fmt, size_t fmt_size, Args&& ... args) {
    typename T::Data data;

    data.p = fmt;
    data.pe = fmt + fmt_size;
    data.eof = data.pe;
    data.mark = nullptr;

    
#line 147 "format-base.hpp.rl"
    
#line 148 "format-base.hpp.rl"
    
#line 149 "format-base.hpp.rl"
    
#line 150 "format-base.hpp.rl"

    for(;;) {
      
#line 93 "format-base.hpp"
	{
	if ( (   data.p) == (  data.pe) )
		goto _test_eof;
	switch ( (  data.cs) )
	{
tr3:
#line 9 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_open_bracket(data); }
	goto st8;
tr4:
#line 10 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_argument(data, std::forward<Args>(args)...); }
	goto st8;
tr8:
#line 11 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_argument(data, (   data.p)); }
#line 10 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_argument(data, std::forward<Args>(args)...); }
	goto st8;
tr29:
#line 13 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_precision(data, (   data.p)); }
#line 10 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_argument(data, std::forward<Args>(args)...); }
	goto st8;
tr34:
#line 12 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_width(data, (   data.p)); }
#line 10 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_argument(data, std::forward<Args>(args)...); }
	goto st8;
st8:
	if ( ++(   data.p) == (  data.pe) )
		goto _test_eof8;
case 8:
#line 129 "format-base.hpp"
	if ( (*(   data.p)) == 123 )
		goto st1;
	goto tr35;
tr35:
#line 7 "format-base.hpp.rl"
	{ static_cast<T&>(*this).mark(data, (   data.p)); }
	goto st9;
st9:
	if ( ++(   data.p) == (  data.pe) )
		goto _test_eof9;
case 9:
#line 141 "format-base.hpp"
	if ( (*(   data.p)) == 123 )
		goto tr38;
	goto st9;
tr38:
#line 8 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_text(data, (   data.p)); }
	goto st1;
st1:
	if ( ++(   data.p) == (  data.pe) )
		goto _test_eof1;
case 1:
#line 153 "format-base.hpp"
	switch( (*(   data.p)) ) {
		case 58: goto st3;
		case 123: goto tr3;
		case 125: goto tr4;
	}
	if ( 48 <= (*(   data.p)) && (*(   data.p)) <= 57 )
		goto tr0;
	goto st0;
tr5:
#line 14 "format-base.hpp.rl"
	{ static_cast<T&>(*this).argument_error(data); }
	goto st0;
#line 166 "format-base.hpp"
st0:
(  data.cs) = 0;
	goto _out;
tr0:
#line 7 "format-base.hpp.rl"
	{ static_cast<T&>(*this).mark(data, (   data.p)); }
	goto st2;
st2:
	if ( ++(   data.p) == (  data.pe) )
		goto _test_eof2;
case 2:
#line 178 "format-base.hpp"
	switch( (*(   data.p)) ) {
		case 58: goto tr7;
		case 125: goto tr8;
	}
	if ( 48 <= (*(   data.p)) && (*(   data.p)) <= 57 )
		goto st2;
	goto tr5;
tr7:
#line 11 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_argument(data, (   data.p)); }
	goto st3;
tr9:
#line 24 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::SignSpace); }
	goto st3;
tr10:
#line 39 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::Prefixed); }
	goto st3;
tr11:
#line 35 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::Percentage); }
	goto st3;
tr12:
#line 23 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::SignPlus); }
	goto st3;
tr13:
#line 40 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::CommaSeparator); }
	goto st3;
tr15:
#line 18 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::AlignRight); }
	goto st3;
tr16:
#line 32 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::UpperExponent); }
	goto st3;
tr17:
#line 33 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::LargeExponent); }
	goto st3;
tr18:
#line 34 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::UpperHex); }
	goto st3;
tr19:
#line 19 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::AlignCentered); }
	goto st3;
tr20:
#line 28 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::Char); }
	goto st3;
tr21:
#line 29 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::Exponent); }
	goto st3;
tr22:
#line 30 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::Fixed); }
	goto st3;
tr24:
#line 31 "format-base.hpp.rl"
	{ static_cast<T&>(*this).set_flag(data, Flag::Hex); }
	goto st3;
st3:
	if ( ++(   data.p) == (  data.pe) )
		goto _test_eof3;
case 3:
#line 250 "format-base.hpp"
	switch( (*(   data.p)) ) {
		case 32: goto tr9;
		case 35: goto tr10;
		case 37: goto tr11;
		case 43: goto tr12;
		case 44: goto tr13;
		case 46: goto st4;
		case 62: goto tr15;
		case 69: goto tr16;
		case 71: goto tr17;
		case 88: goto tr18;
		case 94: goto tr19;
		case 99: goto tr20;
		case 101: goto tr21;
		case 102: goto tr22;
		case 119: goto st6;
		case 120: goto tr24;
		case 125: goto tr4;
	}
	goto tr5;
tr26:
#line 13 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_precision(data, (   data.p)); }
	goto st4;
tr31:
#line 12 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_width(data, (   data.p)); }
	goto st4;
st4:
	if ( ++(   data.p) == (  data.pe) )
		goto _test_eof4;
case 4:
#line 283 "format-base.hpp"
	if ( 48 <= (*(   data.p)) && (*(   data.p)) <= 57 )
		goto tr25;
	goto tr5;
tr25:
#line 7 "format-base.hpp.rl"
	{ static_cast<T&>(*this).mark(data, (   data.p)); }
	goto st5;
st5:
	if ( ++(   data.p) == (  data.pe) )
		goto _test_eof5;
case 5:
#line 295 "format-base.hpp"
	switch( (*(   data.p)) ) {
		case 46: goto tr26;
		case 119: goto tr28;
		case 125: goto tr29;
	}
	if ( 48 <= (*(   data.p)) && (*(   data.p)) <= 57 )
		goto st5;
	goto tr5;
tr28:
#line 13 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_precision(data, (   data.p)); }
	goto st6;
tr33:
#line 12 "format-base.hpp.rl"
	{ static_cast<T&>(*this).capture_width(data, (   data.p)); }
	goto st6;
st6:
	if ( ++(   data.p) == (  data.pe) )
		goto _test_eof6;
case 6:
#line 316 "format-base.hpp"
	if ( 48 <= (*(   data.p)) && (*(   data.p)) <= 57 )
		goto tr30;
	goto tr5;
tr30:
#line 7 "format-base.hpp.rl"
	{ static_cast<T&>(*this).mark(data, (   data.p)); }
	goto st7;
st7:
	if ( ++(   data.p) == (  data.pe) )
		goto _test_eof7;
case 7:
#line 328 "format-base.hpp"
	switch( (*(   data.p)) ) {
		case 46: goto tr31;
		case 119: goto tr33;
		case 125: goto tr34;
	}
	if ( 48 <= (*(   data.p)) && (*(   data.p)) <= 57 )
		goto st7;
	goto tr5;
	}
	_test_eof8: (  data.cs) = 8; goto _test_eof; 
	_test_eof9: (  data.cs) = 9; goto _test_eof; 
	_test_eof1: (  data.cs) = 1; goto _test_eof; 
	_test_eof2: (  data.cs) = 2; goto _test_eof; 
	_test_eof3: (  data.cs) = 3; goto _test_eof; 
	_test_eof4: (  data.cs) = 4; goto _test_eof; 
	_test_eof5: (  data.cs) = 5; goto _test_eof; 
	_test_eof6: (  data.cs) = 6; goto _test_eof; 
	_test_eof7: (  data.cs) = 7; goto _test_eof; 

	_test_eof: {}
	if ( (   data.p) == ( data.eof) )
	{
	switch ( (  data.cs) ) {
	case 9: 
#line 8 "format-base.hpp.rl"
	{ static_cast<T&>(*this).emit_text(data, (   data.p)); }
	break;
	case 2: 
	case 3: 
	case 4: 
	case 5: 
	case 6: 
	case 7: 
#line 14 "format-base.hpp.rl"
	{ static_cast<T&>(*this).argument_error(data); }
	break;
#line 365 "format-base.hpp"
	}
	}

	_out: {}
	}

#line 153 "format-base.hpp.rl"
      if (data.p == data.eof || data.cs == 
#line 374 "format-base.hpp"
0
#line 153 "format-base.hpp.rl"
)
        break;
    }
  }
};


}

#endif
