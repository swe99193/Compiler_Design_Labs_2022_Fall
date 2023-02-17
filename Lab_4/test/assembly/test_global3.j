.class public test_global3
.super java/lang/Object

.field public static a I
.field public static b I
.field public static c F
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic test_global3/a I
	ldc 0
	putstatic test_global3/b I
	ldc 0.0
	putstatic test_global3/c F
	ldc 3
	putstatic test_global3/a I
	ldc 4
	putstatic test_global3/b I
	invokestatic test_global3/tt()I
	invokestatic io/writelnI(I)V
	return
.end method

.method public static tt()I
	.limit locals 20
	.limit stack 100
	ldc 2
	multianewarray [I 1
	astore 0
	ldc 2
	multianewarray [I 1
	astore 1
	ldc 10
	aload 0
	swap
	ldc 1
	ldc 1
	isub
	swap
	iastore
	aload 0
	ldc 1
	ldc 1
	isub
	iaload
	ldc 11
	iadd
	aload 1
	swap
	ldc 1
	ldc 1
	isub
	swap
	iastore
	aload 1
	ldc 1
	ldc 1
	isub
	iaload
	istore 19
	iload 19
	ireturn
.end method

