.class public test1
.super java/lang/Object

.field public static a I
.field public static b I
.field public static c I
.field public static u I
.field public static d [I
.field public static e [F
.field public static g F
.field public static h F
.field public static x F
.field public static k [[F
.field public static l [[I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic test1/a I
	ldc 0
	putstatic test1/b I
	ldc 0
	putstatic test1/c I
	ldc 0
	putstatic test1/u I
	ldc 10
	multianewarray [I 1
	putstatic test1/d [I
	ldc 10
	multianewarray [F 1
	putstatic test1/e [F
	ldc 0.0
	putstatic test1/g F
	ldc 0.0
	putstatic test1/h F
	ldc 0.0
	putstatic test1/x F
	ldc 35
	ldc 35
	multianewarray [[F 2
	putstatic test1/k [[F
	ldc 35
	ldc 35
	multianewarray [[I 2
	putstatic test1/l [[I
	ldc 8
	ldc 8
	invokestatic test1/addition(II)I
	putstatic test1/c I
	getstatic test1/c I
	invokestatic io/writelnI(I)V
	ldc -8
	ldc -8
	invokestatic test1/addition(II)I
	putstatic test1/c I
	getstatic test1/c I
	invokestatic io/writelnI(I)V
	ldc 3.300000
	ldc 5.500000
	invokestatic test1/ggyy(FF)F
	putstatic test1/x F
	getstatic test1/x F
	invokestatic io/writelnR(F)V
	ldc 0
	putstatic test1/b I
	getstatic test1/b I
	getstatic test1/a I
	if_icmpgt TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
ifne IF_0
	ldc 222
	putstatic test1/a I
	goto ENDIF_0
IF_0:
	ldc 111
	putstatic test1/a I
ENDIF_0:
	getstatic test1/a I
	invokestatic io/writelnI(I)V
	getstatic test1/b I
	getstatic test1/a I
	if_icmplt TRUE_3
	ldc 0
	goto END_relop_3
TRUE_3:
	ldc 1
END_relop_3:
ifne IF_2
	ldc 222
	putstatic test1/a I
	goto ENDIF_2
IF_2:
	ldc 111
	putstatic test1/a I
ENDIF_2:
	getstatic test1/a I
	invokestatic io/writelnI(I)V
	getstatic test1/b I
	getstatic test1/a I
	if_icmpeq TRUE_5
	ldc 0
	goto END_relop_5
TRUE_5:
	ldc 1
END_relop_5:
ifne IF_4
	ldc 222
	putstatic test1/a I
	goto ENDIF_4
IF_4:
	ldc 111
	putstatic test1/a I
ENDIF_4:
	getstatic test1/a I
	invokestatic io/writelnI(I)V
	getstatic test1/b I
	getstatic test1/a I
	if_icmpge TRUE_7
	ldc 0
	goto END_relop_7
TRUE_7:
	ldc 1
END_relop_7:
ifne IF_6
	ldc 222
	putstatic test1/a I
	goto ENDIF_6
IF_6:
	ldc 111
	putstatic test1/a I
ENDIF_6:
	getstatic test1/a I
	invokestatic io/writelnI(I)V
	getstatic test1/b I
	getstatic test1/a I
	if_icmple TRUE_9
	ldc 0
	goto END_relop_9
TRUE_9:
	ldc 1
END_relop_9:
ifne IF_8
	ldc 222
	putstatic test1/a I
	goto ENDIF_8
IF_8:
	ldc 111
	putstatic test1/a I
ENDIF_8:
	getstatic test1/a I
	invokestatic io/writelnI(I)V
	getstatic test1/b I
	ldc 0
	if_icmpne TRUE_11
	ldc 0
	goto END_relop_11
TRUE_11:
	ldc 1
END_relop_11:
ifne IF_10
	ldc 222
	putstatic test1/a I
	goto ENDIF_10
IF_10:
	ldc 111
	putstatic test1/a I
ENDIF_10:
	getstatic test1/a I
	invokestatic io/writelnI(I)V
	ldc 1
	putstatic test1/a I
	goto COND_12
WHILE_12:
	getstatic test1/a I
	invokestatic io/writelnI(I)V
	getstatic test1/a I
	ldc 1
	iadd
	putstatic test1/a I
COND_12:
	getstatic test1/a I
	ldc 5
	if_icmplt TRUE_13
	ldc 0
	goto END_relop_13
TRUE_13:
	ldc 1
END_relop_13:
ifne WHILE_12
	ldc 1
	putstatic test1/b I
	goto COND_14
WHILE_14:
	getstatic test1/b I
	getstatic test1/b I
	getstatic test1/b I
	ldc 3
	iadd
	imul
	iadd
	getstatic test1/d [I
	swap
	getstatic test1/b I
	ldc 1
	isub
	swap
	iastore
	getstatic test1/b I
	ldc 1
	iadd
	putstatic test1/b I
COND_14:
	getstatic test1/b I
	ldc 11
	if_icmplt TRUE_15
	ldc 0
	goto END_relop_15
TRUE_15:
	ldc 1
END_relop_15:
ifne WHILE_14
	ldc 9.990000
	getstatic test1/e [F
	swap
	ldc 3
	ldc 1
	isub
	swap
	fastore
	ldc 3.140000
	getstatic test1/k [[F
	ldc 25
	ldc 23
	isub
	aaload
	swap
	ldc 26
	ldc 23
	isub
	swap
	fastore
	ldc 88
	getstatic test1/l [[I
	ldc 28
	ldc 23
	isub
	aaload
	swap
	ldc 26
	ldc 23
	isub
	swap
	iastore
	getstatic test1/a I
	invokestatic io/writelnI(I)V
	getstatic test1/d [I
	ldc 5
	ldc 1
	isub
	iaload
	putstatic test1/u I
	getstatic test1/u I
	invokestatic io/writelnI(I)V
	getstatic test1/e [F
	ldc 3
	ldc 1
	isub
	faload
	putstatic test1/g F
	getstatic test1/g F
	invokestatic io/writelnR(F)V
	getstatic test1/k [[F
	ldc 25
	ldc 23
	isub
	aaload
	ldc 26
	ldc 23
	isub
	faload
	putstatic test1/g F
	getstatic test1/g F
	invokestatic io/writelnR(F)V
	getstatic test1/l [[I
	ldc 28
	ldc 23
	isub
	aaload
	ldc 26
	ldc 23
	isub
	iaload
	putstatic test1/u I
	getstatic test1/u I
	invokestatic io/writelnI(I)V
	ldc 9
	ldc 9
	iadd
	ldc 10
	isub
	putstatic test1/u I
	getstatic test1/u I
	invokestatic io/writelnI(I)V
	ldc 9
	ldc 9
	iadd
	ldc 3
	idiv
	ldc 5
	ldc 2
	imul
	iadd
	ldc 1
	isub
	getstatic test1/u I
	iadd
	putstatic test1/u I
	getstatic test1/u I
	invokestatic io/writelnI(I)V
	return
.end method

.method public static sort([I)V
	.limit locals 20
	.limit stack 100
	ldc 0
	istore 1
	iload 1
	putstatic test1/c I
	return
.end method


.method public static addition(II)I
	.limit locals 20
	.limit stack 100
	iload 0
	iload 1
	iadd
	istore 19
	iload 19
	ireturn
.end method


.method public static ggyy(FF)F
	.limit locals 20
	.limit stack 100
	fload 0
	fload 1
	fadd
	fstore 19
	fload 19
	freturn
.end method

