// test: string
PROGRAM example(input, output, error);
    Var a, str:string;
BEGIN
    writelnS("3");
    writelnS("heyy yoo");
    writelnS(str); // empty string
    writelnS("ab" + " cde xyz"); // "ab cde xyz"
    str := "rabbit";
    writelnS("assigned str: " + str);
    writelnS(str + " :mid: " + str + str)
END.
