.class public test2
.super java/lang/Object

.field public static aa I
.field public static bb I
.field public static cc I
.field public static g [[[I
.field public static r [[I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic test2/aa I
	ldc 0
	putstatic test2/bb I
	ldc 0
	putstatic test2/cc I
	ldc 2
	ldc 2
	ldc 2
	multianewarray [[[I 3
	putstatic test2/g [[[I
	ldc 2
	ldc 2
	multianewarray [[I 2
	putstatic test2/r [[I
	getstatic test2/aa I
	ldc 3
	getstatic test2/bb I
	imul
	iadd
	ldc 4
	ldc 2
	idiv
	isub
	putstatic test2/aa I
	getstatic test2/aa I
	invokestatic io/writelnI(I)V
	getstatic test2/bb I
	invokestatic io/writelnI(I)V
	getstatic test2/aa I
	getstatic test2/bb I
	if_icmple TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
ifne IF_0
	ldc 222
	putstatic test2/aa I
	goto ENDIF_0
IF_0:
	getstatic test2/aa I
	ldc 0
	if_icmplt TRUE_3
	ldc 0
	goto END_relop_3
TRUE_3:
	ldc 1
END_relop_3:
ifne IF_2
	ldc 111
	putstatic test2/aa I
	goto ENDIF_2
IF_2:
	ldc 333
	putstatic test2/aa I
ENDIF_2:
ENDIF_0:
	getstatic test2/aa I
	invokestatic io/writelnI(I)V
	goto COND_4
WHILE_4:
	ldc 0
	putstatic test2/aa I
	goto COND_5
WHILE_5:
	getstatic test2/aa I
	ldc 1
	iadd
	putstatic test2/aa I
COND_5:
	getstatic test2/aa I
	ldc 5
	if_icmplt TRUE_6
	ldc 0
	goto END_relop_6
TRUE_6:
	ldc 1
END_relop_6:
ifne WHILE_5
	getstatic test2/bb I
	ldc 1
	iadd
	putstatic test2/bb I
	getstatic test2/bb I
	invokestatic io/writelnI(I)V
COND_4:
	getstatic test2/bb I
	ldc 5
	if_icmplt TRUE_7
	ldc 0
	goto END_relop_7
TRUE_7:
	ldc 1
END_relop_7:
ifne WHILE_4
	getstatic test2/aa I
	getstatic test2/r [[I
	ldc 1
	ldc 0
	isub
	aaload
	ldc 4
	ldc 4
	isub
	iaload
	iadd
	ldc 2
	ldc 3
	ldc 4.000000
	ldc 6.500000
	invokestatic test2/tt(IIFF)I
	iadd
	getstatic test2/g [[[I
	ldc 0
	ldc 0
	isub
	aaload
	ldc 3
	ldc 2
	isub
	aaload
	swap
	ldc 4
	ldc 4
	isub
	swap
	iastore
	getstatic test2/g [[[I
	ldc 0
	ldc 0
	isub
	aaload
	ldc 3
	ldc 2
	isub
	aaload
	ldc 4
	ldc 4
	isub
	iaload
	invokestatic io/writelnI(I)V
	return
.end method

.method public static ss()V
	.limit locals 20
	.limit stack 100
	ldc 0
	istore 0
	return
.end method


.method public static tt(IIFF)I
	.limit locals 20
	.limit stack 100
	ldc 0
	istore 4
	ldc 3
	ldc 4
	ldc 5
	imul
	iadd
	istore 4
	iload 4
	invokestatic io/writelnI(I)V
	iload 0
	ldc 5
	iadd
	istore 19
	iload 19
	ireturn
.end method

