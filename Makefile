all: mfvj11-aprendiz mfvj11-jogador clean

mfvj11-aprendiz: mfvj11-aprendiz.o biblioteca.o
	gcc mfvj11-aprendiz.o biblioteca.o -o mfvj11-aprendiz

mfvj11-aprendiz.o: mfvj11-aprendiz.c biblioteca.h
	gcc -c -g mfvj11-aprendiz.c -o mfvj11-aprendiz.o
mfvj11-jogador: mfvj11-jogador.o biblioteca.o
	gcc mfvj11-jogador.o biblioteca.o -o mfvj11-jogador

mfvj11-jogador.o: mfvj11-jogador.c biblioteca.h
	gcc -c -g mfvj11-jogador.c -o mfvj11-jogador.o

biblioteca.o: biblioteca.c biblioteca.h
	gcc -c -g biblioteca.c -o biblioteca.o
clean:
	rm -rf *.o 

