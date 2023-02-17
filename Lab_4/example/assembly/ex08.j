.class public ex08
.super java/lang/Object

.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	invokestatic ex08/g()I
	invokestatic ex08/f(I)I
	invokestatic io/writelnI(I)V
	return
.end method

.method public static f(I)I
	.limit locals 20
	.limit stack 100
	iload 0
	istore 19
	iload 19
	ireturn
.end method


.method public static g()I
	.limit locals 20
	.limit stack 100
	ldc 1
	istore 19
	iload 19
	ireturn
.end method

