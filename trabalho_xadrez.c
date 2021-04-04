#include "stdio.h"
#include "stdlib.h"

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

//Fun��es de opera��es entre listas (lista de jogadas poss�veis).

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


struct Jogada *CalculaJogadasPossiveis(struct Posicao pos){
    
    struct Peca *aux;
    struct Jogada *listaPossiveisJogadas = CriaListaJogadas();

    //Zerando o contador de ataques de cada pe�a.
    
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
        ///Brancas
        aux = pos.brancas->prox;
        while(aux != pos.brancas){
            CalculaJogadas(pos, aux->linha, aux->coluna, listaPossiveisJogadas);    
            aux = aux->prox;
        }
    }else{
        ///Pretas
        aux = pos.pretas->prox;
        while(aux != pos.pretas){
            CalculaJogadas(pos, aux->linha, aux->coluna, listaPossiveisJogadas);
            aux = aux->prox;
        }
    }

    return listaPossiveisJogadas;

}
//Fun��es de opera��o entre listas (lista de pe�as).

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
    
void RemovePeca(struct Peca *lista, int codigo, int linha, int coluna)
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

void CalculaPeao(struct Posicao pos,int linha,int coluna, struct Jogada *lista){ 
    struct Jogada jogada;
    int qtd = 0, peca = pos.tab[linha][coluna]->codigo;

    if (linha+peca>=0 && linha+peca<=7){//n�o est� na primeira nem na �ltima linha
        if (pos.tab[linha+peca][coluna]==NULL){ //pode avancar
            //jogs[qtd] = CriaJogada(linha,coluna,linha+peca,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+peca, coluna);
        }
        if (coluna>0 && pos.tab[linha+peca][coluna-1]->codigo*peca<0){ //verificar captura na esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha+peca,coluna-1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+peca, coluna-1);
        }
        if (coluna<7 && pos.tab[linha+peca][coluna+1]->codigo*peca<0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha+peca,coluna+1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+peca, coluna+1);
            pos.tab[linha+peca][coluna+1]->ataques++;
        }
    }
}

void CalculaCavalo(struct Posicao pos, int linha, int coluna, struct Jogada *lista){
    int qtd=0,peca = pos.tab[linha][coluna]->codigo;

    if (linha<6){ //duas linhas acima
        if (coluna<7 && pos.tab[linha+2][coluna+1]->codigo*peca<=0){ //direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha+2,coluna+1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+2, coluna+1);
            if(pos.tab[linha+2][coluna+1]->codigo*peca < 0)
                pos.tab[linha+2][coluna+1]->ataques++;
        }
        if (coluna>0 && pos.tab[linha+2][coluna-1]->codigo*peca<=0){ //esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha+2,coluna-1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+2, coluna-1);
            if(pos.tab[linha+2][coluna-1]->codigo*peca < 0)
                pos.tab[linha+2][coluna-1]->ataques++;
        }
    }
    if (linha<7){//uma linha acima
        if (coluna<6 && pos.tab[linha+1][coluna+2]->codigo*peca<=0){ //duas casas � direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna+2); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+1, coluna+2);
            if(pos.tab[linha+1][coluna+2]->codigo*peca<0)
                pos.tab[linha+1][coluna+2]->ataques++;
        }
        if (coluna>1 && pos.tab[linha+1][coluna-2]->codigo*peca<=0){ //duas casas � esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna-2); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+1, coluna-2);
            if(pos.tab[linha+1][coluna-2]->codigo*peca<0)
                pos.tab[linha+1][coluna-2]->ataques++;
        }
    }
    if (linha>1){ //duas linhas abaixo
        if (coluna<7 && pos.tab[linha-2][coluna+1]->codigo*peca<=0){ //direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha-2,coluna+1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-2, coluna+1);
            if(pos.tab[linha-2][coluna+1]->codigo*peca<0)
                pos.tab[linha-2][coluna+1]->ataques++;
        }
        if (coluna>0 && pos.tab[linha-2][coluna-1]->codigo*peca<=0){ //esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha-2,coluna-1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-2, coluna-1);
            if(pos.tab[linha-2][coluna-1]->codigo*peca<0)
                pos.tab[linha-2][coluna-1]->ataques++;
        }
    }
    if (linha>0){//uma linha abaixo
        if (coluna<6 && pos.tab[linha-1][coluna+2]->codigo*peca<=0){ //duas casas � direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna+2); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-1, coluna+2);
            if(pos.tab[linha-1][coluna+2]->codigo*peca<0)
                pos.tab[linha-1][coluna+2]->ataques++;
        }
        if (coluna>1 && pos.tab[linha-1][coluna-2]->codigo*peca<=0){ //duas casas � esquerd
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna-2); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-1, coluna-2);
            if(pos.tab[linha-1][coluna-2]->codigo*peca<0)
                pos.tab[linha-1][coluna-2]->ataques++;
        }
    }
}

