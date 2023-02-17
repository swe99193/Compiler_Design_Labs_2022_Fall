.class public example
.super java/lang/Object

.field public static a I
.field public static b [[I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic example/a I
	ldc 10
	ldc 2
	multianewarray [[I 2
	putstatic example/b [[I
	ldc 5
	putstatic example/a I
	ldc 2
	getstatic example/b [[I
	getstatic example/a I
	ldc 1
	isub
	aaload
	swap
	ldc 2
	ldc 1
	isub
	swap
	iastore
	getstatic example/a I
	invokestatic io/writelnI(I)V
	getstatic example/b [[I
	ldc 3
	ldc 1
	isub
	aaload
	ldc 2
	ldc 1
	isub
	iaload
	invokestatic io/writelnI(I)V
	getstatic example/b [[I
	ldc 5
	ldc 1
	isub
	aaload
	ldc 2
	ldc 1
	isub
	iaload
	invokestatic io/writelnI(I)V
	getstatic example/b [[I
	getstatic example/a I
	ldc 1
	isub
	aaload
	ldc 2
	ldc 1
	isub
	iaload
	invokestatic io/writelnI(I)V
	return
.end method
