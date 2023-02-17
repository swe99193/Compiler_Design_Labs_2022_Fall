.class public ex10
.super java/lang/Object

.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 1
	ldc 1
	if_icmpeq TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
ifne IF_0
	ldc 2
	invokestatic io/writelnI(I)V
	goto ENDIF_0
IF_0:
	ldc 1
	invokestatic io/writelnI(I)V
ENDIF_0:
	return
.end method
