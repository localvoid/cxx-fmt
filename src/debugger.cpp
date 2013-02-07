
#line 1 "debugger.cpp.rl"
#include <iostream>


#line 33 "debugger.cpp.rl"


#include <cstdint>
#include <iostream>
#include <string.h>

namespace {

int capture_integer(const char *p, const char *fpc) {
  int i = 0;
  while (p != fpc) {
    i = i * 10 + (*p - '0');
    p++;
  }
  return i;
}


#line 26 "debugger.cpp"
static const int format_start = 8;
static const int format_first_final = 8;
static const int format_error = 0;

static const int format_en_main = 8;


#line 51 "debugger.cpp.rl"

}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cout << "Usage: fmt-debugger [FORMAT_STRING]" << std::endl;
  } else {

    int cs = 0;
    const char *p = argv[1];
    const char *pe = &p[strlen(argv[1])];
    const char *eof = pe;
    const char *mark = p;

    for(;;) {
      
#line 51 "debugger.cpp"
	{
	if ( p == pe )
		goto _test_eof;
	switch ( cs )
	{
tr3:
#line 8 "debugger.cpp.rl"
	{ std::cout << "OpenBracket\n"; }
	goto st8;
tr4:
#line 9 "debugger.cpp.rl"
	{ std::cout << "Argument\n"; }
	goto st8;
tr7:
#line 10 "debugger.cpp.rl"
	{ std::cout << "      index: " << capture_integer(mark, p) << std::endl; }
#line 9 "debugger.cpp.rl"
	{ std::cout << "Argument\n"; }
	goto st8;
tr27:
#line 12 "debugger.cpp.rl"
	{ std::cout << "  precision: " << capture_integer(mark, p) << std::endl; }
#line 9 "debugger.cpp.rl"
	{ std::cout << "Argument\n"; }
	goto st8;
tr31:
#line 11 "debugger.cpp.rl"
	{ std::cout << "      width: " << capture_integer(mark, p) << std::endl; }
#line 9 "debugger.cpp.rl"
	{ std::cout << "Argument\n"; }
	goto st8;
st8:
	if ( ++p == pe )
		goto _test_eof8;
case 8:
#line 87 "debugger.cpp"
	if ( (*p) == 123 )
		goto st1;
	goto tr32;
tr32:
#line 6 "debugger.cpp.rl"
	{ mark = p; }
	goto st9;
st9:
	if ( ++p == pe )
		goto _test_eof9;
case 9:
#line 99 "debugger.cpp"
	if ( (*p) == 123 )
		goto tr35;
	goto st9;
tr35:
#line 7 "debugger.cpp.rl"
	{ std::cout << "Text(" << std::string(mark, p - mark) << ")\n"; }
	goto st1;
st1:
	if ( ++p == pe )
		goto _test_eof1;
case 1:
#line 111 "debugger.cpp"
	switch( (*p) ) {
		case 58: goto st3;
		case 123: goto tr3;
		case 125: goto tr4;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr1;
	goto tr0;
tr0:
#line 28 "debugger.cpp.rl"
	{ std::cout << "Argument Error\n"; }
	goto st0;
#line 124 "debugger.cpp"
st0:
cs = 0;
	goto _out;
tr1:
#line 6 "debugger.cpp.rl"
	{ mark = p; }
	goto st2;
st2:
	if ( ++p == pe )
		goto _test_eof2;
case 2:
#line 136 "debugger.cpp"
	switch( (*p) ) {
		case 58: goto tr6;
		case 125: goto tr7;
	}
	if ( 48 <= (*p) && (*p) <= 57 )
		goto st2;
	goto tr0;
tr6:
#line 10 "debugger.cpp.rl"
	{ std::cout << "      index: " << capture_integer(mark, p) << std::endl; }
	goto st3;
tr8:
#line 16 "debugger.cpp.rl"
	{ std::cout << "       flag: SignSpace" << std::endl; }
	goto st3;
tr9:
#line 25 "debugger.cpp.rl"
	{ std::cout << "       flag: Prefixed" << std::endl; }
	goto st3;
tr10:
#line 24 "debugger.cpp.rl"
	{ std::cout << "       flag: Percentage" << std::endl; }
	goto st3;
tr11:
#line 15 "debugger.cpp.rl"
	{ std::cout << "       flag: SignPlus" << std::endl; }
	goto st3;
tr12:
#line 27 "debugger.cpp.rl"
	{ std::cout << "       flag: Comma" << std::endl; }
	goto st3;
tr14:
#line 26 "debugger.cpp.rl"
	{ std::cout << "       flag: ZeroPadding" << std::endl; }
	goto st3;
tr15:
#line 13 "debugger.cpp.rl"
	{ std::cout << "       flag: AlignLeft" << std::endl; }
	goto st3;
tr16:
#line 14 "debugger.cpp.rl"
	{ std::cout << "       flag: AlignRight" << std::endl; }
	goto st3;
tr17:
#line 23 "debugger.cpp.rl"
	{ std::cout << "       flag: UpperExponent" << std::endl; }
	goto st3;
tr18:
#line 22 "debugger.cpp.rl"
	{ std::cout << "       flag: LargeExponent" << std::endl; }
	goto st3;
tr19:
#line 21 "debugger.cpp.rl"
	{ std::cout << "       flag: UpperHex" << std::endl; }
	goto st3;
tr20:
#line 17 "debugger.cpp.rl"
	{ std::cout << "       flag: Char" << std::endl; }
	goto st3;
tr21:
#line 18 "debugger.cpp.rl"
	{ std::cout << "       flag: Exponent" << std::endl; }
	goto st3;
tr22:
#line 19 "debugger.cpp.rl"
	{ std::cout << "       flag: Fixed" << std::endl; }
	goto st3;
tr24:
#line 20 "debugger.cpp.rl"
	{ std::cout << "       flag: Hex" << std::endl; }
	goto st3;
st3:
	if ( ++p == pe )
		goto _test_eof3;
case 3:
#line 212 "debugger.cpp"
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
#line 11 "debugger.cpp.rl"
	{ std::cout << "      width: " << capture_integer(mark, p) << std::endl; }
	goto st4;
st4:
	if ( ++p == pe )
		goto _test_eof4;
case 4:
#line 242 "debugger.cpp"
	if ( 48 <= (*p) && (*p) <= 57 )
		goto tr25;
	goto tr0;
tr25:
#line 6 "debugger.cpp.rl"
	{ mark = p; }
	goto st5;
st5:
	if ( ++p == pe )
		goto _test_eof5;
case 5:
#line 254 "debugger.cpp"
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
#line 6 "debugger.cpp.rl"
	{ mark = p; }
	goto st7;
st7:
	if ( ++p == pe )
		goto _test_eof7;
case 7:
#line 275 "debugger.cpp"
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
#line 7 "debugger.cpp.rl"
	{ std::cout << "Text(" << std::string(mark, p - mark) << ")\n"; }
	break;
	case 1: 
	case 2: 
	case 3: 
	case 4: 
	case 5: 
	case 6: 
	case 7: 
#line 28 "debugger.cpp.rl"
	{ std::cout << "Argument Error\n"; }
	break;
#line 312 "debugger.cpp"
	}
	}

	_out: {}
	}

#line 67 "debugger.cpp.rl"
      if (p == eof || cs == 
#line 321 "debugger.cpp"
0
#line 67 "debugger.cpp.rl"
)
        break;
    }

  }

  return 0;
}
