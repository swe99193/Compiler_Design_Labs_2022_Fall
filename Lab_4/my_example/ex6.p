// test: pass array to function
PROGRAM example(input, output, error);
VAR a: ARRAY[0..1] of ARRAY[0..1] of INTEGER;

FUNCTION slice(s :ARRAY[3..4] of INTEGER) : INTEGER;
BEGIN
  slice := s[3] + s[4]
END;

BEGIN
  a[0][0] := 1;
  a[0][1] := 3;

  writelnI(slice(a[0]))
END.
