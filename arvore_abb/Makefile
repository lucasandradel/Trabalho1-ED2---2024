all: arvore_abb.o busca.o geracao.o main.o
	gcc geracao.o arvore_abb.o busca.o main.o -o prog
	./prog

arvore_abb.o: arvore_abb.c
	gcc -c arvore_abb.c

busca.o: busca.c
	gcc -c busca.c

geracao.o: geracao.c
	gcc -c geracao.c

main.o: main.c
	gcc -c main.c
	
run: prog
	./prog

clean:
	rm *.o prog