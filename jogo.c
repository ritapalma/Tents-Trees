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
#include "pilha.h" 
#include "files.h"
#include "admissibilidade.h"

int ve_ponto(leitura *jogo, int i, int j,int *x, int *y)
{
    if (jogo->matriz_jogo[i][j] == '.'){
        *x = i;
        *y = j;
        return 1;
    }
    else
        return -1;
}

char verifica_position(leitura *jogo, char position, int i, int j,int *x,int *y)
{
    int res=0;

    if (position == 'I'){ /* Esquerda */
        if (j != 0){
            res=ve_ponto(jogo,i,j-1,x,y);
            if (res == 1)
                return 'E';
        }
        position=verifica_position(jogo,'E',i,j,x,y);
        return position;
    }
    else if (position == 'E'){ /* Cima */ 
        if (i != 0){
            res=ve_ponto(jogo,i-1,j,x,y);
            if (res == 1)
                return 'C';
        }
        position=verifica_position(jogo,'C',i,j,x,y);
        return position;
    }
    else if (position =='C'){ /* Baixo */
        if (i != jogo->n_linhas-1){
            res=ve_ponto(jogo,i+1,j,x,y);
            if (res == 1)
                return 'B';
        }
        position=verifica_position(jogo,'B',i,j,x,y);
        return position;
    }
    else if (position == 'B'){ /* Direita */
        if (j != jogo->n_colunas-1){
            res=ve_ponto(jogo,i,j+1,x,y);
            if (res == 1)
                return 'D';
        }
        position=verifica_position(jogo,'D',i,j,x,y);
        return position;
    }
    else if (position == 'D'&& jogo->epoca == 'B'){ /* Nao tem tenda */
        return 'V';
    }
    return 'F';
}

int arvores_tendas_adjacentes(leitura* jogo,int *x,int *y,int i,int j,char modo)
{
  int contagem=0;
  if(i != 0){
   if(jogo->matriz_jogo[i-1][j] == modo){ /* Cima */
    contagem++;
    *x = i-1;
    *y = j;
   }
  }
  if(i != (jogo->n_linhas-1)){ 
    if(jogo->matriz_jogo[i+1][j] == modo){ /* Baixo */
      contagem++;
      *x = i+1;
      *y = j;
    }
  }
  if(j != 0){
    if(jogo->matriz_jogo[i][j-1] == modo){ /* Esquerda */
      contagem++;
      *x = i;
      *y = j-1;
    }
  }
  if(j != (jogo->n_colunas-1)){
    if(jogo->matriz_jogo[i][j+1] == modo){ /* Direita */
      contagem++;
      *x = i;
      *y = j+1;
    }
  }
  return contagem;
}

int tendas_diagonais(leitura* jogo,int i,int j)
{
  int position[4]={1,1,1,1}; /* {Esquerda,Direita,Cima,Baixo} */
  if (j == 0)
    position[0]=0;
  if(j == jogo->n_colunas-1)
    position[1]=0;
  if (i == 0)
    position[2]=0;
  if(i == jogo->n_linhas-1)
    position[3]=0;

  if(position[0] == 1){ /* Cantos Esquerdos */
    if((position[2] == 1 && jogo->matriz_jogo[i-1][j-1] == 'T')||(position[3] == 1 && jogo->matriz_jogo[i+1][j-1] == 'T'))
      return 1;
  }
  if(position[1] == 1){ /* Cantos Direitos */
    if((position[2] == 1 && jogo->matriz_jogo[i-1][j+1] == 'T')||(position[3] == 1 && jogo->matriz_jogo[i+1][j+1] == 'T'))
      return 1;
  }
  return 0; /* Nao ha tendas diagonais */
}

int modo_B(leitura* jogo,int i, int j) 
{
  int x,y;

  if(arvores_tendas_adjacentes(jogo,&x,&y,i,j,'A') != 0 && jogo->colunas[j] != 0 && jogo->linhas[i] != 0 
    && arvores_tendas_adjacentes(jogo,&x,&y,i,j,'T') == 0 && tendas_diagonais(jogo,i,j) == 0 && jogo->spaces_l[i] != 0
    && jogo->spaces_c[j] != 0 && jogo->matriz_jogo[i][j] == '.'){
    return 0;
  }
  return 1;
}

void colocar_tenda_relva(leitura *jogo,int x,int y,char modo)
{
    jogo->matriz_jogo[x][y] = modo;
}

void decrementar_vetores(leitura *jogo,int x,int y)
{
    jogo->linhas[x]--;
    jogo->colunas[y]--;
    jogo->spaces_l[x]--;
    jogo->spaces_c[y]--;
}

