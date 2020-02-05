/******************************************************************************
* 1 Semestre 2019/2020 -AED 
* Autores: Pedro Ventura, 93155 & Rita Palma, 93172 
*
* NOME
*   admissibilidade.h
*
* DESCRICAO
*   Funções para verificar a admissibilidade dos argumentos na linha de comando;
*   Funções para verificar a admissbilidade do mapa;
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
 *      Verifica se o número de argumentos é o correto, 
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
 *    Verifica se o número de espaços livres no mapa é menor 
 *    que os do vetor do cabeçalho, para cada linha/coluna;
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
 *    Verifica se a soma do vetor de tendas por coluna é igual a soma do 
 *    vetor de tendas por linha,
 *    se o número de tendas para cada linha/coluna é positivo e,
 *    se o número de tendas por linha/coluna é menor ou igual que 
 *    o número maximo possivel para essa linha/coluna.
 *
 *  Argumentos:
 *    Struct leitura;
 *    Total de tendas;
 *
 *  Return:
 *    Se não cumprir alguma das condicoes anteriores, retorna -1, 
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
 *     Verifica se a epoca do mapa é válida, executa a parte logica,
 *     e chama a função admissibilidade_possibilidades
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