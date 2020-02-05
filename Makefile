# ---------------------------------------------------------------------
# 1 Semestre 2019/2020 -AED 
# Autores: Pedro Ventura, 93155 & Rita Palma, 93172 
#
# Para compilar o programa:
#    make
#----------------------------------------------------------------------


CC = gcc
CFLAGS  = -Wall -std=c99 -O3


default: campista

campista:  jogo.o pilha.o admissibilidade.o files.o 
	$(CC) $(CFLAGS) -o campista jogo.o pilha.o admissibilidade.o files.o

jogo.o:  jogo.c jogo.h
	$(CC) $(CFLAGS) -c jogo.c

pilha.o:  pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

admissibilidade.o:  admissibilidade.c admissibilidade.h
	$(CC) $(CFLAGS) -c admissibilidade.c

files.o:  files.c files.h
	$(CC) $(CFLAGS) -c files.c

clean:
	$(RM) count *.o *~
