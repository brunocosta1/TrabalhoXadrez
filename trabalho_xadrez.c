#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PEAO    1
#define CAVALO  2
#define BISPO   3
#define TORRE   4
#define RAINHA  5
#define REI     6


struct Jogada{
    int deLinha,deColuna,paraLinha,paraColuna;
    struct Jogada *prox, *ant;
};

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

//Funções de operações entre listas (lista de jogadas possíveis).

struct Jogada *CriaListaJogadas()
{
    struct Jogada *sentinela = (struct Jogada*)malloc(sizeof(struct Jogada));
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;
    return sentinela;
}


struct Jogada *CriaJogada(int deLinha, int deColuna, int paraLinha, int paraColuna){

    struct Jogada *resp = (struct Jogada*)malloc(sizeof(struct Jogada));
    resp->deLinha = deLinha;
    resp->deColuna = deColuna;
    resp->paraLinha = paraLinha;
    resp->paraColuna = paraColuna;

    resp->prox = NULL;
    resp->ant = NULL;
    
    return resp;

}

void InsereJogadaInicio(struct Jogada *lista, int deLinha, int deColuna, int paraLinha, int paraColuna){
    
    struct Jogada *novo = CriaJogada(deLinha, deColuna, paraLinha, paraColuna);
    novo->prox = lista->prox;
    novo->ant = lista;
    lista->prox->ant = novo;
    lista->prox = novo;
    
}

struct Jogada *BuscaJogada(struct Jogada *lista, int deLinha, int deColuna, int paraLinha, int paraColuna){
   
    struct Jogada *aux = lista->prox;

    while(aux != lista && !(aux->deLinha == deLinha && aux->deColuna == deColuna && aux->paraLinha == paraLinha && aux->paraColuna == paraColuna))
        aux = aux->prox;

    if(aux != lista)
        return aux;
    else
        return NULL;
}
struct Jogada *DestruirListaJogadas(struct Jogada *lista){
    struct Jogada *aux = lista;
    lista->ant->prox = NULL;
    while(aux != NULL)
    {
        lista = lista->prox;
        free(aux);
        aux = lista;
    }

    return NULL;
}

void CalculaPeao(struct Posicao pos,int linha,int coluna, struct Jogada *lista){ 
    int qtd = 0, peca = pos.tab[linha][coluna]->codigo;
 

    if (linha+peca>=0 && linha+peca<=7){//n?o est? na primeira nem na ?ltima linha
        if (pos.tab[linha+peca][coluna]==NULL){ //pode avancar
            //jogs[qtd] = CriaJogada(linha,coluna,linha+peca,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+peca, coluna);
            
        }
        if (coluna>0 && pos.tab[linha+peca][coluna-1] != NULL && pos.tab[linha+peca][coluna-1]->codigo*peca<0){ //verificar captura na esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha+peca,coluna-1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+peca, coluna-1);
            pos.tab[linha+peca][coluna-1]->ataques++;
        }
        if (coluna<7 && pos.tab[linha+peca][coluna+1] != NULL && pos.tab[linha+peca][coluna+1]->codigo*peca<0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha+peca,coluna+1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+peca, coluna+1);
            pos.tab[linha+peca][coluna+1]->ataques++;
        }
    }
    
    if(pos.tab[linha+peca][coluna] == NULL && pos.tab[linha+2*peca][coluna] == NULL){
        if(linha == 1 && pos.tab[linha][coluna]->codigo > 0)
            InsereJogadaInicio(lista, linha, coluna, linha+2*peca, coluna);

        if(linha == 6 && pos.tab[linha][coluna]->codigo < 0){
            InsereJogadaInicio(lista, linha, coluna, linha+2*peca, coluna);
        }


    }

}

