.class public test_array
.super java/lang/Object

.field public static a [I
.field public static b I
.field public static c [[I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 2
	multianewarray [I 1
	putstatic test_array/a [I
	ldc 0
	putstatic test_array/b I
	ldc 2
	ldc 2
	multianewarray [[I 2
	putstatic test_array/c [[I
	ldc 1
	getstatic test_array/a [I
	swap
	ldc 1
	ldc 1
	isub
	swap
	iastore
	ldc 2
	getstatic test_array/a [I
	swap
	ldc 2
	ldc 1
	isub
	swap
	iastore
	getstatic test_array/a [I
	ldc 1
	ldc 1
	isub
	iaload
	getstatic test_array/c [[I
	ldc 1
	ldc 1
	isub
	aaload
	swap
	ldc 1
	ldc 1
	isub
	swap
	iastore
	getstatic test_array/a [I
	ldc 2
	ldc 1
	isub
	iaload
	getstatic test_array/c [[I
	ldc 1
	ldc 1
	isub
	aaload
	swap
	ldc 2
	ldc 1
	isub
	swap
	iastore
	getstatic test_array/a [I
	ldc 2
	ldc 1
	isub
	iaload
	getstatic test_array/a [I
	ldc 1
	ldc 1
	isub
	iaload
	iadd
	getstatic test_array/c [[I
	ldc 2
	ldc 1
	isub
	aaload
	swap
	ldc 1
	ldc 1
	isub
	swap
	iastore
	getstatic test_array/a [I
	ldc 2
	ldc 1
	isub
	iaload
	getstatic test_array/a [I
	ldc 2
	ldc 1
	isub
	iaload
	iadd
	getstatic test_array/c [[I
	ldc 2
	ldc 1
	isub
	aaload
	swap
	ldc 2
	ldc 1
	isub
	swap
	iastore
	getstatic test_array/c [[I
	ldc 1
	ldc 1
	isub
	aaload
	ldc 1
	ldc 1
	isub
	iaload
	getstatic test_array/c [[I
	ldc 1
	ldc 1
	isub
	aaload
	ldc 2
	ldc 1
	isub
	iaload
	iadd
	getstatic test_array/c [[I
	ldc 2
	ldc 1
	isub
	aaload
	ldc 1
	ldc 1
	isub
	iaload
	iadd
	getstatic test_array/c [[I
	ldc 2
	ldc 1
	isub
	aaload
	ldc 2
	ldc 1
	isub
	iaload
	iadd
	invokestatic io/writelnI(I)V
	return
.end method
