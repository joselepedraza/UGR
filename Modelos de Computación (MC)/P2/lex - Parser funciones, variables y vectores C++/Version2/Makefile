
all: lex compilar exec

lex :
	lex parsercppVVF.l

compilar :
	g++ lex.yy.c -o parser -ll

exec : 
	./parser progcpp.cpp