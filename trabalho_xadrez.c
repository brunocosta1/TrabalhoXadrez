#include "stdio.h"
#include "stdlib.h"

#define PEAO    1
#define CAVALO  2
#define BISPO   3
#define TORRE   4
#define RAINHA  5
#define REI     6

typedef struct{
    int deLinha,deColuna,paraLinha,paraColuna;
    struct Jogada *prox, *ant;
}Jogada;

struct Peca
{
    int codigo;
    int linha, coluna;
    int ataques;
    struct Peca *prox, *ant;
};

struct Posicao
{
    int qtdBrancas;
    struct Peca *brancas;
    
    int qtdPretas;
    struct Peca *pretas;

    int jogVez;

    struct Peca *tab[8][8];
};

//Funções de operação entre listas.

struct Peca *CriaLista()
{
    struct Peca *sentinela = (struct Peca*)malloc(sizeof(struct Peca));
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;
    return sentinela;
}

struct Peca *CriaPeca(int codigo, int linha, int coluna)
{
    struct Peca *resp = (struct Peca*)malloc(sizeof(struct Peca));
    resp->codigo = codigo;
    resp->linha = linha;
    resp->coluna = coluna;

    resp->prox = NULL;
    resp->ant = NULL;
    
    return resp;    
} 

void InsereInicio(struct Peca *lista, int codigo, int linha, int coluna)
{
    struct Peca *novo = CriaPeca(codigo, linha, coluna);
    novo->prox = lista->prox;
    novo->ant = lista;
    lista->prox->ant = novo;
    lista->prox = novo;
}

struct Peca *Busca(struct Peca *lista, int codigo, int linha, int coluna)
{
    struct Peca *aux = lista->prox;
    while(aux != lista && aux->codigo != codigo && aux->linha != linha && aux->coluna != coluna)
        aux = aux->prox;

    if(aux != lista)
        return aux;
    else
        return NULL;

}
    
void Remove(struct Peca *lista, int codigo, int linha, int coluna)
{
    struct Peca *aux = Busca(lista, codigo, linha, coluna);
    if(aux != NULL)
    {
        aux->prox->ant = aux->ant;
        aux->ant->prox = aux->prox;
        free(aux);
    }
}

struct Peca *DestruirLista(struct Peca *lista)
{
    struct Peca *aux = lista;
    lista->ant->prox = NULL;
    while(aux != NULL)
    {
        lista = lista->prox;
        free(aux);
        aux = lista;
    }
    return NULL;
}

void ResetCor(){
    printf("\033[0m");
}

void AjustaCor(int peca){
    switch(abs(peca)){
    case PEAO: printf("\033[0;36m");break;
    case CAVALO: printf("\033[1;33m");break;
    case BISPO: printf("\033[0;35m");break;
    case TORRE: printf("\033[0;32m");break;
    case RAINHA: printf("\033[0;34m");break;
    case REI: printf("\033[1;31m");break;
    }
}

Jogada CriaJogada(int deLinha, int deColuna, int paraLinha, int paraColuna){
    Jogada jog = {deLinha,deColuna,paraLinha,paraColuna};
    return jog;
}

void DesenhaTabuleiro(struct Posicao posAtual){
    int i,j;
    system("clear");

    printf("    +---+---+---+---+---+---+---+---+\n");
    for (i=7;i>=0;i--){
        printf("%d   |",i+1);
        for (j=0;j<8;j++){
            AjustaCor(posAtual.tab[i][j]->codigo);
            if (posAtual.tab[i][j]>=0)
                printf(" %d",posAtual.tab[i][j]->codigo);
            else printf("%d",posAtual.tab[i][j]->codigo);
            ResetCor();
            printf(" |");
        }
        printf("\n    +---+---+---+---+---+---+---+---+\n");
    }
    printf("      1   2   3   4   5   6   7   8 \n");
}

