/******************************************************************************
* 1 Semestre 2019/2020 -AED 
* Autores: Pedro Ventura, 93155 & Rita Palma, 93172 
*
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <strings.h>

#include "pilha.h"  

static Pilha *pointer;

void Init(unsigned pNumb)
{
    pointer = NULL;
}

void Push(int x, int y, char position) 
{
    Pilha *Top = (Pilha *)malloc(sizeof(Pilha));

    Top->x = x; 
    Top->y = y; 
    Top->position=position;
    Top->next = pointer;
    pointer = Top;
}

char valores_pilha(char position,int *i,int *j)
{
    *i=pointer->x;
    *j=pointer->y;
    position=pointer->position;

    return position;
}

void Pop() 
{
    Pilha *aux = NULL;

    aux=pointer->next;
    free(pointer); 
    pointer=aux;
}

BOOL Is_Empty()
{
    return pointer==NULL? TRUE : FALSE;
}