void CalculaCavalo(struct Posicao pos, int linha, int coluna, struct Jogada *lista){
    int qtd=0,peca = pos.tab[linha][coluna]->codigo;


    if (linha<6){ //duas linhas acima
        if (coluna<7){ //direita
            if(pos.tab[linha+2][coluna+1] == NULL)
                InsereJogadaInicio(lista, linha, coluna, linha+2, coluna+1);
            else if(pos.tab[linha+2][coluna+1]->codigo*peca<0){
                InsereJogadaInicio(lista, linha, coluna, linha+2, coluna+1);
                pos.tab[linha+2][coluna+1]->ataques++;
            }
        }
        if (coluna>0){ //esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha+2,coluna-1); qtd++;
            if(pos.tab[linha+2][coluna-1] == NULL)
                InsereJogadaInicio(lista, linha, coluna, linha+2, coluna-1);
            else if(pos.tab[linha+2][coluna-1]->codigo*peca<0){
                InsereJogadaInicio(lista, linha, coluna, linha+2, coluna-1);
                pos.tab[linha+2][coluna-1]->ataques++;
            }
        }
    }

    if (linha<7){//uma linha acima
        if (coluna<6){ //duas casas ? direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna+2); qtd++;
            if(pos.tab[linha+1][coluna+2] == NULL)
                InsereJogadaInicio(lista, linha, coluna, linha+1, coluna+2);
            else if(pos.tab[linha+1][coluna+2]->codigo*peca<0) {
                InsereJogadaInicio(lista, linha, coluna, linha+1, coluna+2);
                pos.tab[linha+1][coluna+2]->ataques++;
            }
        }
        if (coluna>1 && (pos.tab[linha+1][coluna-2] == NULL ||pos.tab[linha+1][coluna-2]->codigo*peca<0)){ //duas casas ? esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna-2); qtd++;
            if(pos.tab[linha+1][coluna-2] == NULL)
                InsereJogadaInicio(lista, linha, coluna, linha+1, coluna-2);
            else if(pos.tab[linha+1][coluna-2]->codigo*peca<0){
                InsereJogadaInicio(lista, linha, coluna, linha+1, coluna-2);
                pos.tab[linha+1][coluna-2]->ataques++;
            }
        }
    }
    if (linha>1){ //duas linhas abaixo
        if (coluna<7){ //direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha-2,coluna+1); qtd++;
            if(pos.tab[linha-2][coluna+1] == NULL)
                InsereJogadaInicio(lista, linha, coluna, linha-2, coluna+1);
            else if(pos.tab[linha-2][coluna+1]->codigo*peca<0){
                InsereJogadaInicio(lista, linha, coluna, linha-2, coluna+1);
                pos.tab[linha-2][coluna+1]->ataques++;
            }
        }
        if (coluna>0){ 
            //jogs[qtd] = CriaJogada(linha,coluna,linha-2,coluna-1); qtd++;
            if(pos.tab[linha-2][coluna-1] == NULL)
                InsereJogadaInicio(lista, linha, coluna, linha -2, coluna -1);
            else if(pos.tab[linha-2][coluna-1]->codigo*peca<0){
                InsereJogadaInicio(lista, linha, coluna, linha -2, coluna -1);
                pos.tab[linha-2][coluna-1]->ataques++;
            }
        }
    }
    if (linha>0){//uma linha abaixo
        if (coluna<6){
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna+2); qtd++;
            if(pos.tab[linha-1][coluna+2] == NULL)
                InsereJogadaInicio(lista, linha, coluna, linha-1, coluna+2);
            else if(pos.tab[linha-1][coluna+2]->codigo*peca<0){
                InsereJogadaInicio(lista, linha, coluna, linha-1, coluna+2);
                pos.tab[linha-1][coluna+2]->ataques++;
            }
        }
        if (coluna>1){
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna-2); qtd++;
            if(pos.tab[linha-1][coluna-2] == NULL)
                InsereJogadaInicio(lista, linha, coluna, linha -1, coluna-2);
            else if(pos.tab[linha-1][coluna-2]->codigo*peca<0){
                InsereJogadaInicio(lista, linha, coluna, linha -1, coluna-2);
                pos.tab[linha-1][coluna-2]->ataques++;
            }
        }
    }

}

