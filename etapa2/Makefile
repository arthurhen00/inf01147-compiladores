# Etapa 2
# Arthur Hendges da Silva - 00332968
# 2024/01

CC = gcc
CFLAGS = -Wall

etapa2: hash_table.o y.tab.o lex.yy.o main.o
	$(CC) -o etapa2 main.o hash_table.o y.tab.o lex.yy.o
	rm lex.yy.c y.tab.c y.tab.h *.o

main.o: main.c
	$(CC) -c main.c

y.tab.o: y.tab.c
	$(CC) -c y.tab.c

y.tab.c: parser.y
	yacc parser.y -d

lex.yy.o: lex.yy.c
	$(CC) -c lex.yy.c

lex.yy.c: scanner.l
	lex scanner.l

hash_table.o: hash_table.c
	$(CC) -c hash_table.c

clean:
	rm etapa2 lex.yy.c y.tab.c y.tab.h *.o

tgz:
	tar cvzf etapa2.tgz .