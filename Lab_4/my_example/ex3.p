// test: simple function & procedure
PROGRAM example(input, output, error);
    FUNCTION g :integer;
    begin
        g := 30/5+3;
    end;
    FUNCTION f(a:integer) :integer;
    begin
        f := g;
    end;
BEGIN
    writelnI(f(g));
END.
