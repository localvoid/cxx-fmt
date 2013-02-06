#include <cstdint>
#include <iostream>
#include <string.h>

#include <fmt/format-base.hpp>

namespace fmt {

std::ostream& operator<<(std::ostream& os, const Flag& f) {
  if (f & Flag::AlignLeft)
    os << "align left";
  else if (f & Flag::AlignRight)
    os << "align right";
  else if (f & Flag::AlignCentered)
    os << "align centered";
  else if (f & Flag::SignPlus)
    os << "sign plus";
  else if (f & Flag::SignSpace)
    os << "sign space";
  else if (f & Flag::Char)
    os << "char";
  else if (f & Flag::Hex)
    os << "hex";
  else if (f & Flag::UpperHex)
    os << "upper hex";
  else if (f & Flag::Exponent)
    os << "exponent";
  else if (f & Flag::UpperExponent)
    os << "upper exponent";
  else if (f & Flag::Fixed)
    os << "fixed";
  else if (f & Flag::LargeExponent)
    os << "large exponent";
  else if (f & Flag::Percentage)
    os << "percentage";
  else if (f & Flag::Prefixed)
    os << "prefixed";
  else if (f & Flag::CommaSeparator)
    os << "comma separator";
  return os;
}

class FormatDebugger : public FormatBase<FormatDebugger> {
public:
  void mark(Data &d, const char *fpc) {
    std::cout << "Mark\n";
    FormatBase::mark(d, fpc);
  }

  void capture_precision(Data &d, const char *fpc) {
    int i = capture_integer(d, fpc);
    std::cout << "  precision: " << i << std::endl;
  }

  void capture_width(Data &d, const char *fpc) {
    int i = capture_integer(d, fpc);
    std::cout << "  width: " << i << std::endl;
  }

  void capture_argument(Data &d, const char *fpc) {
    int i = capture_integer(d, fpc);
    std::cout << "  argument: " << i << std::endl;
  }

  void set_flag(Data &d, Flag v) {
    std::cout << "  flag: " << v << std::endl;
  }

  void emit_text(Data &d, const char *end) {
    std::string s(d.mark, end - d.mark);
    std::cout << "Text(" << s << ")\n";
  }

  void emit_open_bracket(Data &d) {
    std::cout << "OpenBracket\n";
  }

  void emit_argument(Data &d) {
    std::cout << "Argument\n";
  }

  void argument_error(Data &d) {
    std::cout << "Argument Error\n";
  }

  void end_error(Data &d) {
    std::cout << "End Error\n";
  }
};

}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cout << "Usage: fmt-debugger [FORMAT_STRING]" << std::endl;
  } else {
    fmt::FormatDebugger f;
    f(argv[1], strlen(argv[1]));
  }

  return 0;
}