void CalculaBispo(struct Posicao pos, int linha, int coluna, struct Jogada *lista){ 
    int qtd = 0,peca = pos.tab[linha][coluna]->codigo;
    
    int k=0;
    
    do{//diagonal superior direita
        k++;
        if (linha+k<8 && coluna+k<8 && (pos.tab[linha+k][coluna+k] == NULL || pos.tab[linha+k][coluna+k]->codigo*peca<0)){
            //jogs[qtd] = CriaJogada(linha,coluna,linha+k,coluna+k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+k, coluna+k);
            if(pos.tab[linha+k][coluna+k] != NULL && pos.tab[linha+k][coluna+k]->codigo*peca<0)
                pos.tab[linha+k][coluna+k]->ataques++;
        }
    }while (linha+k<8 && coluna+k<8 && pos.tab[linha+k][coluna+k]==NULL);

    k=0;
    do{//diagonal superior esquerda
        k++;
        if (linha+k<8 && coluna-k>=0 && (pos.tab[linha+k][coluna-k] == NULL || pos.tab[linha+k][coluna-k]->codigo*peca<0)){
            //jogs[qtd] = CriaJogada(linha,coluna,linha+k,coluna-k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+k, coluna-k);
            if(pos.tab[linha+k][coluna-k] != NULL && pos.tab[linha+k][coluna-k]->codigo*peca<0)
                pos.tab[linha+k][coluna-k]->ataques++;
        }
    }while (linha+k<8 && coluna-k>=0 && pos.tab[linha+k][coluna-k]==NULL);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna+k<8 && (pos.tab[linha-k][coluna+k] == NULL || pos.tab[linha-k][coluna+k]->codigo*peca<0)){
            //jogs[qtd] = CriaJogada(linha,coluna,linha-k,coluna+k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-k, coluna+k);
            if(pos.tab[linha-k][coluna+k] != NULL && pos.tab[linha-k][coluna+k]->codigo*peca<0)
                pos.tab[linha-k][coluna+k]->ataques++;
        }
    }while (linha-k>=0 && coluna+k<8 && pos.tab[linha-k][coluna+k]==NULL);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna-k>=0 && (pos.tab[linha-k][coluna-k] == NULL || pos.tab[linha-k][coluna-k]->codigo*peca<0)){
            //jogs[qtd] = CriaJogada(linha,coluna,linha-k,coluna-k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-k, coluna-k);
            if(pos.tab[linha-k][coluna-k] != NULL && pos.tab[linha-k][coluna-k]->codigo*peca<0)
                pos.tab[linha-k][coluna-k]->ataques++;

        }
    }while (linha-k>=0 && coluna+k>=0 && pos.tab[linha-k][coluna-k]==NULL);


}

void CalculaTorre(struct Posicao pos, int linha, int coluna, struct Jogada *lista){
    int qtd = 0, peca=pos.tab[linha][coluna]->codigo;
    int k=0;

    do{//coluna acima
        k++;
        if (linha+k<8 && (pos.tab[linha+k][coluna] == NULL || pos.tab[linha+k][coluna]->codigo*peca<0)){
            //jogs[qtd] = CriaJogada(linha,coluna,linha+k,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+k, coluna);
            if(pos.tab[linha+k][coluna] != NULL && pos.tab[linha+k][coluna]->codigo*peca<0)
                pos.tab[linha+k][coluna]->ataques++;
        }
    }while(linha+k<8 && pos.tab[linha+k][coluna]==NULL);

    k=0;
    do{//coluna abaixo
        k++;
        if (linha-k>=0 && (pos.tab[linha-k][coluna] == NULL || pos.tab[linha-k][coluna]->codigo*peca<0)){
            //jogs[qtd] = CriaJogada(linha,coluna,linha-k,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-k, coluna);
            if(pos.tab[linha-k][coluna] != NULL && pos.tab[linha-k][coluna]->codigo*peca<0)
                pos.tab[linha-k][coluna]->ataques++;
        }
    }while(linha-k>=0 && pos.tab[linha-k][coluna]==NULL);

    k=0;
    do{//linha direita
        k++;
        if (coluna+k<8 && (pos.tab[linha][coluna+k] == NULL || pos.tab[linha][coluna+k]->codigo*peca<0)){
            //jogs[qtd] = CriaJogada(linha,coluna,linha,coluna+k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha, coluna+k);
           if(pos.tab[linha][coluna+k] != NULL && pos.tab[linha][coluna+k]->codigo*peca<0)
               pos.tab[linha][coluna+k]->ataques++;
        }
    }while(coluna+k<8 && pos.tab[linha][coluna+k]==NULL);

    k=0;
    do{//linha esquerda
        k++;
        if (coluna-k>=0 && (pos.tab[linha][coluna-k] == NULL || pos.tab[linha][coluna-k]->codigo*peca<0)){
            //jogs[qtd] = CriaJogada(linha,coluna,linha,coluna-k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha, coluna-k);
            if(pos.tab[linha][coluna-k] != NULL && pos.tab[linha][coluna-k]->codigo*peca<0)
                pos.tab[linha][coluna-k]->ataques++;
        }
    }while(coluna-k>=0 && pos.tab[linha][coluna-k]==NULL);

}


