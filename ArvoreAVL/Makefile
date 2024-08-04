all: ArvoreAVL.o Busca.o Geracao.o main.o
	gcc Geracao.o ArvoreAVL.o Busca.o main.o -o prog
	./prog

ArvoreAVL.o: ArvoreAVL.c
	gcc -c ArvoreAVL.c

Busca.o: Busca.c
	gcc -c Busca.c

Geracao.o: Geracao.c
	gcc -c Geracao.c

main.o: main.c
	gcc -c main.c
	
run: prog
	./prog

clean:
	rm *.o prog