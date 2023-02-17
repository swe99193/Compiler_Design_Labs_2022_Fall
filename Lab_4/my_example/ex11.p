// test: NOT
PROGRAM example(input, output, error);
BEGIN
    writelnI(not 0); // true
    writelnI(not 3); // false
    writelnI(not (1-1)); // true
    writelnI(not (1+1)); // false
    writelnR(-1.0);
END.