void CalculaRei(struct Posicao pos, int linha, int coluna, struct Jogada *lista){
    int qtd = 0, peca=pos.tab[linha][coluna]->codigo;

    if (linha<7){//linha de cima
        if (pos.tab[linha+1][coluna] == NULL || pos.tab[linha+1][coluna]->codigo*peca<0){//mesma coluna
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+1,coluna);
            if(pos.tab[linha+1][coluna] != NULL && pos.tab[linha+1][coluna]->codigo*peca<0)
                pos.tab[linha+1][coluna]->ataques++;
        }
        if (coluna<7 && (pos.tab[linha+1][coluna+1] == NULL || pos.tab[linha+1][coluna+1]->codigo*peca<0)){//superior direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna+1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+1, coluna+1);
            if(pos.tab[linha+1][coluna+1] != NULL && pos.tab[linha+1][coluna+1]->codigo*peca<0)
                pos.tab[linha+1][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha+1][coluna-1] == NULL || pos.tab[linha+1][coluna-1]->codigo*peca<0)){//superior esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna-1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+1, coluna-1);
            if(pos.tab[linha+1][coluna-1] != NULL && pos.tab[linha+1][coluna-1]->codigo*peca<0)
                pos.tab[linha+1][coluna-1]->ataques++;
        }
    }

    if (linha>0){//linha de baixo
        if (pos.tab[linha-1][coluna] == NULL || pos.tab[linha-1][coluna]->codigo*peca<0){//mesma coluna
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-1, coluna);
            if(pos.tab[linha-1][coluna] != NULL && pos.tab[linha-1][coluna]->codigo*peca<0)
                pos.tab[linha-1][coluna]->ataques++;
        }
        if (coluna<7 && (pos.tab[linha-1][coluna+1] == NULL || pos.tab[linha-1][coluna+1]->codigo*peca<0)){//inferior direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna+1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-1, coluna+1);
            if(pos.tab[linha-1][coluna+1] != NULL && pos.tab[linha-1][coluna+1]->codigo*peca<0)
                pos.tab[linha-1][coluna+1]->ataques++;
        }
        if (coluna>0 && (pos.tab[linha-1][coluna-1] == NULL || pos.tab[linha-1][coluna-1]->codigo*peca<0)){//inferior esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna-1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-1, coluna-1);
            if(pos.tab[linha-1][coluna-1] != NULL && pos.tab[linha-1][coluna-1]->codigo*peca<0)
                pos.tab[linha-1][coluna-1]->ataques++;
        }
    }

    if (coluna<7 && (pos.tab[linha][coluna+1] == NULL || pos.tab[linha][coluna+1]->codigo*peca<0)){ //mesma linha, casa da direita
        //jogs[qtd] = CriaJogada(linha,coluna,linha,coluna+1); qtd++;
        InsereJogadaInicio(lista, linha, coluna, linha, coluna+1);
        if(pos.tab[linha][coluna+1] != NULL && pos.tab[linha][coluna+1]->codigo*peca<0)
            pos.tab[linha][coluna+1]->ataques++;
    }

    if (coluna>0 && (pos.tab[linha][coluna-1] == NULL || pos.tab[linha][coluna-1]->codigo*peca<0)){ //mesma linha, casa da esquerda
        //jogs[qtd] = CriaJogada(linha,coluna,linha,coluna-1); qtd++;
        InsereJogadaInicio(lista, linha, coluna, linha, coluna -1);
        if(pos.tab[linha][coluna-1] != NULL && pos.tab[linha][coluna-1]->codigo*peca<0)
            pos.tab[linha][coluna-1]->ataques++;
    }

}


