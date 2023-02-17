.class public test_global2
.super java/lang/Object

.field public static a I
.field public static b I
.field public static c F
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic test_global2/a I
	ldc 0
	putstatic test_global2/b I
	ldc 0.0
	putstatic test_global2/c F
	ldc 3
	putstatic test_global2/a I
	ldc 4
	putstatic test_global2/b I
	invokestatic test_global2/tt()I
	invokestatic io/writelnI(I)V
	return
.end method

.method public static tt()I
	.limit locals 20
	.limit stack 100
	ldc 0
	istore 0
	ldc 0
	istore 1
	ldc 3
	istore 0
	iload 0
	ldc 5
	iadd
	istore 1
	iload 1
	istore 19
	iload 19
	ireturn
.end method

