// test: print array, array index
PROGRAM example(input, output, error);
    VAR a: INTEGER;
    VAR b: ARRAY[1..10] of ARRAY[1..20] of INTEGER;
BEGIN
  a := 5;
  b[a][2] := 2; // b[5][2] = 2
  b[a][a] := 5; // b[5][5] = 5
  writelnI(a);
  writelnI(b[3][2]);
  writelnI(b[5][2]);
  writelnI(b[a][2]); // b[5][2]
  writelnI(b[a][a]); // b[5][5]
  writelnI(b[b[a][a]][2]); // b[5][2]
END.
