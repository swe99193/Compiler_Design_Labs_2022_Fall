.class public test_procedure
.super java/lang/Object

.field public static a I
.field public static b I
.field public static c F
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic test_procedure/a I
	ldc 0
	putstatic test_procedure/b I
	ldc 0.0
	putstatic test_procedure/c F
	invokestatic test_procedure/ss()I
	invokestatic test_procedure/ss()I
	imul
	invokestatic test_procedure/ss()I
	iadd
	putstatic test_procedure/a I
	invokestatic test_procedure/tt()V
	invokestatic test_procedure/tt()V
	invokestatic test_procedure/tt()V
	getstatic test_procedure/a I
	invokestatic io/writelnI(I)V
	return
.end method

.method public static ss()I
	.limit locals 20
	.limit stack 100
	ldc 3
	ldc 4
	ldc 5
	imul
	iadd
	istore 19
	iload 19
	ireturn
.end method


.method public static tt()V
	.limit locals 20
	.limit stack 100
	invokestatic test_procedure/ss()I
	ldc 33
	invokestatic test_procedure/ss()I
	imul
	iadd
	getstatic test_procedure/a I
	iadd
	putstatic test_procedure/a I
	ldc 0.500000
	putstatic test_procedure/c F
	return
.end method