int CalculaPeao(int tab[8][8],int linha,int coluna,Jogada jogs[]){
    Jogada jogada;
    int qtd = 0, peca = tab[linha][coluna];

    if (linha+peca>=0 && linha+peca<=7){//não está na primeira nem na última linha
        if (tab[linha+peca][coluna]==0){ //pode avancar
            jogs[qtd] = CriaJogada(linha,coluna,linha+peca,coluna); qtd++;
        }
        if (coluna>0 && tab[linha+peca][coluna-1]*peca<0){ //verificar captura na esquerda
            jogs[qtd] = CriaJogada(linha,coluna,linha+peca,coluna-1); qtd++;
        }
        if (coluna<7 && tab[linha+peca][coluna+1]*peca<0){
            jogs[qtd] = CriaJogada(linha,coluna,linha+peca,coluna+1); qtd++;
        }
    }
    return qtd;
}

int CalculaCavalo(int tab[8][8], int linha, int coluna, Jogada jogs[]){
    int qtd=0,peca = tab[linha][coluna];

    if (linha<6){ //duas linhas acima
        if (coluna<7 && tab[linha+2][coluna+1]*peca<=0){ //direita
            jogs[qtd] = CriaJogada(linha,coluna,linha+2,coluna+1); qtd++;
        }
        if (coluna>0 && tab[linha+2][coluna-1]*peca<=0){ //esquerda
            jogs[qtd] = CriaJogada(linha,coluna,linha+2,coluna-1); qtd++;
        }
    }
    if (linha<7){//uma linha acima
        if (coluna<6 && tab[linha+1][coluna+2]*peca<=0){ //duas casas à direita
            jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna+2); qtd++;
        }
        if (coluna>1 && tab[linha+1][coluna-2]*peca<=0){ //duas casas à esquerda
            jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna-2); qtd++;
        }
    }
    if (linha>1){ //duas linhas abaixo
        if (coluna<7 && tab[linha-2][coluna+1]*peca<=0){ //direita
            jogs[qtd] = CriaJogada(linha,coluna,linha-2,coluna+1); qtd++;
        }
        if (coluna>0 && tab[linha-2][coluna-1]*peca<=0){ //esquerda
            jogs[qtd] = CriaJogada(linha,coluna,linha-2,coluna-1); qtd++;
        }
    }
    if (linha>0){//uma linha abaixo
        if (coluna<6 && tab[linha-1][coluna+2]*peca<=0){ //duas casas à direita
            jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna+2); qtd++;
        }
        if (coluna>1 && tab[linha-1][coluna-2]*peca<=0){ //duas casas à esquerd
            jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna-2); qtd++;
        }
    }
    return qtd;
}

int CalculaBispo(int tab[8][8], int linha, int coluna, Jogada jogs[]){
    int qtd = 0,peca = tab[linha][coluna];

    int k=0;

    do{//diagonal superior direita
        k++;
        if (linha+k<8 && coluna+k<8 && tab[linha+k][coluna+k]*peca<=0){
            jogs[qtd] = CriaJogada(linha,coluna,linha+k,coluna+k); qtd++;
        }
    }while (linha+k<8 && coluna+k<8 && tab[linha+k][coluna+k]==0);

    k=0;
    do{//diagonal superior esquerda
        k++;
        if (linha+k<8 && coluna-k>=0 && tab[linha+k][coluna-k]*peca<=0){
            jogs[qtd] = CriaJogada(linha,coluna,linha+k,coluna-k); qtd++;
        }
    }while (linha+k<8 && coluna-k>=0 && tab[linha+k][coluna-k]==0);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna+k<8 && tab[linha-k][coluna+k]*peca<=0){
            jogs[qtd] = CriaJogada(linha,coluna,linha-k,coluna+k); qtd++;
        }
    }while (linha-k>=0 && coluna+k<8 && tab[linha-k][coluna+k]==0);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna-k>=0 && tab[linha-k][coluna-k]*peca<=0){
            jogs[qtd] = CriaJogada(linha,coluna,linha-k,coluna-k); qtd++;
        }
    }while (linha-k>=0 && coluna+k>=0 && tab[linha-k][coluna-k]==0);

    return qtd;
}

