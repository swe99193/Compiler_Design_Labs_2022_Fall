# jasmin assembly
## directive statements
directive names
```
.catch .class .end .field .implements .interface .limit .line
.method .source .super .throws .var
```
directive statements
```
.limit stack 10
.method public myMethod()V
.class Foo

```

## main function (beginning)
```
.limit locals 100
.limit stack 100
```

## main function (initialize global variables)
```
?
```

## print(var)
```
writeln(var)
```
```
getstatic java/lang/System/out Ljava/io/PrintStream;
getstatic foo/var I
invokestatic java/lang/String/valueOf(I)Ljava/lang/String;
invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V
```

## call function with args and store to var

```
var = addition(a, 8)
```
```
getstatic foo/a I
ldc 8
invokestatic foo/addition(II)I // call
putstatic foo/var I
```

## print expression or function call
```
writeln(addition(8, 8))
```
```
invokestatic foo/addition(II)I
invokestatic io/writelnI(I)V
```

```
writeln(a)
```
```
getstatic foo/a I
invokestatic io/writelnI(I)V
```

```
a = readlnI
```
```
invokestatic io/readlnI()I
putstatic foo/a I
```

## access function arguments and local var
```
function(int a, int b)
var c
```
```
iload 0 // a is var#0 (value passed from outside)
iload 1 // b is var#1 (value passed from outside)
iload 2 // c is var#2
```

## function return value
```
return x
```
```
iload 1 // x is var#1
ireturn
```


## load variables
global var
```
getstatic foo/b I
```
local var
```
iload 1
```

## store variables
```
b = 111;
```
global var
```
ldc 111
putstatic foo/b I
```
local var
```
ldc 111
istore 1 // b is var#1
```


## load & store & print array
note: 
* jasmin array is 0-based
### global array
```
var d: array [ 1 .. 10 ] of integer; 
d[b] := b + b * (b + 3)
```
```
	getstatic foo/d [I
	getstatic foo/b I
	ldc 1   // undo the offset
	isub
	getstatic foo/b I
	getstatic foo/b I
	getstatic foo/b I
	ldc 3
	iadd
	imul
	iadd
	iastore // assignment to ia (int array)
```

ref: example/external_io/ex09.j
```
VAR b: ARRAY[1..2] of INTEGER;
arr[1] = 10
writelnI(arr[1])
```
```
    getstatic ex09/a [I
    ldc 2
    ldc 1
    isub
    ldc 1
    iastore

    getstatic ex09/arr [I
    ldc 2
    ldc 1
    isub
    iaload
    invokestatic io/writelnI(I)V
```

ref: example/external_io/ex09.j
```
VAR b: ARRAY[1..2] of ARRAY[1..2] of INTEGER;
arr[1][2] = 10
writelnI(arr[1][2])
```
```
    getstatic foo/arr [[I
    ldc 1
    ldc 1
    isub
    aaload
    ldc 2
    ldc 1
    isub
    ldc 10
    iastore

    getstatic ex09/b [[I
    ldc 1
    ldc 1
    isub
    aaload
    ldc 2
    ldc 1
    isub
    iaload
    invokestatic io/writelnI(I)V
```
### local array
```
.method public static addition(II)I
	.limit locals 100
	.limit stack 100
	ldc 5
	ldc 5
	multianewarray [[I 2
	astore 3
			; init arr[5][5]
	aload 3
	ldc 1
    aaload
    ldc 3
    ldc 9919
    iastore
			; a[1][3] = 9919
	aload 3
	ldc 1
	aaload
	ldc 3
	iaload
			; load arr[1][3]
	invokestatic io/writelnI(I)V
.end method
```

## arithm op
(tmp var) = 2 - 1
```
ldc 2
ldc 1
isub
```

## ifelse
```
if(EXPR1 == EXPR2)
then
    STMT1
else
    STMT2
```
v1
```
    EXPR1
    EXPR2
    if_icmpeq IF
    ELSE_STMT
    goto ENDIF
IF:
    IF_STMT
ENDIF:
```
v2
```
    EXPR1 == EXPR2
    ifne IF
    ELSE_STMT
    goto ENDIF
IF:
    IF_STMT
ENDIF:
```

## while
```
while(EXPR1 == EXPR2){
    STMT
}
```
v1
```
    goto COND
WHILE:
    STMT
COND:
    EXPR1
    EXPR2
    if_icmpeq WHILE
```
v2
```
    goto COND
WHILE:
    STMT
COND:
    EXPR1 == EXPR2
    ifne WHILE
```

## <, >, <=, >=,  ==, !=
* leave `1(true)` or `0(false)` on the stack top
```
EXPR1 == EXPR2
```
```
    EXPR1
    EXPR2
    if_icmpeq TRUE
    ldc 0
    goto END_relop
TRUE:
    ldc 1
END_relop:
```
(float)
```
    EXPR1
    EXPR2

>
    fcmpg
    ldc 1
    if_icmpeq TRUE

<
    fcmpg
    ldc -1
    if_icmpeq TRUE

<=
    fcmpg
    ldc 1
    if_icmplt TRUE

>=
    fcmpg
    ldc -1
    if_icmpgt TRUE

==
    fcmpg
    ldc 0
    if_icmpeq TRUE

!=
    fcmpg
    ldc 0
    if_icmpne TRUE

            // (one of the above blocks)
    ldc 0
    goto END_relop
TRUE:
    ldc 1
END_relop:
```

## AND, OR, NOT
* leave `1(true)` or `0(false)` on the stack top
```
NOT(EXPR)
```
```
    EXPR
    ifeq TRUE
    ldc 0
    goto END_bool
TRUE:
    ldc 1
END_bool:
```

## string
### string concatenation
```
    writelnS("abc" + " xyz")
```
```
	new java/lang/StringBuffer
	dup
	invokespecial java/lang/StringBuffer/<init>()V
	ldc "abc"
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	ldc " xyz"
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	invokevirtual java/lang/StringBuffer/toString()Ljava/lang/String;
    invokestatic io/writelnS(Ljava/lang/String;)V
```
### string assignment
```
    a = "xyz"
```
global string
```
	ldc " xyz"
    putstatic example/a Ljava/lang/String;
```

## Misc.
semicolon must be preceded by a whitespace character
```
abc ;def // "abd" & "def"
```