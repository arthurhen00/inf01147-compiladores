# Compiladores - Etapa 6 - Marcelo Johann - 2024/01
# Arthur Hendges da Silva - 00332968
# 

CC = clang
CFLAGS = -Wall

etapa6: hash_table.o ast.o semantic.o tac.o asm.o y.tab.o lex.yy.o main.o
	$(CC) -o etapa6 hash_table.o ast.o semantic.o tac.o asm.o y.tab.o lex.yy.o main.o
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

semantic.o: semantic.c
	$(CC) -c semantic.c $(CFLAGS)

tac.o: tac.c
	$(CC) -c tac.c $(CFLAGS)

asm.o: asm.c
	$(CC) -c asm.c $(CFLAGS)

clean:
	rm etapa6 lex.yy.c y.tab.c y.tab.h *.o *.s

tgz:
	tar cvzf etapa6.tgz .

test:
	gcc t.c -S
	gcc t.s -o t.exe
	./t.exe

t:
	make
	./etapa6 t.txt
	gcc out.s
	./a.out