int CalculaTorre(int tab[8][8], int linha, int coluna, Jogada jogs[]){
    int qtd = 0, peca=tab[linha][coluna];

    int k=0;

    do{//coluna acima
        k++;
        if (linha+k<8 && tab[linha+k][coluna]*peca<=0){
            jogs[qtd] = CriaJogada(linha,coluna,linha+k,coluna); qtd++;
        }
    }while(linha+k<8 && tab[linha+k][coluna]==0);

    k=0;
    do{//coluna abaixo
        k++;
        if (linha-k>=0 && tab[linha-k][coluna]*peca<=0){
            jogs[qtd] = CriaJogada(linha,coluna,linha-k,coluna); qtd++;
        }
    }while(linha-k>=0 && tab[linha-k][coluna]==0);

    k=0;
    do{//linha direita
        k++;
        if (coluna+k<8 && tab[linha][coluna+k]*peca<=0){
            jogs[qtd] = CriaJogada(linha,coluna,linha,coluna+k); qtd++;
        }
    }while(coluna+k<8 && tab[linha][coluna+k]==0);

    k=0;
    do{//linha esquerda
        k++;
        if (coluna-k>=0 && tab[linha][coluna-k]*peca<=0){
            jogs[qtd] = CriaJogada(linha,coluna,linha,coluna-k); qtd++;
        }
    }while(coluna-k>=0 && tab[linha][coluna-k]==0);

    return qtd;
}

int CalculaRei(int tab[8][8], int linha, int coluna,Jogada jogs[]){
    int qtd = 0, peca=tab[linha][coluna];

    if (linha<7){//linha de cima
        if (tab[linha+1][coluna]*peca<=0){//mesma coluna
            jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna); qtd++;
        }
        if (coluna<7 && tab[linha+1][coluna+1]*peca<=0){//superior direita
            jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna+1); qtd++;
        }
        if (coluna>=0 && tab[linha+1][coluna-1]*peca<=0){//superior esquerda
            jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna-1); qtd++;
        }
    }

    if (linha>0){//linha de baixo
        if (tab[linha-1][coluna]*peca<=0){//mesma coluna
            jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna); qtd++;
        }
        if (coluna<7 && tab[linha-1][coluna+1]*peca<=0){//inferior direita
            jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna+1); qtd++;
        }
        if (coluna>=0 && tab[linha-1][coluna-1]*peca<=0){//inferior esquerda
            jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna-1); qtd++;
        }
    }

    if (coluna<7 && tab[linha][coluna+1]*peca<=0){ //mesma linha, casa da direita
        jogs[qtd] = CriaJogada(linha,coluna,linha,coluna+1); qtd++;
    }

    if (coluna>0 && tab[linha][coluna-1]*peca<=0){ //mesma linha, casa da esquerda
        jogs[qtd] = CriaJogada(linha,coluna,linha,coluna-1); qtd++;
    }

    return qtd;
}

struct Posicao IniciaTabuleiro()
{
    int i,j;
    struct Posicao posInicial;
    posInicial.brancas = CriaLista();
    posInicial.pretas = CriaLista();    
    posInicial.qtdPretas = posInicial.qtdBrancas = 16;
    posInicial.jogVez = 1;


    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            if (i==1)
            {
                InsereInicio(posInicial.brancas, PEAO, i, j);
                posInicial.tab[i][j]= posInicial.brancas->prox;//peões branco
            }
            else if (i==6)
            {    
                InsereInicio(posInicial.pretas, -PEAO, i, j);
                posInicial.tab[i][j]= posInicial.pretas->prox;//peões preto
            }

            else posInicial.tab[i][j] = NULL;//outras casas

    InsereInicio(posInicial.brancas, TORRE, 0, 0);
    posInicial.tab[0][0] = posInicial.brancas->prox;

    InsereInicio(posInicial.brancas, TORRE, 0, 7);
    posInicial.tab[0][7] = posInicial.brancas->prox;


    
    InsereInicio(posInicial.pretas, -TORRE, 7, 0);
    posInicial.tab[7][0] = posInicial.pretas->prox; 

    InsereInicio(posInicial.pretas, -TORRE, 7, 7);
    posInicial.tab[7][7] =posInicial.pretas->prox;

    
    InsereInicio(posInicial.brancas, CAVALO, 0, 1);
    posInicial.tab[0][1] = posInicial.brancas->prox;

    InsereInicio(posInicial.brancas, CAVALO, 0, 6);
    posInicial.tab[0][6] = posInicial.brancas->prox;

    InsereInicio(posInicial.pretas, -CAVALO, 7, 1);
    posInicial.tab[7][1] = posInicial.pretas->prox;
    
    InsereInicio(posInicial.pretas, -CAVALO, 7, 6);
    posInicial.tab[7][6] = posInicial.pretas->prox;


