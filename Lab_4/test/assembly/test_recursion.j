.class public test_recursion
.super java/lang/Object

.field public static a I
.field public static b I
.field public static c F
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic test_recursion/a I
	ldc 0
	putstatic test_recursion/b I
	ldc 0.0
	putstatic test_recursion/c F
	ldc 4
	invokestatic test_recursion/fact(I)I
	putstatic test_recursion/a I
	getstatic test_recursion/a I
	invokestatic io/writelnI(I)V
	return
.end method

.method public static fact(I)I
	.limit locals 20
	.limit stack 100
	iload 0
	ldc 1
	if_icmpeq TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
ifne IF_0
	iload 0
	iload 0
	ldc 1
	isub
	invokestatic test_recursion/fact(I)I
	imul
	istore 19
	goto ENDIF_0
IF_0:
	iload 0
	istore 19
ENDIF_0:
	iload 19
	ireturn
.end method

