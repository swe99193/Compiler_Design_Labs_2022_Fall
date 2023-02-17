.class public test_nestedStmt
.super java/lang/Object

.field public static a I
.field public static b I
.field public static d I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic test_nestedStmt/a I
	ldc 0
	putstatic test_nestedStmt/b I
	ldc 0
	putstatic test_nestedStmt/d I
	ldc 1
	putstatic test_nestedStmt/a I
	ldc 7
	putstatic test_nestedStmt/b I
	ldc 9
	putstatic test_nestedStmt/d I
	getstatic test_nestedStmt/a I
	getstatic test_nestedStmt/b I
	ldc 3
	iadd
	if_icmplt TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
ifne IF_0
	getstatic test_nestedStmt/d I
	ldc 1000
	iadd
	putstatic test_nestedStmt/d I
	goto ENDIF_0
IF_0:
	getstatic test_nestedStmt/a I
	ldc 5
	iadd
	getstatic test_nestedStmt/b I
	ldc 2
	isub
	if_icmpgt TRUE_3
	ldc 0
	goto END_relop_3
TRUE_3:
	ldc 1
END_relop_3:
ifne IF_2
	getstatic test_nestedStmt/d I
	ldc 100
	iadd
	putstatic test_nestedStmt/d I
	goto ENDIF_2
IF_2:
	goto COND_4
WHILE_4:
	goto COND_5
WHILE_5:
	getstatic test_nestedStmt/b I
	ldc 2
	iadd
	putstatic test_nestedStmt/b I
COND_5:
	getstatic test_nestedStmt/b I
	ldc 11
	if_icmplt TRUE_6
	ldc 0
	goto END_relop_6
TRUE_6:
	ldc 1
END_relop_6:
ifne WHILE_5
	getstatic test_nestedStmt/a I
	ldc 10
	iadd
	putstatic test_nestedStmt/a I
COND_4:
	getstatic test_nestedStmt/a I
	getstatic test_nestedStmt/b I
	if_icmplt TRUE_7
	ldc 0
	goto END_relop_7
TRUE_7:
	ldc 1
END_relop_7:
ifne WHILE_4
ENDIF_2:
ENDIF_0:
	getstatic test_nestedStmt/a I
	invokestatic io/writelnI(I)V
	getstatic test_nestedStmt/b I
	invokestatic io/writelnI(I)V
	getstatic test_nestedStmt/d I
	invokestatic io/writelnI(I)V
	return
.end method
