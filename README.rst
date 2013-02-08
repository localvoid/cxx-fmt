===============================
 C++ string formatting library
===============================

The library is in alpha state.

And currently doesn't support fast conversion of floating point
values, it is now using sprintf for this purposes.

Synopsis
--------

::

  #include <fmt/format.hpp>

  template<typename ...Args>
  uint32_t fmt::format(const char *out, const char *format, Args&& ... args);


Description
-----------

Format strings contain "placeholder fields" surrounded by curly braces
`{}`. Anything that is not contained in braces is considered literal
text. If you need to include a open brace character in the literal
text, it can be escaped by doubling: {{.

::

  fmt::format("Hello curly brace {{ and {}", "world");


Argument specification
++++++++++++++++++++++

::

  arg       = '{' arg_index? (':' flags* options*)? '}'
  arg_index = [0-9]+
  flags     = [<>+ cefoxEGX%#0,]
  options   = (width | precision)
  width     = 'w' [0-9]+
  precision = '.' [0-9]+

Flags
+++++

==== =================================================================
Flag Description
==== =================================================================
>    Align right
<    Align left
\+   A sign (+ or -) should always be placed before a number.
' '  A space should be placed before a positive number.
c    Convert to char
e    Exponent
f    Fixed
o    Octal
x    Hexadecimal
E    Upper Exponent
G    Large Exponent
X    Upper Hexadecimal
%    Percentage
#    Prefixed
0    Zero padding
,    Comma separator
==== =================================================================

Options
+++++++


Example
-------

::

  char buf[128];
  uint32_t size = fmt::format(buf, "format integer: {:X>w6}", 0xff);
  std::cout << std::string(buf, size) << std::endl;

should output: ``"format integer:   0xFF"``


Roadmap
-------

 - Native floating point conversion
 - Width flag for string values
 - Percentage flag
 - Unit Tests coverage

