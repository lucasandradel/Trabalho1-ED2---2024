all: Geracao.o main.o
	gcc Geracao.o main.o -o prog
	./prog 5000 out3-20000.txt
Geracao.o: Geracao.c
	gcc -c Geracao.c

main.o: main.c
	gcc -c main.c
	
run: prog
	./prog

clean:
	rm *.o prog