void CalculaBispo(struct Posicao pos, int linha, int coluna, struct Jogada *lista){ 
    int qtd = 0,peca = pos.tab[linha][coluna]->codigo;

    int k=0;

    do{//diagonal superior direita
        k++;
        if (linha+k<8 && coluna+k<8 && pos.tab[linha+k][coluna+k]->codigo*peca<=0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha+k,coluna+k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+k, coluna+k);
            if(pos.tab[linha+k][coluna+k]->codigo*peca<0)
                pos.tab[linha+k][coluna+k]->ataques++;
        }
    }while (linha+k<8 && coluna+k<8 && pos.tab[linha+k][coluna+k]==NULL);

    k=0;
    do{//diagonal superior esquerda
        k++;
        if (linha+k<8 && coluna-k>=0 && pos.tab[linha+k][coluna-k]->codigo*peca<=0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha+k,coluna-k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+k, coluna-k);
            if(pos.tab[linha+k][coluna-k]->codigo*peca<0)
                pos.tab[linha+k][coluna-k]->ataques++;
        }
    }while (linha+k<8 && coluna-k>=0 && pos.tab[linha+k][coluna-k]==NULL);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna+k<8 && pos.tab[linha-k][coluna+k]->codigo*peca<=0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha-k,coluna+k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-k, coluna+k);
            if(pos.tab[linha-k][coluna+k]->codigo*peca<0)
                pos.tab[linha-k][coluna+k]->ataques++;
        }
    }while (linha-k>=0 && coluna+k<8 && pos.tab[linha-k][coluna+k]==NULL);

    k=0;
    do{//diagonal inferior direita
        k++;
        if (linha-k>=0 && coluna-k>=0 && pos.tab[linha-k][coluna-k]->codigo*peca<=0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha-k,coluna-k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-k, coluna-k);
            if(pos.tab[linha-k][coluna-k]->codigo*peca<0)
                pos.tab[linha-k][coluna-k]->ataques++;

        }
    }while (linha-k>=0 && coluna+k>=0 && pos.tab[linha-k][coluna-k]==NULL);

}

void CalculaTorre(struct Posicao pos, int linha, int coluna, struct Jogada *lista){
    int qtd = 0, peca=pos.tab[linha][coluna]->codigo;

    int k=0;

    do{//coluna acima
        k++;
        if (linha+k<8 && pos.tab[linha+k][coluna]->codigo*peca<=0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha+k,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+k, coluna);
            if(pos.tab[linha+k][coluna]->codigo*peca<0)
                pos.tab[linha+k][coluna]->ataques++;
        }
    }while(linha+k<8 && pos.tab[linha+k][coluna]==NULL);

    k=0;
    do{//coluna abaixo
        k++;
        if (linha-k>=0 && pos.tab[linha-k][coluna]->codigo*peca<=0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha-k,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-k, coluna);
            if(pos.tab[linha-k][coluna]->codigo*peca<0)
                pos.tab[linha-k][coluna]->ataques++;
        }
    }while(linha-k>=0 && pos.tab[linha-k][coluna]==NULL);

    k=0;
    do{//linha direita
        k++;
        if (coluna+k<8 && pos.tab[linha][coluna+k]->codigo*peca<=0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha,coluna+k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha, coluna+k);
           if( pos.tab[linha][coluna+k]->codigo*peca<0)
               pos.tab[linha][coluna+k]->ataques++;
        }
    }while(coluna+k<8 && pos.tab[linha][coluna+k]==NULL);

    k=0;
    do{//linha esquerda
        k++;
        if (coluna-k>=0 && pos.tab[linha][coluna-k]->codigo*peca<=0){
            //jogs[qtd] = CriaJogada(linha,coluna,linha,coluna-k); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha, coluna-k);
            if(pos.tab[linha][coluna-k]->codigo*peca<0)
                pos.tab[linha][coluna-k]->ataques++;
        }
    }while(coluna-k>=0 && pos.tab[linha][coluna-k]==NULL);

}