void CalculaJogadas(struct Posicao pos,int linha, int coluna, struct Jogada *lista){

    if(pos.tab[linha][coluna] != NULL){
        int aux, peca = pos.tab[linha][coluna]->codigo;
        switch (abs(peca)){
        case PEAO:   CalculaPeao(pos,linha,coluna, lista);break;//peoes
        case CAVALO: CalculaCavalo(pos,linha,coluna, lista);break;//cavalos
        case BISPO:  CalculaBispo(pos,linha,coluna, lista);break;//bispos
        case TORRE:  CalculaTorre(pos,linha,coluna, lista);break;//torres
        case RAINHA: CalculaBispo(pos, linha, coluna, lista);
                     CalculaTorre(pos, linha, coluna, lista);
        case REI:    CalculaRei(pos,linha,coluna, lista);break;//rei
        }
    }
}
struct Jogada *CalculaJogadasPossiveis(struct Posicao pos){
    
    struct Peca *aux;
    struct Jogada *listaPossiveisJogadas = CriaListaJogadas();
    //Zerando o contador de ataques de cada pe?a.
    
    aux = pos.brancas->prox;
    
    while(aux != pos.brancas){
        aux->ataques = 0;
        aux = aux->prox;
    }

    aux = pos.pretas->prox; 
    
    while(aux != pos.pretas){
        aux->ataques = 0;
        aux = aux->prox;
    }

    
    if(pos.jogVez == 1){
        //Brancas
        aux = pos.brancas->prox;

        while(aux != pos.brancas){
            CalculaJogadas(pos, aux->linha, aux->coluna, listaPossiveisJogadas);
            aux = aux->prox;
        }
    }else{ 
        //Pretas
        aux = pos.pretas->prox;    
        while(aux != pos.pretas){
            CalculaJogadas(pos, aux->linha, aux->coluna, listaPossiveisJogadas);
            aux = aux->prox;
        }
    
    }



    return listaPossiveisJogadas;

}
//Funções de operações entre listas (lista de peças).

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
    
void RemovePeca(struct Peca *ponteiro)
{
    ponteiro->prox->ant = ponteiro->ant;
    ponteiro->ant->prox = ponteiro->prox;
    free(ponteiro);
}

struct Peca *DestruirListaPecas(struct Peca *lista)
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

void DesenhaTabuleiro(struct Posicao posAtual){
    int i,j;
    system("clear");

    printf("    +---+---+---+---+---+---+---+---+\n");
    for (i=7;i>=0;i--){
        printf("%d   |",i+1);
        for (j=0;j<8;j++){
            if(posAtual.tab[i][j] != NULL){

                AjustaCor(posAtual.tab[i][j]->codigo);
                printf(" %1d",posAtual.tab[i][j]->codigo);
            }
            else printf(" %1d",0);
            
            ResetCor();
            printf(" |");
        }
        printf("\n    +---+---+---+---+---+---+---+---+\n");
    }
    printf("      1   2   3   4   5   6   7   8 \n");
}

struct Posicao IniciaTabuleiro()
{
    int i,j;
    struct Posicao posInicial;
    posInicial.brancas = CriaLista();
    posInicial.pretas = CriaLista();    
    posInicial.qtdPretas = posInicial.qtdBrancas = 16;
    posInicial.jogVez = 1;


