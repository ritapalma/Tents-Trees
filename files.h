/******************************************************************************
* 1 Semestre 2019/2020 -AED 
* Autores: Pedro Ventura, 93155 & Rita Palma, 93172 
*
* NOME
*   files.h
*
* DESCRICAO
*   Funções para aceder ao ficheiro de entrada e saída  
*
******************************************************************************/

#include <stdio.h> 
#include "jogo.h"

#ifndef _files_
#define _files_

/**************************************************************************
 *  Funcao:
 *    abre_ficheiro 
 *
 *  Descricao:
 *    Abre o ficheiro consoante o modo;
 * 
 *  Argumentos:
 *    Nome do ficheiro para abrir
 *    Modo para abrir o ficheiro ;
 *
 *  Return:
 *    Retorna o ponteiro para o ficheiro aberto;
 *************************************************************************/
FILE *abre_ficheiro (char *, char *);

/**************************************************************************
 *  Funcao:
 *    nome_saida 
 *
 *  Descricao:
 *    Cria o nome do ficheiro de saída até ao .camp do ficheiro de entrada, 
 *    com a extensao .tents;
 * 
 *  Argumentos:
 *    Nome do ficheiro de entrada
 *
 *  Return:
 *    Retorna o nome do ficheiro de saida;
 *************************************************************************/
char *nome_saida (char *);


/**************************************************************************
 *  Funcao:
 *    le_ficheiro 
 *
 *  Descricao:
 *    Le o ficheiro de teste;
 * 
 *  Argumentos:
 *    Apontador do ficheiro de entrada;
 *    Struct leitura;
 *    Nome do ficheiro de entrada;
 *
 *  Return:
 *    Nenhum;
 *************************************************************************/
void le_ficheiro(FILE *, leitura* , char *);

/**************************************************************************
 *  Funcao:
 *    escreve_ficheiro 
 *
 *  Descricao:
 *    Escreve no ficheiro de sai­da, o cabecalho, o resultado e a matriz, 
 *    só quando o mapa é valido;
 * 
 *  Argumentos:
 *    Nome do ficheiro de entrada;
 *    Struct leitura;
 *    Validade do cabecalho/mapa;
 *
 *  Return:
 *    Nenhum;
 *************************************************************************/
void escreve_ficheiro ( char *, leitura* ,int );

#endif /* _files_*/