.class public test_combination
.super java/lang/Object

.field public static a I
.field public static b I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic test_combination/a I
	ldc 0
	putstatic test_combination/b I
	ldc 3
	putstatic test_combination/a I
	ldc 4
	putstatic test_combination/b I
	getstatic test_combination/a I
	ldc 3
	iadd
	getstatic test_combination/b I
	ldc 2
	isub
	invokestatic test_combination/comb(II)I
	invokestatic io/writelnI(I)V
	return
.end method

.method public static comb(II)I
	.limit locals 20
	.limit stack 100
	iload 0
	iload 1
	if_icmpgt TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
ifne IF_0
	ldc 1
	istore 19
	goto ENDIF_0
IF_0:
	iload 0
	ldc 1
	if_icmpeq TRUE_3
	ldc 0
	goto END_relop_3
TRUE_3:
	ldc 1
END_relop_3:
ifne IF_2
	iload 0
	ldc 0
	if_icmpgt TRUE_5
	ldc 0
	goto END_relop_5
TRUE_5:
	ldc 1
END_relop_5:
ifne IF_4
	ldc 0
	istore 19
	goto ENDIF_4
IF_4:
	iload 1
	ldc 0
	if_icmpgt TRUE_7
	ldc 0
	goto END_relop_7
TRUE_7:
	ldc 1
END_relop_7:
ifne IF_6
	ldc 1
	istore 19
	goto ENDIF_6
IF_6:
	iload 0
	ldc 1
	isub
	iload 1
	ldc 1
	isub
	invokestatic test_combination/comb(II)I
	iload 0
	ldc 1
	isub
	iload 1
	invokestatic test_combination/comb(II)I
	iadd
	istore 19
ENDIF_6:
ENDIF_4:
	goto ENDIF_2
IF_2:
	ldc 1
	istore 19
ENDIF_2:
ENDIF_0:
	iload 19
	ireturn
.end method