    for (i=0;i<8;i++){
        for (j=0;j<8;j++){
            if (i==1)
            {
                InsereInicio(posInicial.brancas, PEAO, i, j);
                posInicial.tab[i][j]= posInicial.brancas->prox;//pe?es branco
            }
            else if (i==6)
            {    
                InsereInicio(posInicial.pretas, -PEAO, i, j);
                posInicial.tab[i][j]= posInicial.pretas->prox;//pe?es preto
            }

            else posInicial.tab[i][j] = NULL;//outras casas
        }
    }

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

int qtdJogadas(struct Jogada *lista){

    int qtd = 0;
    struct Jogada *aux = lista->prox;

    while(aux != lista){
        qtd++;
        aux = aux->prox;
    }

    return qtd;

}

struct Jogada EscolheJogada(struct Jogada *lista){
    
    struct Jogada jogada, *aux = NULL ;
    
    int ver = 0;
    
    

    do{

        printf("========================================"); 
        printf("\nDigite a jogada desejada\n");
        printf("========================================\n"); 
        printf("\nLinha de onde a peça está:\n");
        scanf("%d", &jogada.deLinha);
        jogada.deLinha--;
        printf("\nColuna de onde a peça está:\n");
        scanf("%d", &jogada.deColuna);
        jogada.deColuna--;
        printf("Linha para onde a peça vai:\n");
        scanf("%d", &jogada.paraLinha);
        jogada.paraLinha--;
        printf("Coluna para onde a peça vai:\n");
        scanf("%d", &jogada.paraColuna);
        jogada.paraColuna--;
        
        aux = BuscaJogada(lista, jogada.deLinha, jogada.deColuna, jogada.paraLinha, jogada.paraColuna);
        
        if(aux == NULL)
            printf("Essa jogada não é possível!\n");
        else
            ver++;
    }while(ver == 0);

    return jogada;
}
 



int ExecutaJogada(struct Jogada jog, struct Posicao *pos){
    
    int resp = 0;
    
    struct Peca *peca = pos->tab[jog.deLinha][jog.deColuna];

    pos->tab[jog.deLinha][jog.deColuna] = NULL;

    if(pos->tab[jog.paraLinha][jog.paraColuna] != NULL){
        if(abs(pos->tab[jog.paraLinha][jog.paraColuna]->codigo) == REI)
            resp = 1;

        RemovePeca(pos->tab[jog.paraLinha][jog.paraColuna]);
        
        if(pos->jogVez == 1)
            pos->qtdPretas--;
        else
            pos->qtdBrancas--;
    }

    pos->tab[jog.paraLinha][jog.paraColuna] = peca;
    peca->linha = jog.paraLinha;
    peca->coluna = jog.paraColuna;

    pos->jogVez = -pos->jogVez;
        

    // Verificando a última linha do lado das pretas:

    for(int i = 0; i < 8; i++){
        if(pos->tab[7][i]->codigo == PEAO)
            pos->tab[7][i]->codigo = RAINHA;

        if(pos->tab[0][i]->codigo == -PEAO)
            pos->tab[7][i]->codigo = -RAINHA;
    }


    return resp;
}

struct Posicao CopiaPosicao(struct Posicao pos){
    
    struct Posicao copia;
    struct Peca *aux;
    copia.brancas = CriaLista();
    copia.pretas = CriaLista();
    
    copia.jogVez = pos.jogVez;
    copia.qtdPretas = pos.qtdPretas;
    copia.qtdBrancas = pos.qtdBrancas;
    
    // Inicializando todas as casas

    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            copia.tab[i][j] = NULL;
    


    // Colocando as peças brancas 

    aux = pos.brancas->ant; 

    while(aux != pos.brancas){
        InsereInicio(copia.brancas, aux->codigo, aux->linha, aux->coluna);
        copia.tab[aux->linha][aux->coluna] = copia.brancas->prox;
        aux = aux->ant;
    }

    // Colocando as peças pretas na lista

    aux = pos.pretas->ant;
            
