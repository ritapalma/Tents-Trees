/******************************************************************************
* 1 Semestre 2019/2020 -AED 
* Autores: Pedro Ventura, 93155 & Rita Palma, 93172 
*
* NOME
*   jogo.h
*
* DESCRICAO
*   Fun��es para para ser poss�vel a resolu��o do mapa
*
******************************************************************************/

#ifndef _jogo_
#define _jogo_

/*****************************************************************************
 *  Data Type: leitura
 *
 *  Descricao: Estrutura com:
 *      1) numero de linhas e numero de colunas do mapa (dimensao da matriz);
 *      2) numero de arvores lidas no mapa;
 *      3) vetor de tendas por linha e por colunas;
 *      4) numero de possibilidades de por tendas por linha/coluna;
 *      5) matriz com o mapa de jogo, que � constantemente alterada;
 *      6) epoca do mapa de jogo.
 * 
 **************************************************************************/
typedef struct _leitura {
  int n_linhas, n_colunas, n_arvores;
  int *linhas, *colunas,*spaces_l,*spaces_c;
  char **matriz_jogo;
  char epoca;
}leitura;


/**************************************************************************
 *  Funcao:
 *    ve_ponto
 *
 *  Descricao:
 *    Verifica a exist�ncia de um ponto na posi��o i,j, se este existir 
 *    envia por referencia as coordenadas do ponto que existe.
 * 
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *    Coordenadas x,y;
 *
 *  Return:
 *    Retorna 1 se existir um ponto na posi��o, -1 caso contr�rio.
 *************************************************************************/
int ve_ponto(leitura *, int , int ,int *, int *);


/**************************************************************************
 *  Funcao:
 *    verifica_position
 *
 *  Descricao:
 *    Verifica a posi��o onde existe um ponto, 
 *    em rela��o � esquerda, cima, baixo, direita da posi��o em quest�o.
 *
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *    Coordenadas x,y;
 *    Position, que corresponde a ultima posicao experimentada;
 *
 *  Return:
 *    Retorna a inicial da posi��o ou uma letra diferente para sabermos
 *    que n�o � possivel a coloca��o da tenda, envia por referencia 
 *    as coordenadas da tenda colocada.
 *************************************************************************/
char verifica_position(leitura *, char , int , int ,int *,int *);


/**************************************************************************
 *  Funcao:
 *    arvores_tendas_adjacentes
 *
 *  Descricao:
 *    Verifica a exist�ncia de arvores/tendas adjacentes 
 *    (cima, baixo,esquerda,direita)
 *    consoante a letra 'A' ou 'T', 
 *
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *    Coordenadas x,y; 
 *    Modo, que corresponde a letra que se procura nas adjacencias;
 *
 *  Return:
 *    Retorna o n�mero de arvores/tendas adjacentes
 *************************************************************************/
int arvores_tendas_adjacentes(leitura* ,int *,int *,int ,int ,char ); 


/**************************************************************************
 *  Funcao:
 *    tendas_diagonais
 *
 *  Descricao:
 *    Verifica a exist�ncia de tendas diagonais � posi��o i, j 
 *  
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *
 *  Return:
 *    Retorna 1 se existirem tendas diagonais e 0 caso contrario.
*************************************************************************/
int tendas_diagonais(leitura* ,int ,int );


/**************************************************************************
 *  Funcao:
 *    modo_B
 *
 *  Descricao:
 *    Verifica se � possivel colocar uma tenda na posi��o i, j,
 *    consoante diversas fun��es referidas anteriormente   
 *
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *
 *  Return:
 *    Retorna 0 se for possivel, 1 caso contr�rio.
 *************************************************************************/
int modo_B(leitura* ,int , int );


/**************************************************************************
 *  Funcao:
 *    colocar_tenda_relva
 *
 *  Descricao:
 *   Coloca na matriz_jogo 'T'/'R', consoante o argumento, na posi��o i,j
 * 
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *    Modo;
 *
 *  Return:
 *    Nenhum
 *************************************************************************/
