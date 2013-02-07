#include <iostream>

%%{
  machine format;

  action Mark              { mark = fpc; }
  action EmitText          { std::cout << "Text(" << std::string(mark, fpc - mark) << ")\n"; }
  action EmitOpenBracket   { std::cout << "OpenBracket\n"; }
  action EmitArgument      { std::cout << "Argument\n"; }
  action CaptureArgument   { std::cout << "      index: " << capture_integer(mark, fpc) << std::endl; }
  action CaptureWidth      { std::cout << "      width: " << capture_integer(mark, fpc) << std::endl; }
  action CapturePrecision  { std::cout << "  precision: " << capture_integer(mark, fpc) << std::endl; }
  action FlagAlignLeft     { std::cout << "       flag: AlignLeft" << std::endl; }
  action FlagAlignRight    { std::cout << "       flag: AlignRight" << std::endl; }
  action FlagSignPlus      { std::cout << "       flag: SignPlus" << std::endl; }
  action FlagSignSpace     { std::cout << "       flag: SignSpace" << std::endl; }
  action FlagChar          { std::cout << "       flag: Char" << std::endl; }
  action FlagExponent      { std::cout << "       flag: Exponent" << std::endl; }
  action FlagFixed         { std::cout << "       flag: Fixed" << std::endl; }
  action FlagHex           { std::cout << "       flag: Hex" << std::endl; }
  action FlagUpperHex      { std::cout << "       flag: UpperHex" << std::endl; }
  action FlagLargeExponent { std::cout << "       flag: LargeExponent" << std::endl; }
  action FlagUpperExponent { std::cout << "       flag: UpperExponent" << std::endl; }
  action FlagPercentage    { std::cout << "       flag: Percentage" << std::endl; }
  action FlagPrefixed      { std::cout << "       flag: Prefixed" << std::endl; }
  action FlagZeroPadding   { std::cout << "       flag: ZeroPadding" << std::endl; }
  action FlagComma         { std::cout << "       flag: Comma" << std::endl; }
  action ArgumentError     { std::cout << "Argument Error\n"; }
  action EndError          { std::cout << "End Error\n"; }

  include format_spec "../ragel/format-spec.rl";

}%%

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

%% write data;

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
      %% write exec;
      if (p == eof || cs == %%{ write error; }%%)
        break;
    }

  }

  return 0;
}
