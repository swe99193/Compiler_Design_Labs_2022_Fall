.class public ex03
.super java/lang/Object

.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 1
	ldc 2
	iadd
	invokestatic io/writelnI(I)V
	ldc 1
	ldc 2
	isub
	invokestatic io/writelnI(I)V
	ldc 1
	ldc 2
	imul
	invokestatic io/writelnI(I)V
	ldc 1
	ldc 2
	idiv
	invokestatic io/writelnI(I)V
	ldc 1.000000
	ldc 2.000000
	fadd
	invokestatic io/writelnR(F)V
	ldc 1.000000
	ldc 2.000000
	fsub
	invokestatic io/writelnR(F)V
	ldc 1.000000
	ldc 2.000000
	fmul
	invokestatic io/writelnR(F)V
	ldc 1.000000
	ldc 2.000000
	fdiv
	invokestatic io/writelnR(F)V
	ldc 1
	ldc 2
	if_icmpgt TRUE_0
	ldc 0
	goto END_relop_0
TRUE_0:
	ldc 1
END_relop_0:
	invokestatic io/writelnI(I)V
	ldc 1
	ldc 2
	if_icmplt TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
	invokestatic io/writelnI(I)V
	ldc 1
	ldc 2
	if_icmpeq TRUE_2
	ldc 0
	goto END_relop_2
TRUE_2:
	ldc 1
END_relop_2:
	invokestatic io/writelnI(I)V
	ldc 1
	ldc 2
	if_icmple TRUE_3
	ldc 0
	goto END_relop_3
TRUE_3:
	ldc 1
END_relop_3:
	invokestatic io/writelnI(I)V
	ldc 1
	ldc 2
	if_icmpge TRUE_4
	ldc 0
	goto END_relop_4
TRUE_4:
	ldc 1
END_relop_4:
	invokestatic io/writelnI(I)V
	ldc 1
	ldc 2
	if_icmpne TRUE_5
	ldc 0
	goto END_relop_5
TRUE_5:
	ldc 1
END_relop_5:
	invokestatic io/writelnI(I)V
	ldc 1.000000
	ldc 2.000000
	fcmpg
	ldc 1
	if_icmpeq TRUE_6
	ldc 0
	goto END_relop_6
TRUE_6:
	ldc 1
END_relop_6:
	invokestatic io/writelnI(I)V
	ldc 1.000000
	ldc 2.000000
	fcmpg
	ldc -1
	if_icmpeq TRUE_7
	ldc 0
	goto END_relop_7
TRUE_7:
	ldc 1
END_relop_7:
	invokestatic io/writelnI(I)V
	ldc 1.000000
	ldc 2.000000
	fcmpg
	ldc 0
	if_icmpeq TRUE_8
	ldc 0
	goto END_relop_8
TRUE_8:
	ldc 1
END_relop_8:
	invokestatic io/writelnI(I)V
	ldc 1.000000
	ldc 2.000000
	fcmpg
	ldc 1
	if_icmplt TRUE_9
	ldc 0
	goto END_relop_9
TRUE_9:
	ldc 1
END_relop_9:
	invokestatic io/writelnI(I)V
	ldc 1.000000
	ldc 2.000000
	fcmpg
	ldc -1
	if_icmpgt TRUE_10
	ldc 0
	goto END_relop_10
TRUE_10:
	ldc 1
END_relop_10:
	invokestatic io/writelnI(I)V
	ldc 1.000000
	ldc 2.000000
	fcmpg
	ldc 0
	if_icmpne TRUE_11
	ldc 0
	goto END_relop_11
TRUE_11:
	ldc 1
END_relop_11:
	invokestatic io/writelnI(I)V
	new java/lang/StringBuffer
	dup
	invokespecial java/lang/StringBuffer/<init>()V
	ldc "1"
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	ldc "2"
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	invokevirtual java/lang/StringBuffer/toString()Ljava/lang/String;
	invokestatic io/writelnS(Ljava/lang/String;)V
	return
.end method
