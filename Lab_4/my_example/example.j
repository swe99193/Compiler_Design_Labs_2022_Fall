.class public example
.super java/lang/Object

.field public static a Ljava/lang/String;
.field public static str Ljava/lang/String;
.method public static main([Ljava/lang/String;)V
	.limit locals 50
	.limit stack 50
	ldc ""
	putstatic example/a Ljava/lang/String;
	ldc ""
	putstatic example/str Ljava/lang/String;
	ldc "3"
	invokestatic io/writelnS(Ljava/lang/String;)V
	ldc "heyy yoo"
	invokestatic io/writelnS(Ljava/lang/String;)V
	getstatic example/str Ljava/lang/String;
	invokestatic io/writelnS(Ljava/lang/String;)V
	new java/lang/StringBuffer
	dup
	invokespecial java/lang/StringBuffer/<init>()V
	ldc "ab"
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	ldc " cde xyz"
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	invokevirtual java/lang/StringBuffer/toString()Ljava/lang/String;
	invokestatic io/writelnS(Ljava/lang/String;)V
	ldc "rabbit"
	putstatic example/str Ljava/lang/String;
	new java/lang/StringBuffer
	dup
	invokespecial java/lang/StringBuffer/<init>()V
	ldc "assigned str: "
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	getstatic example/str Ljava/lang/String;
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	invokevirtual java/lang/StringBuffer/toString()Ljava/lang/String;
	invokestatic io/writelnS(Ljava/lang/String;)V
	new java/lang/StringBuffer
	dup
	invokespecial java/lang/StringBuffer/<init>()V
	new java/lang/StringBuffer
	dup
	invokespecial java/lang/StringBuffer/<init>()V
	new java/lang/StringBuffer
	dup
	invokespecial java/lang/StringBuffer/<init>()V
	getstatic example/str Ljava/lang/String;
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	ldc " :mid: "
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	invokevirtual java/lang/StringBuffer/toString()Ljava/lang/String;
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	getstatic example/str Ljava/lang/String;
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	invokevirtual java/lang/StringBuffer/toString()Ljava/lang/String;
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	getstatic example/str Ljava/lang/String;
	invokevirtual java/lang/StringBuffer/append(Ljava/lang/String;)Ljava/lang/StringBuffer;
	invokevirtual java/lang/StringBuffer/toString()Ljava/lang/String;
	invokestatic io/writelnS(Ljava/lang/String;)V
	return
.end method
