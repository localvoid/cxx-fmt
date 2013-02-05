===============================
 C++ string formatting library
===============================

The library is currently work in progress.

Format syntax
-------------

Format strings contain "placeholder fields" surrounded by curly braces
`{}`. Anything that is not contained in braces is considered literal
text. If you need to include a open brace character in the literal
text, it can be escaped by doubling: {{.

::
  fmt::format("Hello curly brace {{ and {}", "world");


Argument specification
++++++++++++++++++++++

::
  argument_index? (':' flags* options*)?

Flags
+++++

Alignment
^^^^^^^^^

- > - right
- < - left
- ^ - centered
- = - numeric

Sign
^^^^

- +   - plus
- ' ' - space

Type Conversion
^^^^^^^^^^^^^^^

- c - char
- e - exponent
- f - fixed
- n - localized
- o - octal
- x - hex
- E - upper exponent
- G - large exponent
- X - upper hex
- % - percentage

Misc
^^^^

- # - prefixed
- 0 - zero padding
- , - comma separator

Options
+++++++

- w[0-9]+ - width
- .[0-9]+ - precision

Example
-------

::
  fmt::format("format integer: {:X>w6}", 0xff);

should output: "format integer:   0xFF"
