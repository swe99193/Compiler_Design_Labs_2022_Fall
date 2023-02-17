// test: read input
PROGRAM example(input, output, error);
    VAR a:integer;
    VAR b: ARRAY[0..1] of ARRAY[0..1] of INTEGER;
BEGIN
    a := readlnI;
    writelnI(a);
    b[0][0] := readlnI;
    writelnI(b[0][0]);
    writelnI(b[0][1]);
END.