void colocar_tenda_relva(leitura *,int ,int ,char );


/**************************************************************************
 *  Funcao:
 *    decrementar_vetores
 *
 *  Descricao:
 *    Decrementa os vetores jogo->colunas, jogo->linhas,
 *    jogo->spaces_l, jogo->spaces_c, da struct leitura
 *    na posicao i, j
 *  
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *
 *  Return:
 *    Nenhum
 *************************************************************************/
void decrementar_vetores(leitura *,int ,int );


/**************************************************************************
 *  Funcao:
 *    tira_do_mapa
 *
 *  Descricao:
 *    Tira do mapa a letra enviada como argumento e
 *    coloca nessa posi��o i, j  um '.', 
 *    incrementando os 4 vetores anteriores na posicao i,j
 * 
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *    Modo ;
 *
 *  Return:
 *    Nenhum
 *************************************************************************/
void tira_do_mapa(leitura *,int ,int ,char );


/**************************************************************************
 *  Funcao:
 *    mega_position
 *
 *  Descricao:
 *    Gera todos os caminhos para a resolu��o do mapa de jogo.
 * 
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *    Coordenadas x,y ;
 *    Position
 *
 *  Return:
 *    Retorna o char da posi��o escolhida (E,C,B,D,V,H)
*************************************************************************/
char mega_position(leitura *,int *,int *,char ,int *,int *);


/**************************************************************************
 *  Funcao:
 *    verifica_linhas_colunas
 *
 *  Descricao:
 *    Verifica se o vetor do n�mero de tendas por linha/coluna � nulo 
 * 
 *  Argumentos:
 *    Struct leitura;
 *
 *  Return:
 *    Retorna 1 se o vetor for nulo,1 caso contrario 
*************************************************************************/
int verifica_linhas_colunas(leitura *);


/**************************************************************************
 *  Funcao:
 *    verifica_b_aux
 *
 *  Descricao:
 *    Fun��o auxiliar do verifica_b, utilizada em epoca baixa, 
 *    procura uma nova posi��o para uma tenda, 
 *    consoante diversos parametros; 
 * 
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *    Coordenadas x,y ;
 *    Position
 *    Posicao jj
 *
 *  Return:
 *    Retorna o char da posi��o escolhida (E,C,B,D,V)
*************************************************************************/
char verifica_B_aux(leitura *,int *,int *,int *,int *,char ,int *);


/**************************************************************************
 *  Funcao:
 *    verifica_B
 *
 *  Descricao:
 *    Verifica se a linhas anterior � em quest�o 
 *    esta com 0 tendas por colocar.
 * 
 *  Argumentos:
 *    Posicao i, j ;
 *    Struct leitura;
 *    Coordenadas x,y ;
 *    Position
 *    Posicao jj
 *
 *  Return:
 *  Retorna o char da posi��o escolhida (E,C,B,D,V).
*************************************************************************/
char verifica_B(leitura *,int *,int *,int *,int *,char ,int *);

/**************************************************************************
 *  Funcao:
 *    caminhos
 *
 *  Descricao:
 *    Percorre a matriz de jogo e comporta-se de diferentes formas,
 *    consoante o que verifica na matriz
 * 
 *  Argumentos:
 *    Struct leitura;
 *
 *  Return:
 *    Retorna 1 se o mapa tiver sido resolvido, 
 *    -1 se nao for possivel resolver
*************************************************************************/
int caminhos(leitura *);


/**************************************************************************
 *  Funcao:
 *    relva_linha
 *
 *  Descricao:
 *    Coloca 'R' em todos os '.' da linha i da matriz lida;
 * 
 *  Argumentos:
 *    Struct leitura;
 *    Posicao i;
 *
 *  Return:
 *    Nenhum
*************************************************************************/
void relva_linha(leitura *,int );