    InsereInicio(posInicial.brancas, BISPO, 0, 2);
    posInicial.tab[0][2] = posInicial.brancas->prox;

    InsereInicio(posInicial.brancas, BISPO, 0, 5);
    posInicial.tab[0][5] = posInicial.brancas->prox;

    InsereInicio(posInicial.pretas, -BISPO, 7, 2);
    posInicial.tab[7][2] = posInicial.pretas->prox;

    InsereInicio(posInicial.pretas, -BISPO, 7, 5);
    posInicial.tab[7][5] = posInicial.pretas->prox;


    InsereInicio(posInicial.brancas, RAINHA, 0, 3);
    posInicial.tab[0][3] = posInicial.brancas->prox;
    
    InsereInicio(posInicial.brancas, REI, 0, 4);
    posInicial.tab[0][4] = posInicial.brancas->prox;


    InsereInicio(posInicial.pretas, -RAINHA, 7, 3);
    posInicial.tab[7][3] = posInicial.pretas->prox;

    InsereInicio(posInicial.pretas, -REI, 7, 4);
    posInicial.tab[7][4] = posInicial.pretas->prox;
    

    return posInicial;
}

void EscolhePeca(int tab[8][8],int *linha, int *coluna){
    do{
        printf("Digite a linha e a coluna da peca a ser movida:");
        scanf("%d %d",linha,coluna); //lê valores de 1 a 8
        (*linha)--; //converte para valores de 0 a 7
        (*coluna)--;
        if (tab[*linha][*coluna]==0){
            printf("Nao tem peca nessa casa!!!\n");
        }
    }while (tab[*linha][*coluna]==0);
}

int CalculaJogadas(int tab[8][8],int linha, int coluna, Jogada jogs[]){
    int aux, peca = tab[linha][coluna];
    switch (abs(peca)){
    case PEAO:   return CalculaPeao(tab,linha,coluna,jogs);break;//peoes
    case CAVALO: return CalculaCavalo(tab,linha,coluna,jogs);break;//cavalos
    case BISPO:  return CalculaBispo(tab,linha,coluna,jogs);break;//bispos
    case TORRE:  return CalculaTorre(tab,linha,coluna,jogs);break;//torres
    case RAINHA: aux = CalculaBispo(tab,linha,coluna,jogs);
                 aux += CalculaTorre(tab,linha,coluna,&jogs[aux]);
                 return aux;
                 break;
    case REI:    return CalculaRei(tab,linha,coluna,jogs);break;//rei
    }
}

int EscolheJogada(int qtd, Jogada jogs[]){
    int i,j,op;
    do{
        for (i=0;i<qtd;i++){
            printf("Jogada %2d: mover para linha %d coluna %d |",i+1,jogs[i].paraLinha+1,jogs[i].paraColuna+1);
            if ( (i+1) % 3 == 0)
                printf("\n");
        }
        printf("\nJogada:");
        scanf("%d",&op);
    }while (op<1 || op>qtd);
    return op;
}

int ExecutaJogada(int tab[8][8],Jogada jog){
    int resp=0, peca = tab[jog.deLinha][jog.deColuna];

    tab[jog.deLinha][jog.deColuna] = 0; //tira a peça

    if (abs(tab[jog.paraLinha][jog.paraColuna])==REI) //verifica se o rei adversário será capturado
        resp = peca; //resp indica quem será vencedor

    tab[jog.paraLinha][jog.paraColuna] = peca; //coloca a peça na nova posição

    return resp;
}

int main(){
    int tab[8][8];
    int vencedor=0,linha,coluna,escolha;
    int qtdJogadas;
    Jogada jogadas[30];
    struct Posicao posAtual;

    posAtual = IniciaTabuleiro();
    while (vencedor==0){
        DesenhaTabuleiro(posAtual);
        EscolhePeca(tab,&linha,&coluna);
        qtdJogadas = CalculaJogadas(tab,linha,coluna,jogadas);
        if (qtdJogadas>0){
            escolha = EscolheJogada(qtdJogadas,jogadas);
            vencedor = ExecutaJogada(tab,jogadas[escolha-1]);
        }else printf("Nao ha jogadas disponiveis!");
    }
    if (vencedor>0){
        printf("Brancas venceram!");
    }else printf("Pretas venceram!");
}
