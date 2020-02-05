/******************************************************************************
* 1 Semestre 2019/2020 -AED 
* Autores: Pedro Ventura, 93155 & Rita Palma, 93172 
*
* NOME
*   admissibilidade.h
*
* DESCRICAO
*   Fun��es para verificar a admissibilidade dos argumentos na linha de comando;
*   Fun��es para verificar a admissbilidade do mapa;
*  
******************************************************************************/

#include "jogo.h"

#ifndef _admissibilidade_
#define _admissibilidade_

/**************************************************************************
 *  Funcao:
 *      verifica_argumentos 
 *
 *  Descricao:
 *      Verifica se o n�mero de argumentos � o correto, 
 *      se o executavel se chama campista e,
 *      se o ficheiro de entrada termina em .camp;
 * 
 *  Argumentos:
 *      Argumentos da linha de comando ;
 *
 *  Return:
 *      Nenhum
 *************************************************************************/
void verifica_argumentos(int argc, char *argv[]);


/**************************************************************************
 *  Funcao:
 *    admissibilidade_possibilidades 
 *
 *  Descricao:
 *    Verifica se o n�mero de espa�os livres no mapa � menor 
 *    que os do vetor do cabe�alho, para cada linha/coluna;
 * 
 *  Argumentos:
 *    Struct leitura;
 *
 *  Return:
 *    Retorna -1 se isso acontecer (mapa invalido), ou 1 caso contrario
 *************************************************************************/
int admissibilidade_possibilidades(leitura *);


/**************************************************************************
 *  Funcao:
 *    admissibildade_antes 
 *
 *  Descricao:
 *    Verifica se a soma do vetor de tendas por coluna � igual a soma do 
 *    vetor de tendas por linha,
 *    se o n�mero de tendas para cada linha/coluna � positivo e,
 *    se o n�mero de tendas por linha/coluna � menor ou igual que 
 *    o n�mero maximo possivel para essa linha/coluna.
 *
 *  Argumentos:
 *    Struct leitura;
 *    Total de tendas;
 *
 *  Return:
 *    Se n�o cumprir alguma das condicoes anteriores, retorna -1, 
 *    se cumprir todas retorna 1. 
 *    Envia por referencia o numero de tendas totais,
 *    se o cabecalho for valido.
 *************************************************************************/
int admissibilidade_antes(leitura*,int *);


/**************************************************************************
 *  Funcao:
 *    admissibilidade_depois 
 *
 *  Descricao:
 *     Verifica se a epoca do mapa � v�lida, executa a parte logica,
 *     e chama a fun��o admissibilidade_possibilidades
 * 
 *  Argumentos:
 *    Struct leitura;
 *    Total de tendas no mapa;     
 *
 *  Return:
 *    Retorna -1 se nao for uma epoca valida, 
 *    ou se a admissibilidade_possibilidades o retornar;
 *    Retorna 1, caso a epoca seja valida e o mapa seja valido.
 *************************************************************************/
int admissibilidade_depois(leitura* , int );

#endif /* _admissibilidade_ */