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

#include "files.h"
#include "pilha.h"
#include "jogo.h"
#include "admissibilidade.h"


FILE *abre_ficheiro (char *nome, char *mode)
{
    FILE *fp;
    fp = fopen ( nome, mode );
    if ( fp == NULL ) {
        fprintf ( stderr, "ERROR: cannot open file '%s'\n", nome);
        exit (0); 
    }
    return (fp);
}

char *nome_saida (char *ficheiro)
{
    char *nome;

    nome =  (char *)calloc((strlen(ficheiro) - strlen(".camp") + strlen(".tents") + 1 ),sizeof(char)); /* + 1 do \0 */
    if ( nome == NULL ){
        fprintf ( stderr, "ERROR: not enough memory available!\n" );
        exit (1);
    }

    strncpy ( nome, ficheiro, strlen(ficheiro)-5); /* -5 do strlen(".camp") */
    strcat ( nome, ".tents" );

    return nome;
}

void escreve_ficheiro ( char *ficheiro, leitura* jogo,int res)
{
    FILE *f;
    char *nome;
    int i=0,j=0;

    nome =  nome_saida (ficheiro);
    f = abre_ficheiro ( nome, "a+");

    fprintf(f, "%d %d ",jogo->n_linhas,jogo->n_colunas);

    if (res == -1)
        fprintf(f,"-1\n"); /* Jogo invalido */

    else{
        if(caminhos(jogo) == 1){
            fprintf(f,"1\n"); /* Jogo valido */
            for(i=0; i < jogo->n_linhas; i++){
                for(j=0; j < jogo->n_colunas; j++){
                    if(jogo->matriz_jogo[i][j] == 'B')
                        fprintf(f,"A");
                    else if(jogo->matriz_jogo[i][j] == 'R')
                        fprintf(f,".");    
                    else
                        fprintf(f,"%c",jogo->matriz_jogo[i][j]);
                }
                fprintf(f,"\n");
            }
        }
        else
            fprintf(f,"-1\n"); /* Jogo invalido */
    }
    fprintf(f,"\n");
    fclose(f);
    free(nome);
}

void le_ficheiro(FILE *fp, leitura* jogo, char *ficheiro)
{
    int i=0,j=0,find,x=0,res=0,aux=0;
    char lixo;

    Init();
    jogo->n_arvores=0;

    if(fscanf(fp,"%d %d",&jogo->n_linhas,&jogo->n_colunas) == 2)
        i=0;
    
    jogo->linhas=(int *)malloc((jogo->n_linhas)*sizeof(int));
    jogo->colunas=(int *)malloc((jogo->n_colunas)*sizeof(int));

    for (i=0; i < (jogo->n_linhas); i++){
        if(fscanf(fp,"%d",&jogo->linhas[i]) == 1)
            continue;
    }
    for (i=0;i<jogo->n_colunas;i++){
        if(fscanf(fp,"%d",&jogo->colunas[i]) == 1)
            continue;
    }

    res=admissibilidade_antes(jogo,&aux);
    if(res!=-1){ /* So aloca memoria se o cabecalho for valido */
        jogo->matriz_jogo=(char**)malloc((jogo->n_linhas)*sizeof(char*));
        jogo->spaces_l=(int *)malloc((jogo->n_linhas)*sizeof(int));
        jogo->spaces_c=(int *)malloc((jogo->n_colunas)*sizeof(int));

        for (i=0; i < (jogo->n_linhas); i++){
            jogo->matriz_jogo[i]=(char*)malloc((jogo->n_colunas)*sizeof(char));
            jogo->spaces_l[i]=0;
        }
        for(i=0; i < jogo->n_colunas; i++)
            jogo->spaces_c[i]=0;
    }
    
    for(i=0; i < jogo->n_linhas; i++){
        for (j=0;j<jogo->n_colunas;j++){
            lixo=fgetc(fp); /* Permite-nos avancar o ponteiro, sem alocar obrigatoriamente memoria para a matriz */
            if (lixo == ' ' || lixo == '\n' || lixo == '\t') /* Com estes caracteres, o j decrementa para ler a quantidade de elementos exatos da matriz */
                j--;
            else if(res != -1){ 
                jogo->matriz_jogo[i][j]=lixo;
                if (lixo == 'A')
                    jogo->n_arvores++;
                else{
                    jogo->spaces_l[i]++;
                    jogo->spaces_c[j]++;
                }
            }
        }
    }

    if (res != -1)
        res=admissibilidade_depois(jogo,aux);
    
    escreve_ficheiro (ficheiro,jogo,res);
    if (fscanf(fp,"%d",&find) == 1){ /* Caso encontre um inteiro apos a leitura da matriz, entao ha um novo jogo para resolver */
        x= conta_digitos(find); /* Para nos permitir andar para tras o numero de digitos lidos anteriormente */
        fseek(fp,-x,SEEK_CUR); /* De forma a garantir que comecamos a ler o proximo cabecalho na posicao certa */
        if (res != -1)
            libertar_struct(jogo); /* So libertamos a estrutura se tivermos alocado memoria para tal */
        else{
            free(jogo->colunas);
            free(jogo->linhas);
        }
        while (Is_Empty() != TRUE) /* Para limpar a pilha a cada jogo */
            Pop();

        le_ficheiro(fp,jogo,ficheiro);
    }
    else{ /* Ja nao ha mais nada para ler, entao limpa-se toda a memoria alocada */
        if (res != -1)
            libertar_struct(jogo);
        else{
            free(jogo->colunas);
            free(jogo->linhas);
        }
        while (Is_Empty() != TRUE)
            Pop();
    }
}


