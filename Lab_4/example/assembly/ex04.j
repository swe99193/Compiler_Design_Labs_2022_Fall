.class public ex04
.super java/lang/Object

.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 1
	ifeq TRUE_0
	ldc 0
	goto END_bool_0
TRUE_0:
	ldc 1
END_bool_0:
	invokestatic io/writelnI(I)V
	ldc -1.000000
	invokestatic io/writelnR(F)V
	return
.end method
