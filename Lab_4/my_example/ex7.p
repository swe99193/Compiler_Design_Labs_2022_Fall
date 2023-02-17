// test: function local array
PROGRAM example(input, output, error);

PROCEDURE foo;
VAR a: ARRAY[0..1] of INTEGER;
BEGIN
  a[0] := 5;
  a[1] := 10;
  writelnI(a[0]);
  writelnI(a[1]);
END;

FUNCTION goo : INTEGER;
VAR a: ARRAY[0..1] of INTEGER;
BEGIN
  a[1] := 10;
  goo := a[1]
END;

BEGIN
    foo;
    writelnI(goo);
END.
