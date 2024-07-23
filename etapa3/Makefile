# Compiladores - Etapa 3 - Marcelo Johann - 2024/01
# Arthur Hendges da Silva - 00332968
# 

CC = gcc
CFLAGS = -Wall

etapa3: hash_table.o ast.o y.tab.o lex.yy.o main.o
	$(CC) -o etapa3 hash_table.o ast.o y.tab.o lex.yy.o main.o
	rm lex.yy.c y.tab.c y.tab.h *.o

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

y.tab.o: y.tab.c
	$(CC) -c y.tab.c

y.tab.c: parser.y
	yacc parser.y -d

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

lex.yy.c: scanner.l
	lex scanner.l

hash_table.o: hash_table.c
	$(CC) -c hash_table.c $(CFLAGS)

ast.o: ast.c
	$(CC) -c ast.c $(CFLAGS)

clean:
	rm etapa3 lex.yy.c y.tab.c y.tab.h *.o

tgz:
	tar cvzf etapa3.tgz .