parametrosCompilacao=-Wall #-Wshadow
nomePrograma=trab2grrTal

all: $(nomePrograma)

$(nomePrograma): main.o ordenacao.o pilha.o
	gcc -o $(nomePrograma) main.o ordenacao.o pilha.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

ordenacao.o: ordenacao.h ordenacao.c
	gcc -c ordenacao.c $(parametrosCompilacao)

pilha.o: pilha.h pilha.c
	gcc -c pilha.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)