void tira_do_mapa(leitura *jogo,int i,int j,char position)
{
    if(position == 'E'){
        jogo->matriz_jogo[i][j-1]='.';
        jogo->linhas[i]++;
        jogo->colunas[j-1]++;
        jogo->spaces_l[i]++;
        jogo->spaces_c[j-1]++;
    }
    else if(position == 'D'){
        jogo->matriz_jogo[i][j+1]='.';
        jogo->linhas[i]++;
        jogo->colunas[j+1]++;
        jogo->spaces_l[i]++;
        jogo->spaces_c[j+1]++;
    }
    if(position == 'C'){
        jogo->matriz_jogo[i-1][j]='.';
        jogo->linhas[i-1]++;
        jogo->colunas[j]++;
        jogo->spaces_l[i-1]++;
        jogo->spaces_c[j]++;
    }
    if(position == 'B'){
        jogo->matriz_jogo[i+1][j]='.';
        jogo->linhas[i+1]++;
        jogo->colunas[j]++;
        jogo->spaces_l[i+1]++;
        jogo->spaces_c[j]++;
    }
}

char mega_position(leitura *jogo,int *i,int *j,char position,int *x,int *y)
{
    position=verifica_position(jogo,position,*i,*j,x,y);
    if(Is_Empty() == TRUE && position == 'F'){
        return 'H';
    }
    if(position == 'F'){ /* Tira o ultimo elemento da pilha e tira do mapa a tenda correspondente */
        position=valores_pilha(position,i,j);
        Pop();
        if(position != 'V')
            tira_do_mapa(jogo,*i,*j,position);

        position=mega_position(jogo,i,j,position,x,y);
    }
    else if(position != 'V'){ /* Verifica se e possivel colocar tenda, pelo modo_B, se nao for, procura uma nova posicao */
        if(modo_B(jogo,*x,*y) == 0) {
            return position;
        }
        else{
            position=mega_position(jogo,i,j,position,x,y);
        }
    }
    return position;
}

int verifica_linhas_colunas(leitura *jogo)
{
    int i=0;

    for(i=0; i < jogo->n_linhas; i++){
        if(jogo->linhas[i] != 0)
            return -1; /* Mapa invalido */ 
    }
    for(i=0; i < jogo->n_colunas; i++){
        if(jogo->colunas[i] != 0)
            return -1;
    }
    return 1; /*  Mapa valido */
}

char verifica_B_aux(leitura *jogo,int *i,int *j,int *x,int *y,char position,int *jj)
{
    position=valores_pilha(position,i,j);
    Pop();
    if(position != 'V')
        tira_do_mapa(jogo,*i,*j,position);

    position=mega_position(jogo,i,j,position,x,y);
    if(position == 'H')
        return 'H';
    if(position != 'V'){
        colocar_tenda_relva(jogo,*x,*y,'T');
        decrementar_vetores(jogo,*x,*y);
    }
    Push(*i,*j,position);
    *i=*i-1;
    *jj=*j+1;
    return position;
}


char verifica_B(leitura *jogo,int *i,int *j,int *x,int *y,char position,int *jj)
{
    if(jogo->epoca == 'B' && *i == jogo->n_linhas-1){
        if(jogo->linhas[*i] != 0 || jogo->linhas[*i-1] != 0) 
            position=verifica_B_aux(jogo,i,j,x,y,position,jj);
        else
            *jj=0; 
    }
    else if(jogo->epoca == 'B' && *i > 0){
        if(jogo->linhas[*i-1] != 0) 
            position=verifica_B_aux(jogo,i,j,x,y,position,jj);
        else
            *jj=0;
    }
    else
        *jj=0;
    
    return position;
} 

int caminhos(leitura *jogo)
{
    int i=0,j=0,x=0,y=0,jj=0;
    char position='I';

    for(i=0; i < jogo->n_linhas; i++){
        for(j=jj; j < jogo->n_colunas; j++){
            if(jogo->matriz_jogo[i][j] == 'A'){
                position=mega_position(jogo,&i,&j,'I',&x,&y);
                if(position == 'H')
                    return -1;
                if(position != 'V'){
                    colocar_tenda_relva(jogo,x,y,'T');
                    decrementar_vetores(jogo,x,y);
                }
                Push(i,j,position);
            }
        }
        position=verifica_B(jogo,&i,&j,&x,&y,position,&jj);
        if(position == 'H')
            return -1;       
        position ='I'; 
    }
    return verifica_linhas_colunas(jogo); 
}

void relva_linha(leitura *jogo,int atual)
{
    int i=0;

    for(i=0; i < jogo->n_colunas; i++){
        if(jogo->matriz_jogo[atual][i] == '.')
            jogo->matriz_jogo[atual][i]='R';
    }
    jogo->spaces_l[atual]=0;
}

