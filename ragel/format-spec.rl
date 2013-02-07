%%{
  machine format_spec;

  align = (
      '<' @FlagAlignLeft
    | '>' @FlagAlignRight
  );

  sign = (
      '+' @FlagSignPlus
    | ' ' @FlagSignSpace
  );

  type = (
      'c' @FlagChar
    | 'e' @FlagExponent
    | 'f' @FlagFixed
    | 'x' @FlagHex
    | 'E' @FlagUpperExponent
    | 'G' @FlagLargeExponent
    | 'X' @FlagUpperHex
    | '%' @FlagPercentage
  );

  misc = (
      '#' @FlagPrefixed
    | '0' @FlagZeroPadding
    | ',' @FlagComma
  );

  flags = (
      align
    | sign
    | type
    | misc
  );

  width = 'w' digit+ >Mark %CaptureWidth;
  precision = '.' digit+ >Mark %CapturePrecision;

  options = (
    ':'
    flags*
    width?
    precision?
  );

  argid = digit+ >Mark %CaptureArgument;

  field = (
      argid
    | argid options
    | options
  );

  text = [^{]+ >Mark %EmitText;
  open_bracket = '{' '{' @EmitOpenBracket;
  argument = '{' field? $!ArgumentError '}' @EmitArgument;

  main := (
      text
    | open_bracket
    | argument
  )**;

}%%
