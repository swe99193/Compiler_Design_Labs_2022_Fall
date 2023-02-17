.class public test_array_assignment
.super java/lang/Object

.field public static a [I
.field public static b I
.field public static c [[I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 5
	multianewarray [I 1
	putstatic test_array_assignment/a [I
	ldc 0
	putstatic test_array_assignment/b I
	ldc 2
	ldc 5
	multianewarray [[I 2
	putstatic test_array_assignment/c [[I
	ldc "a[1..5]:"
	invokestatic io/writelnS(Ljava/lang/String;)V
	ldc 1
	putstatic test_array_assignment/b I
	goto COND_0
WHILE_0:
	getstatic test_array_assignment/b I
	ldc 1
	iadd
	getstatic test_array_assignment/a [I
	swap
	getstatic test_array_assignment/b I
	ldc 1
	isub
	swap
	iastore
	getstatic test_array_assignment/a [I
	getstatic test_array_assignment/b I
	ldc 1
	isub
	iaload
	invokestatic io/writelnI(I)V
	getstatic test_array_assignment/b I
	ldc 1
	iadd
	putstatic test_array_assignment/b I
COND_0:
	getstatic test_array_assignment/b I
	ldc 5
	if_icmple TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
ifne WHILE_0
	ldc "c[1][1..5]:"
	invokestatic io/writelnS(Ljava/lang/String;)V
	ldc 1
	putstatic test_array_assignment/b I
	goto COND_2
WHILE_2:
	getstatic test_array_assignment/c [[I
	ldc 1
	ldc 1
	isub
	aaload
	getstatic test_array_assignment/b I
	ldc 1
	isub
	iaload
	invokestatic io/writelnI(I)V
	getstatic test_array_assignment/b I
	ldc 1
	iadd
	putstatic test_array_assignment/b I
COND_2:
	getstatic test_array_assignment/b I
	ldc 5
	if_icmple TRUE_3
	ldc 0
	goto END_relop_3
TRUE_3:
	ldc 1
END_relop_3:
ifne WHILE_2
	ldc "c[1] := a[1..5];"
	invokestatic io/writelnS(Ljava/lang/String;)V
	getstatic test_array_assignment/a [I
	getstatic test_array_assignment/c [[I
	ldc 1
	ldc 1
	isub
	aaload
	swap
	iastore
	ldc "c[1][1..5]:"
	invokestatic io/writelnS(Ljava/lang/String;)V
	ldc 1
	putstatic test_array_assignment/b I
	goto COND_4
WHILE_4:
	getstatic test_array_assignment/c [[I
	ldc 1
	ldc 1
	isub
	aaload
	getstatic test_array_assignment/b I
	ldc 1
	isub
	iaload
	invokestatic io/writelnI(I)V
	getstatic test_array_assignment/b I
	ldc 1
	iadd
	putstatic test_array_assignment/b I
COND_4:
	getstatic test_array_assignment/b I
	ldc 5
	if_icmple TRUE_5
	ldc 0
	goto END_relop_5
TRUE_5:
	ldc 1
END_relop_5:
ifne WHILE_4
	ldc "a[1] := 100;"
	invokestatic io/writelnS(Ljava/lang/String;)V
	ldc 100
	getstatic test_array_assignment/a [I
	swap
	ldc 1
	ldc 1
	isub
	swap
	iastore
	ldc "c[1][1..5]:"
	invokestatic io/writelnS(Ljava/lang/String;)V
	ldc 1
	putstatic test_array_assignment/b I
	goto COND_6
WHILE_6:
	getstatic test_array_assignment/c [[I
	ldc 1
	ldc 1
	isub
	aaload
	getstatic test_array_assignment/b I
	ldc 1
	isub
	iaload
	invokestatic io/writelnI(I)V
	getstatic test_array_assignment/b I
	ldc 1
	iadd
	putstatic test_array_assignment/b I
COND_6:
	getstatic test_array_assignment/b I
	ldc 5
	if_icmple TRUE_7
	ldc 0
	goto END_relop_7
TRUE_7:
	ldc 1
END_relop_7:
ifne WHILE_6
	return
.end method