void relva_coluna(leitura *jogo,int atual)
{
    int i=0;

    for(i=0; i < jogo->n_linhas; i++){
        if(jogo->matriz_jogo[i][atual] == '.')
            jogo->matriz_jogo[i][atual]='R';
    }
    jogo->spaces_c[atual]=0;
}

void linha_coluna_zero(leitura *jogo,int i,char modo)
{
    if(modo == 'L'){
        if(jogo->linhas[i] == 0)
            relva_linha(jogo,i);
    }
    else{
        if(jogo->colunas[i] == 0)
            relva_coluna(jogo,i);
    }    
}

void colocar_relva_adjacente_tenda(leitura *jogo,int i,int j)
{
    int vect[2]={0}; /* {Cima,Baixo} */

    if(i != 0){ /* Cima */
        if(jogo->matriz_jogo[i-1][j] == '.')
            jogo->matriz_jogo[i-1][j]='R';
        vect[0]=1;
    }

    if(i != (jogo->n_linhas-1)){ /* Baixo */
        if(jogo->matriz_jogo[i+1][j] == '.')
            jogo->matriz_jogo[i+1][j]='R';
        vect[1]=1;
    }

    if(j != 0){ /* Esquerda */
        if(jogo->matriz_jogo[i][j-1] == '.')
            jogo->matriz_jogo[i][j-1]='R';
        if(vect[0]==1)
            if(jogo->matriz_jogo[i-1][j-1] == '.')
                jogo->matriz_jogo[i-1][j-1]='R';
        if(vect[1]==1)
            if(jogo->matriz_jogo[i+1][j-1] == '.')
                jogo->matriz_jogo[i+1][j-1]='R';
    }

    if(j != (jogo->n_colunas-1)){ /* Direita */
        if(jogo->matriz_jogo[i][j+1] == '.')
            jogo->matriz_jogo[i][j+1]='R';
        if(vect[0]==1)
            if(jogo->matriz_jogo[i-1][j+1] == '.')
                jogo->matriz_jogo[i-1][j+1]='R';
        if(vect[1]==1)
            if(jogo->matriz_jogo[i+1][j+1] == '.')
                jogo->matriz_jogo[i+1][j+1]='R';
    }
}

void unic_space(leitura *jogo,int i,int j)
{
    int x=0,y=0;

    if(jogo->matriz_jogo[i][j] == 'A' && jogo->epoca == 'A'){
        if(arvores_tendas_adjacentes(jogo,&x,&y,i,j,'.') == 1){
            if(jogo->linhas[x] > 0 && jogo->colunas[y] > 0){
                colocar_tenda_relva(jogo,x,y,'T');
                decrementar_vetores(jogo,x,y);
                colocar_relva_adjacente_tenda(jogo,x,y);
                jogo->matriz_jogo[i][j]='B'; /* B = arvores com tenda, para nao serem encontradas nos caminhos */
            }
        }
    }
}

void sem_arvore(leitura *jogo,int i,int j)
{
    int x=0,y=0;

    if(arvores_tendas_adjacentes(jogo,&x,&y,i,j,'A') == 0 && jogo->matriz_jogo[i][j] == '.'){
        colocar_tenda_relva(jogo,i,j,'R');
        jogo->spaces_l[i]--;
        jogo->spaces_c[j]--;       
    }
}

void main_jogo(leitura *jogo)
{
    int i=0,j=0;

    for(i=0; i < jogo->n_linhas; i++){
        for(j=0; j < jogo->n_colunas; j++) {
            linha_coluna_zero(jogo,j,'C');
            sem_arvore(jogo,i,j); 
            unic_space(jogo,i,j);
        }
        linha_coluna_zero(jogo,i,'L');
    }       
    return;
}

void libertar_struct(leitura* jogo)
{
  int i=0;

  free(jogo->linhas);
  free(jogo->spaces_l);
  free(jogo->colunas);
  free(jogo->spaces_c);
  for (i=0;i<jogo->n_linhas;i++)
    free(jogo->matriz_jogo[i]);
  free(jogo->matriz_jogo);
}

int conta_digitos(int n)
{
    int count = 0;
    
    while(n != 0){
        n /= 10;
        ++count;
    }
    return count;
}

int main(int argc, char *argv[])
{
    char *ficheiro=NULL;
    leitura *jogo;
    FILE *fp=NULL;

    verifica_argumentos(argc,argv);
    fp=abre_ficheiro (argv[1], "r");

    jogo =(leitura*)malloc(sizeof(leitura));
    if (jogo == NULL){
        exit(EXIT_FAILURE);
    }

    ficheiro=argv[1]; /* Guarda o nome do ficheiro de entrada */
    le_ficheiro (fp, jogo, ficheiro);
    
    free(jogo);
    fclose(fp);

    exit(0);
}