.class public fibonacci_recursive
.super java/lang/Object

.field public static a I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic fibonacci_recursive/a I
	invokestatic io/readlnI()I
	putstatic fibonacci_recursive/a I
	getstatic fibonacci_recursive/a I
	invokestatic fibonacci_recursive/fa(I)I
	invokestatic io/writelnI(I)V
	return
.end method

.method public static fa(I)I
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
	ldc 0
	if_icmpeq TRUE_3
	ldc 0
	goto END_relop_3
TRUE_3:
	ldc 1
END_relop_3:
ifne IF_2
	iload 0
	ldc 1
	isub
	invokestatic fibonacci_recursive/fa(I)I
	iload 0
	ldc 2
	isub
	invokestatic fibonacci_recursive/fa(I)I
	iadd
	istore 19
	goto ENDIF_2
IF_2:
	ldc 0
	istore 19
ENDIF_2:
	goto ENDIF_0
IF_0:
	ldc 1
	istore 19
ENDIF_0:
	iload 19
	ireturn
.end method

