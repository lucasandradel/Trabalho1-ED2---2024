all: arvore_rbn.o busca.o geracao.o main.o
	gcc geracao.o arvore_rbn.o busca.o main.o -o prog
	./prog

arvore_rbn.o: arvore_rbn.c
	gcc -c arvore_rbn.c

busca.o: busca.c
	gcc -c busca.c

geracao.o: Geracao.c
	gcc -c Geracao.c

main.o: main.c
	gcc -c main.c
	
run: prog
	./prog

clean:
	rm *.o prog