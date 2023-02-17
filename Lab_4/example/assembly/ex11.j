.class public ex11
.super java/lang/Object

.field public static a I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic ex11/a I
	goto COND_0
WHILE_0:
	getstatic ex11/a I
	invokestatic io/writelnI(I)V
	getstatic ex11/a I
	ldc 1
	iadd
	putstatic ex11/a I
COND_0:
	getstatic ex11/a I
	ldc 5
	if_icmpne TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
ifne WHILE_0
	return
.end method
