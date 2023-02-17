.class public qsort
.super java/lang/Object

.field public static i I
.field public static j I
.field public static tmp I
.field public static size I
.field public static arr [I
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc 0
	putstatic qsort/i I
	ldc 0
	putstatic qsort/j I
	ldc 0
	putstatic qsort/tmp I
	ldc 0
	putstatic qsort/size I
	ldc 50
	multianewarray [I 1
	putstatic qsort/arr [I
	getstatic qsort/arr [I
	invokestatic qsort/readArr([I)V
	getstatic qsort/arr [I
	invokestatic qsort/quicksort([I)V
	ldc 1
	putstatic qsort/i I
	goto COND_0
WHILE_0:
	getstatic qsort/arr [I
	getstatic qsort/i I
	ldc 1
	isub
	iaload
	invokestatic io/writelnI(I)V
	getstatic qsort/i I
	ldc 1
	iadd
	putstatic qsort/i I
COND_0:
	getstatic qsort/i I
	getstatic qsort/size I
	if_icmple TRUE_1
	ldc 0
	goto END_relop_1
TRUE_1:
	ldc 1
END_relop_1:
ifne WHILE_0
	return
.end method

.method public static readArr([I)V
	.limit locals 20
	.limit stack 100
	ldc 0
	istore 1
	ldc 0
	putstatic qsort/size I
	invokestatic io/readlnI()I
	istore 1
	goto COND_2
WHILE_2:
	getstatic qsort/size I
	ldc 1
	iadd
	putstatic qsort/size I
	iload 1
	getstatic qsort/arr [I
	swap
	getstatic qsort/size I
	ldc 1
	isub
	swap
	iastore
	invokestatic io/readlnI()I
	istore 1
COND_2:
	iload 1
	ldc 0
	if_icmpne TRUE_3
	ldc 0
	goto END_relop_3
TRUE_3:
	ldc 1
END_relop_3:
ifne WHILE_2
	return
.end method


.method public static split(II)I
	.limit locals 20
	.limit stack 100
	ldc 0
	istore 2
	ldc 0
	istore 3
	ldc 0
	istore 4
	ldc 0
	istore 5
	ldc 0
	istore 6
	getstatic qsort/arr [I
	iload 0
	ldc 1
	isub
	iaload
	istore 5
	iload 0
	ldc 1
	iadd
	istore 3
	iload 1
	istore 4
	goto COND_4
WHILE_4:
	ldc 1
	istore 2
	iload 3
	iload 1
	if_icmple TRUE_6
	ldc 0
	goto END_relop_6
TRUE_6:
	ldc 1
END_relop_6:
ifne IF_5
	ldc 0
	istore 2
	goto ENDIF_5
IF_5:
ENDIF_5:
	iload 2
	ldc 1
	if_icmpeq TRUE_8
	ldc 0
	goto END_relop_8
TRUE_8:
	ldc 1
END_relop_8:
ifne IF_7
	goto ENDIF_7
IF_7:
	getstatic qsort/arr [I
	iload 3
	ldc 1
	isub
	iaload
	iload 5
	if_icmplt TRUE_10
	ldc 0
	goto END_relop_10
TRUE_10:
	ldc 1
END_relop_10:
ifne IF_9
	ldc 0
	istore 2
	goto ENDIF_9
IF_9:
ENDIF_9:
ENDIF_7:
	goto COND_11
WHILE_11:
	iload 3
	ldc 1
	iadd
	istore 3
	ldc 1
	istore 2
	iload 3
	iload 1
	if_icmple TRUE_13
	ldc 0
	goto END_relop_13
TRUE_13:
	ldc 1
END_relop_13:
ifne IF_12
	ldc 0
	istore 2
	goto ENDIF_12
IF_12:
ENDIF_12:
	iload 2
	ldc 1
	if_icmpeq TRUE_15
	ldc 0
	goto END_relop_15
TRUE_15:
	ldc 1
END_relop_15:
ifne IF_14
	goto ENDIF_14
IF_14:
	getstatic qsort/arr [I
	iload 3
	ldc 1
	isub
	iaload
	iload 5
	if_icmplt TRUE_17
	ldc 0
	goto END_relop_17
TRUE_17:
	ldc 1
END_relop_17:
ifne IF_16
	ldc 0
	istore 2
	goto ENDIF_16
IF_16:
ENDIF_16:
ENDIF_14:
COND_11:
	iload 2
	ldc 1
	if_icmpeq TRUE_18
	ldc 0
	goto END_relop_18
TRUE_18:
	ldc 1
END_relop_18:
ifne WHILE_11
	ldc 1
	istore 2
	iload 4
	iload 0
	if_icmpgt TRUE_20
	ldc 0
	goto END_relop_20
TRUE_20:
	ldc 1
END_relop_20:
ifne IF_19
	ldc 0
	istore 2
	goto ENDIF_19
IF_19:
ENDIF_19:
	iload 2
	ldc 1
	if_icmpeq TRUE_22
	ldc 0
	goto END_relop_22
TRUE_22:
	ldc 1
END_relop_22:
ifne IF_21
	goto ENDIF_21
IF_21:
	getstatic qsort/arr [I
	iload 4
	ldc 1
	isub
	iaload
	iload 5
	if_icmpge TRUE_24
	ldc 0
	goto END_relop_24
TRUE_24:
	ldc 1
END_relop_24:
ifne IF_23
	ldc 0
	istore 2
	goto ENDIF_23
IF_23:
ENDIF_23:
ENDIF_21:
	goto COND_25
WHILE_25:
	iload 4
	ldc 1
	isub
	istore 4
	ldc 1
	istore 2
	iload 4
	iload 0
	if_icmpgt TRUE_27
	ldc 0
	goto END_relop_27
TRUE_27:
	ldc 1
END_relop_27:
ifne IF_26
	ldc 0
	istore 2
	goto ENDIF_26
IF_26:
ENDIF_26:
	iload 2
	ldc 1
	if_icmpeq TRUE_29
	ldc 0
	goto END_relop_29
TRUE_29:
	ldc 1
END_relop_29:
ifne IF_28
	goto ENDIF_28
IF_28:
	getstatic qsort/arr [I
	iload 4
	ldc 1
	isub
	iaload
	iload 5
	if_icmpge TRUE_31
	ldc 0
	goto END_relop_31
TRUE_31:
	ldc 1
END_relop_31:
ifne IF_30
	ldc 0
	istore 2
	goto ENDIF_30
IF_30:
ENDIF_30:
ENDIF_28:
COND_25:
	iload 2
	ldc 1
	if_icmpeq TRUE_32
	ldc 0
	goto END_relop_32
TRUE_32:
	ldc 1
END_relop_32:
ifne WHILE_25
	iload 3
	iload 4
	if_icmplt TRUE_34
	ldc 0
	goto END_relop_34
TRUE_34:
	ldc 1
END_relop_34:
ifne IF_33
	goto ENDIF_33
IF_33:
	getstatic qsort/arr [I
	iload 3
	ldc 1
	isub
	iaload
	istore 6
	getstatic qsort/arr [I
	iload 4
	ldc 1
	isub
	iaload
	getstatic qsort/arr [I
	swap
	iload 3
	ldc 1
	isub
	swap
	iastore
	iload 6
	getstatic qsort/arr [I
	swap
	iload 4
	ldc 1
	isub
	swap
	iastore
ENDIF_33:
COND_4:
	iload 3
	iload 4
	if_icmple TRUE_35
	ldc 0
	goto END_relop_35
TRUE_35:
	ldc 1
END_relop_35:
ifne WHILE_4
	getstatic qsort/arr [I
	iload 0
	ldc 1
	isub
	iaload
	istore 6
	getstatic qsort/arr [I
	iload 4
	ldc 1
	isub
	iaload
	getstatic qsort/arr [I
	swap
	iload 0
	ldc 1
	isub
	swap
	iastore
	iload 6
	getstatic qsort/arr [I
	swap
	iload 4
	ldc 1
	isub
	swap
	iastore
	iload 4
	istore 19
	iload 19
	ireturn
.end method


.method public static quicksortRecur(II)V
	.limit locals 20
	.limit stack 100
	ldc 0
	istore 2
	ldc 0
	istore 3
	iload 0
	iload 1
	if_icmplt TRUE_37
	ldc 0
	goto END_relop_37
TRUE_37:
	ldc 1
END_relop_37:
ifne IF_36
	goto ENDIF_36
IF_36:
	iload 0
	iload 1
	invokestatic qsort/split(II)I
	istore 3
	iload 0
	iload 3
	ldc 1
	isub
	invokestatic qsort/quicksortRecur(II)V
	iload 3
	ldc 1
	iadd
	iload 1
	invokestatic qsort/quicksortRecur(II)V
ENDIF_36:
	return
.end method


.method public static quicksort([I)V
	.limit locals 20
	.limit stack 100
	ldc 1
	getstatic qsort/size I
	invokestatic qsort/quicksortRecur(II)V
	return
.end method