    while(aux != pos.pretas){
        InsereInicio(copia.pretas, aux->codigo, aux->linha, aux->coluna);
        copia.tab[aux->linha][aux->coluna] = copia.pretas->prox;
        aux = aux->ant;
    }
    


    return copia;

}

void LiberaMemoria(struct Posicao pos){
    pos.brancas = DestruirListaPecas(pos.brancas);
    pos.pretas = DestruirListaPecas(pos.pretas);
}

double AvaliaPosicao(struct Posicao posAtual){
    
    double avaliacao = -0.5; // Colocando uma "vantagem" inicial para as brancas, porque elas que possuem o primeiro lance 

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            
            if(posAtual.tab[i][j] != NULL){
                switch(posAtual.tab[i][j]->codigo){
                    case RAINHA:
                        avaliacao += -9.0;
                        break;
                    case -RAINHA:
                        avaliacao += 9.0;
                        break;
                    case CAVALO:
                        avaliacao += -3.0;
                        break;
                    case -CAVALO:
                        avaliacao += 3.0;
                        break;
                    case BISPO:
                        avaliacao += -3.0;
                        break;
                    case -BISPO:
                        avaliacao += 3.0;
                        break;
                    case TORRE:
                        avaliacao += -5.0;
                        break;
                    case -TORRE:
                        avaliacao += 5.0;
                        break;
                    case REI:
                        avaliacao += -200.0;
                        break;
                    case -REI:
                        avaliacao += 200.0;
                        break;
                }
            }
        }
    }

    // Avaliando se há peões ou peças menores(cavalo ou bispo) no centro (casas e4, d4, e5, d5)
    
    for(int i = 3; i < 5; i++){
        for(int j = 3; j < 5; j++){

            if(posAtual.tab[i][j] != NULL){
                
                switch(posAtual.tab[i][j]->codigo){
                    
                    case PEAO:
                        avaliacao += -0.4;
                        break;
                    case -PEAO:
                        avaliacao += 0.4;
                        break;
                    case CAVALO:
                        avaliacao += -1.0 ;
                        break;
                    case -CAVALO:
                        avaliacao += 1.0;
                        break;
                    case BISPO:
                        avaliacao += -1.0;
                        break;
                    case -BISPO:
                        avaliacao += 1.0;
                        break;
                }

            }
        }



    }
    
    // Analisando quantos ataques tem uma peça (se tiver mais ela será menos valiosa)
   
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(posAtual.tab[i][j] != NULL)
                
                if(posAtual.tab[i][j]->codigo < 0){
                    avaliacao += posAtual.tab[i][j]->ataques*0.1; // Peça preta sofrendo ataque, logo chance maior para as brancas
                    if(posAtual.tab[i][j]->codigo == -REI)
                        avaliacao += posAtual.tab[i][j]->ataques*2; 
                }else{
                    avaliacao += posAtual.tab[i][j]->ataques * -(0.1); // Peça branca sofrento ataque, logo chance maior para as pretas
                    if(posAtual.tab[i][j]->codigo == REI)
                        avaliacao += posAtual.tab[i][j]->ataques*2;
                }

            
        }
    }
    
    return avaliacao;
}

int main(){
    
    struct Jogada jogada, *jogadasPossiveis; 
    
    struct Posicao posAtual;
    int vencedor = 0;
    posAtual = IniciaTabuleiro();
   
    jogadasPossiveis = CalculaJogadasPossiveis(posAtual);


      while(vencedor==0){
        
        DesenhaTabuleiro(posAtual);

        jogadasPossiveis = CalculaJogadasPossiveis(posAtual);

        printf("\n%f\n", AvaliaPosicao(posAtual));

        jogada = EscolheJogada(jogadasPossiveis);
        vencedor = ExecutaJogada(jogada,&posAtual);
        
        jogadasPossiveis = DestruirListaJogadas(jogadasPossiveis);


    }

    if (posAtual.jogVez== 1){
        printf("Brancas venceram!");
    }else printf("Pretas venceram!");

    DestruirListaPecas(posAtual.brancas);
    DestruirListaPecas(posAtual.pretas);


    
    return 0;
}
