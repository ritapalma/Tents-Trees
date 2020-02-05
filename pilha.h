/******************************************************************************
* 1 Semestre 2019/2020 -AED 
* Autores: Pedro Ventura, 93155 & Rita Palma, 93172 
* 
* NOME
*   pilha.h
*
* DESCRICAO
*   Fun��es para aceder � pilha 
*  
******************************************************************************/

#ifndef _pilha_
#define _pilha_


/*****************************************************************************
 *  Data Type: pilha
 *
 *  Descricao: Estrutura com:
 *      1) coordenadas da posi��o alterada no mapa;
 *      2) ultima posi��o colocada no mapa em rela��o � arvore (E,C,B,D,V);
 *     
 **************************************************************************/
typedef struct pilha {
    int x,y; 
    char position; 
    struct pilha *next;
} Pilha;

/***************************************************************************
 *  Data Type: enum
 *
 *  Descricao: Enum com:
 *      1) TRUE OU FALSE
 *     
 **************************************************************************/
typedef enum {
    FALSE,TRUE
} BOOL;

/**************************************************************************
 *  Funcao:
 *    Init 
 *
 *  Descricao:
 *    Inicializa a pilha;
 * 
 *  Argumentos:
 *    Nenhuns ;
 *
 *  Return:
 *    Nenhum
 *************************************************************************/
void Init();


/**************************************************************************
 *  Funcao:
 *    Push 
 *
 *  Descricao:
 *    Coloca os valores dos argumentos na estrutura da pilha e, 
 *    mete o pointer a apontar para o topo da pilha;
 * 
 *  Argumentos:
 *    posicao i, j
 *    char position ;
 *
 *  Return:
 *    Nenhum
 *************************************************************************/
void Push(int,int,char);

/**************************************************************************
 *  Funcao:
 *    valores_pilha 
 *
 *  Descricao:
 *    Coloca os valores dos argumentos no pointer.

 *  Argumentos:
 *    posicao i, j
 *    char position ;
 *
 *  Return:
 *    Retorna o char da posi��o da estrutura da pilha
 *************************************************************************/
char valores_pilha(char,int *i,int *j);

/**************************************************************************
 *  Funcao:
 *    Pop 
 *
 *  Descricao:
 *    Retira a �ltima estrutura inserida na pilha (LIFO)
 * 
 *  Argumentos:
 *    Nenhuns;
 *
 *  Return:
 *    Nenhum
 *************************************************************************/
void Pop();


/**************************************************************************
 *  Funcao:
 *    Is_Empty 
 *
 *  Descricao:
 *    Verifica se a pilha est� vazia,
 * 
 *  Argumentos:
 *    Nenhuns;
 *
 *  Return:
 *    Retorna TRUE se sim, FALSE caso contrario
 *************************************************************************/
BOOL Is_Empty();

#endif /* _pilha_ */