/**************************************************************************
 *  Funcao:
 *    relva_coluna
 *
 *  Descricao:
 *    Coloca 'R' em todos os '.' da coluna i da matriz lida;
 * 
 *  Argumentos:
 *    Struct leitura;
 *    Posicao i;
 *
 *  Return:
 *    Nenhum
*************************************************************************/
void relva_coluna(leitura *,int );


/**************************************************************************
 *  Funcao:
 *    linha_coluna_zero
 *
 *  Descricao:
 *    Verifica se a posi��o i do vetor linhas/colunas � nula 
 *    consoante o modo 'L'/'C', respetivamente 
 * 
 *  Argumentos:
 *    Struct leitura;
 *    Posicao i;
 *    Modo;
 *
 *  Return:
 *    Nenhum
*************************************************************************/
void linha_coluna_zero(leitura *,int ,char );


/**************************************************************************
 *  Funcao:
 *    colocar_relva_adjacente_tenda
 *
 *  Descricao:
 *    Coloca 'R' em todas as 8 posi��es (quando ha pontos nas mesmas) 
 *    ao redor de uma tenda na posi��o i,j
 * 
 *  Argumentos:
 *    Struct leitura;
 *    Posicao i,j;
 *
 *  Return:
 *    Nenhum
*************************************************************************/
void colocar_relva_adjacente_tenda(leitura *,int ,int );


/**************************************************************************
 *  Funcao:
 *    sem_arvore
 *
 *  Descricao:
 *    Coloca 'R' em todas as posi��es onde n�o � possivel
 *    haver existencia de uma tenda, pois n�o existe uma arvore adjacente
 *    e todas as tendas t�m que estar colocadas junto a uma �rvore
 * 
 *  Argumentos:
 *    Struct leitura;
 *    Posicao i,j;
 *
 *  Return:
 *    Nenhum
*************************************************************************/
void sem_arvore(leitura *,int ,int );


/**************************************************************************
 *  Funcao:
 *    unic_space
 *
 *  Descricao:
 *    Coloca uma tenda junto a uma �rvore que s� � tem um espa�o
 *    para por uma tenda em seu redor e,
 *    coloca a �rvore da matriz como um 'B',
 *    para esta n�o ser encontrada quando percorremos os caminhos.
 * 
 *  Argumentos:
 *    Struct leitura;
 *    Posicao i,j;
 *
 *  Return:
 *    Nenhum
*************************************************************************/
void unic_space(leitura *jogo,int i,int j);


/**************************************************************************
 *  Funcao:
 *    main_jogo
 *
 *  Descricao:
 *    Executa a parte l�gica do jogo.
 * 
 *  Argumentos:
 *    Struct leitura;
 *
 *  Return:
 *    Nenhum
*************************************************************************/
void main_jogo(leitura *);


/**************************************************************************
 *  Funcao:
 *    libertar_struct 
 *
 *  Descricao:
 *    Liberta a Struct leitura, fazendo free de toda a mem�ria alocada,
 *    a cada mapa de jogo 
 * 
 *  Argumentos:
 *    Struct leitura;
 *
 *  Return:
 *    Nenhum
*************************************************************************/
void libertar_struct(leitura* );


/**************************************************************************
 *  Funcao:
 *    conta_digitos 
 *
 *  Descricao:
 *    Fun��o utilizada para ser possivel ler
 *    diversos mapas no mesmo ficheiro
 * 
 *  Argumentos:
 *    Inteiro lido quando h� um proximo ficheiro;
 *
 *  Return:
 *    Nenhum
*************************************************************************/
int conta_digitos(int );


/**************************************************************************
 *  Funcao:
 *    main 
 *
 *  Descricao:
 *    Funcao que coordena todo o programa.
 * 
 *  Argumentos:
 *    Argumentos inseridos na linha de comando;
 *
 *  Return:
 *    Da exit(0) no final do programa
*************************************************************************/
int main(int , char *[]);


#endif /* _jogo_ */
