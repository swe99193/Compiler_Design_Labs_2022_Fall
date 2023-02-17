.class public test_array_slice
.super java/lang/Object

.field public static a [[I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 2
	ldc 3
	multianewarray [[I 2
	putstatic test_array_slice/a [[I
	ldc 1
	getstatic test_array_slice/a [[I
	ldc 2
	ldc 1
	isub
	aaload
	swap
	ldc 3
	ldc 3
	isub
	swap
	iastore
	ldc 2
	getstatic test_array_slice/a [[I
	ldc 2
	ldc 1
	isub
	aaload
	swap
	ldc 4
	ldc 3
	isub
	swap
	iastore
	ldc 3
	getstatic test_array_slice/a [[I
	ldc 2
	ldc 1
	isub
	aaload
	swap
	ldc 5
	ldc 3
	isub
	swap
	iastore
	getstatic test_array_slice/a [[I
	ldc 2
	ldc 1
	isub
	aaload
	invokestatic test_array_slice/slice([I)I
	invokestatic io/writelnI(I)V
	return
.end method

.method public static slice([I)I
	.limit locals 20
	.limit stack 100
	aload 0
	ldc 3
	ldc 3
	isub
	iaload
	aload 0
	ldc 4
	ldc 3
	isub
	iaload
	iadd
	aload 0
	ldc 5
	ldc 3
	isub
	iaload
	iadd
	istore 19
	iload 19
	ireturn
.end method

