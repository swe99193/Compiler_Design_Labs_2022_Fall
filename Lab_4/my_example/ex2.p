// test: arithmetic associativity
PROGRAM example(input, output, error);
    VAR a, b:integer;
BEGIN
    a := 2;
    b := 5;
    a := (a*(b-3) + 6)*2 / 5;
    writelnI(a);
END.
