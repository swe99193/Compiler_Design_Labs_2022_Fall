// test: no param call
PROGRAM example(input, output, error);
VAR a, b: INTEGER;
VAR c: REAL;

FUNCTION ss : INTEGER;
BEGIN
  ss := 5
END;

PROCEDURE tt;
BEGIN
    a := ss+3*ss;
END;

BEGIN
    a := ss*ss+ss;
    writelnI(a); // 30
    tt;tt;tt;
    writelnI(a) // 20
END.
