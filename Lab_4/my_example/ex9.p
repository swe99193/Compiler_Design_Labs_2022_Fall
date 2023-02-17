// test: simple while
PROGRAM example(input, output, error);
    VAR a: integer;
BEGIN
    WHILE a != 5 DO
    BEGIN
        writelnI(a);
        a := a + 1;
    END;
END.