void CalculaRei(struct Posicao pos, int linha, int coluna, struct Jogada *lista){
    int qtd = 0, peca=pos.tab[linha][coluna]->codigo;

    if (linha<7){//linha de cima
        if (pos.tab[linha+1][coluna]->codigo*peca<=0){//mesma coluna
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+1,coluna);
            if(pos.tab[linha+1][coluna]->codigo*peca<0)
                pos.tab[linha+1][coluna]->ataques++;
        }
        if (coluna<7 && pos.tab[linha+1][coluna+1]->codigo*peca<=0){//superior direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna+1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+1, coluna+1);
            if(pos.tab[linha+1][coluna+1]->codigo*peca<0)
                pos.tab[linha+1][coluna+1]->ataques++;
        }
        if (coluna>=0 && pos.tab[linha+1][coluna-1]->codigo*peca<=0){//superior esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha+1,coluna-1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha+1, coluna-1);
            if(pos.tab[linha+1][coluna-1]->codigo*peca<0)
                pos.tab[linha+1][coluna-1]->ataques++;
        }
    }

    if (linha>0){//linha de baixo
        if (pos.tab[linha-1][coluna]->codigo*peca<=0){//mesma coluna
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-1, coluna);
            if(pos.tab[linha-1][coluna]->codigo*peca<0)
                pos.tab[linha-1][coluna]->ataques++;
        }
        if (coluna<7 && pos.tab[linha-1][coluna+1]->codigo*peca<=0){//inferior direita
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna+1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-1, coluna+1);
            if(pos.tab[linha-1][coluna+1]->codigo*peca<0)
                pos.tab[linha-1][coluna+1]->ataques++;
        }
        if (coluna>=0 && pos.tab[linha-1][coluna-1]->codigo*peca<=0){//inferior esquerda
            //jogs[qtd] = CriaJogada(linha,coluna,linha-1,coluna-1); qtd++;
            InsereJogadaInicio(lista, linha, coluna, linha-1, coluna-1);
            if(pos.tab[linha-1][coluna-1]->codigo*peca<0)
                pos.tab[linha-1][coluna-1]->ataques++;
        }
    }

    if (coluna<7 && pos.tab[linha][coluna+1]->codigo*peca<=0){ //mesma linha, casa da direita
        //jogs[qtd] = CriaJogada(linha,coluna,linha,coluna+1); qtd++;
        InsereJogadaInicio(lista, linha, coluna, linha, coluna+1);
        if(pos.tab[linha][coluna+1]->codigo*peca<0)
            pos.tab[linha][coluna+1]->ataques++;
    }

    if (coluna>0 && pos.tab[linha][coluna-1]->codigo*peca<=0){ //mesma linha, casa da esquerda
        //jogs[qtd] = CriaJogada(linha,coluna,linha,coluna-1); qtd++;
        InsereJogadaInicio(lista, linha, coluna, linha, coluna -1);
        if(pos.tab[linha][coluna-1]->codigo*peca<0)
            pos.tab[linha][coluna-1]->ataques++;
    }

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
                posInicial.tab[i][j]= posInicial.brancas->prox;//pe�es branco
            }
            else if (i==6)
            {    
                InsereInicio(posInicial.pretas, -PEAO, i, j);
                posInicial.tab[i][j]= posInicial.pretas->prox;//pe�es preto
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

void EscolhePeca(struct Posicao pos ,int *linha, int *coluna){
    do{
        printf("Digite a linha e a coluna da peca a ser movida:");
        scanf("%d %d",linha,coluna); //l� valores de 1 a 8
        (*linha)--; //converte para valores de 0 a 7
        (*coluna)--;
        if (pos.tab[*linha][*coluna]==NULL){
            printf("Nao tem peca nessa casa!!!\n");
        }
    }while (pos.tab[*linha][*coluna]==NULL);
}

void CalculaJogadas(struct Posicao pos,int linha, int coluna, struct Jogada *lista){
    int aux, peca = pos.tab[linha][coluna]->codigo;
    switch (abs(peca)){
    case PEAO:   CalculaPeao(pos,linha,coluna,lista);break;//peoes
    case CAVALO: CalculaCavalo(pos,linha,coluna,lista);break;//cavalos
    case BISPO:  CalculaBispo(pos,linha,coluna,lista);break;//bispos
    case TORRE:  CalculaTorre(pos,linha,coluna,lista);break;//torres
    case RAINHA: CalculaBispo(pos,linha,coluna,lista);
                 CalculaTorre(pos,linha,coluna,lista);
                 break;
    case REI:    CalculaRei(pos,linha,coluna,lista);break;//rei
    }
}

struct Jogada EscolheJogada(struct Jogada *listaJogadas){
    int i = 0,j=0,op, qtd;
    qtd = qtdJogadas(listaJogadas);
    
    /*do{
        for (i=0;i<qtd;i++){
            printf("Jogada %2d: mover para linha %d coluna %d |",i+1,jogs[i].paraLinha+1,jogs[i].paraColuna+1);
            if ( (i+1) % 3 == 0)
                printf("\n");
        }
        printf("\nJogada:");
        scanf("%d",&op);
    }while (op<1 || op>qtd);*/
    
    struct Jogada *aux = listaJogadas->prox;
    do{ 
        while(aux != listaJogadas){
            printf("Jogada %2d: mover para linha %d coluna %d |", i+1, aux->paraLinha+1, aux->paraColuna+1);   
            if((i+1) % 3 == 0)
                printf("\n");
            
            i++;
            aux = aux->prox;
        }
        printf("\nJogada:");
        scanf("%d", &op);
    }while(op<1 || op>qtd);    

    aux = listaJogadas->prox;

    do{
        if(j == op)
            return *aux;
        
        aux = aux->prox;
        j++;
    }while(j != op);


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

int ExecutaJogada(struct Posicao *pos, struct Jogada jog){
    int resp=0; 
    struct Peca *peca = pos->tab[jog.deLinha][jog.deColuna];

    //tab[jog.deLinha][jog.deColuna] = 0; //tira a pe�a

    if(pos->tab[jog.deLinha][jog.deColuna]->codigo * peca->codigo = 0){ //movimenta��o
        pos->tab[jog.paraLinha][jog.paraColuna] = peca; 
        peca->linha = jog.paraLinha;
        peca->coluna = jog.paraColuna;
        pos->tab[jog.deLinha][jog.paraColuna] = NULL;
        
        return 0;
    }   

    if(pos->tab[jog.deLinha][jog.deColuna]->codigo * peca->codigo < 0){ //captura
        
        if(pos->jogVez == 1){
            if(pos->tab[jog.paraLinha][jog.paraColuna]->codigo == -REI){
                RemovePeca(pos->qtdPretas, peca->codigo, peca->linha, peca->coluna);
                pos->qtdPretas--;
                pos->tab[jog.paraLinha][jog.paraColuna] = peca;
                peca->linha = jog.paraLinha;
                peca->coluna = jog.paraColuna;
                pos->tab[jog.deLinha][jog.deColuna] = NULL;
                
                return 1;
            }else{
                RemovePeca(pos->qtdPretas, peca->codigo, peca->linha, peca->coluna);
                pos->qtdPretas--;
                pos->tab[jog.paraLinha][jog.paraColuna] = peca;
                peca->linha = jog.paraLinha;
                peca->coluna = jog.paraColuna;
                pos->tab[jog.deLinha][jog.deColuna] = NULL;
                return 0;
            }
        } 

        if(pos->jogVez == -1){
            if(pos->tab[jog.paraLinha][jog.paraColuna]->codigo == REI){
                RemovePeca(pos->qtdBrancas, peca->codigo, peca->linha, peca->coluna);
                pos->qtdBrancas--;
                pos->tab[jog.paraLinha][jog.paraColuna] = peca;
                peca->linha = jog.paraLinha;
                peca->coluna = jog.paraColuna;
                pos->tab[jog.deLinha][jog.deColuna] = NULL;

                return 1;
            }else{
                RemovePeca(pos->qtdPretas, peca->codigo, peca->linha, peca->coluna);
                pos->qtdPretas--;
                pos->tab[jog.paraLinha][jog.paraColuna] = peca;
                peca->linha = jog.paraLinha;
                peca->coluna = jog.paraColuna;
                pos->tab[jog.deLinha][jog.deColuna] = NULL;
                return 0;
            }
        }
    
    }
    //if (abs(tab[jog.paraLinha][jog.paraColuna])==REI) //verifica se o rei advers�rio ser� capturado
    //    resp = peca; //resp indica quem ser� vencedor

    //tab[jog.paraLinha][jog.paraColuna] = peca; //coloca a pe�a na nova posi��o

    //return resp;
}

int main(){
    int tab[8][8];
    int vencedor=0,linha,coluna,escolha;
    int qtdJogadas;
    struct Jogada *jogadasPossiveis = CriaListaJogadas();
    struct Jogada jogada;
    struct Posicao posAtual;
    posAtual = IniciaTabuleiro();

    while (vencedor==0){
        DesenhaTabuleiro(posAtual);
        EscolhePeca(posAtual,&linha,&coluna);
        jogadasPossiveis = CalculaJogadasPossiveis(posAtual);

        jogada = EscolheJogada(jogadasPossiveis);
        vencedor = ExecutaJogada(&posAtual,jogada);
    }
    if (vencedor>0){
        printf("Brancas venceram!");
    }else printf("Pretas venceram!");


    return 0;
}
