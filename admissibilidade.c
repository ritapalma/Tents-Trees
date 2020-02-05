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

#include "jogo.h"
#include "admissibilidade.h"

void verifica_argumentos(int argc, char *argv[])
{
    char *pointer = NULL;
  
    if (argc == 2) {
        if (strcmp (argv[0],"./campista") != 0) /* Apenas se encontrar este argumento abre o ficheiro indicado no argumento seguinte */
            exit(EXIT_FAILURE);

        pointer = strrchr(argv[1],'.'); /* Obter a string a seguir ao ultimo ponto */
        if (strcmp(pointer,".camp") != 0)
            exit(EXIT_FAILURE);
    }
    else
        exit(EXIT_FAILURE);

}

int admissibilidade_possibilidades(leitura *jogo)
{
    int i=0;

    for (i=0; i < jogo->n_linhas; i++){
        if (jogo->spaces_l[i] < jogo->linhas[i])   
            return -1; 
    }

    for (i=0; i < jogo->n_colunas; i++){
        if (jogo->spaces_c[i] < jogo->colunas[i])   
            return -1; 
    }
    return 1;
}


int admissibilidade_antes(leitura*jogo,int *aux)
{
    int i=0, valor_colunas=0, valor_linhas=0, n_tendas_l=0, n_tendas_c=0;
    
    /* Obter o valor maximo por linha/coluna de tendas, pois as tendas nao se podem tocar */
    valor_linhas = jogo->n_colunas/2 + jogo->n_colunas%2; 
    valor_colunas = jogo->n_linhas/2 + jogo->n_linhas%2;

    for (i=0; i < jogo->n_colunas; i++){
        n_tendas_c+=jogo->colunas[i];
        if (jogo->colunas[i] > valor_colunas || jogo->colunas[i] < 0)
            return -1;
    }
    for (i=0; i < jogo->n_linhas; i++){
        n_tendas_l+=jogo->linhas[i];
        if (jogo->linhas[i] > valor_linhas || jogo->linhas[i] < 0)
            return -1;
    }

    if(n_tendas_c != n_tendas_l) /* modo_A projeto intermedio */
        return -1;

    *aux = n_tendas_c;
     
    return 1;
}

int admissibilidade_depois(leitura* jogo, int total_tendas)
{
    int res=0;

    if (jogo->n_arvores < total_tendas)
        return -1;
    else if (jogo->n_arvores == total_tendas )
        jogo->epoca = 'A';
    else
        jogo->epoca = 'B';

    main_jogo(jogo);
    res=admissibilidade_possibilidades(jogo);
    return res;
}