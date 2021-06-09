#include "../include/jogadas.h"

Jogada *CriaListaJogadas()
{
    Jogada *sentinela = (Jogada*)malloc(sizeof(Jogada));
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;
    return sentinela;
}

Jogada *CriaJogada(int deLinha, int deColuna, int paraLinha, int paraColuna){

    Jogada *resp = (Jogada*)malloc(sizeof(Jogada));
    resp->deLinha = deLinha;
    resp->deColuna = deColuna;
    resp->paraLinha = paraLinha;
    resp->paraColuna = paraColuna;

    resp->prox = NULL;
    resp->ant = NULL;
    
    return resp;

}

void InsereJogadaInicio(Jogada *lista, int deLinha, int deColuna, int paraLinha, int paraColuna){
    
    Jogada *novo = CriaJogada(deLinha, deColuna, paraLinha, paraColuna);
    novo->prox = lista->prox;
    novo->ant = lista;
    lista->prox->ant = novo;
    lista->prox = novo;
    
}

Jogada *BuscaJogada(Jogada *lista, int deLinha, int deColuna, int paraLinha, int paraColuna){
   
    Jogada *aux = lista->prox;

    while(aux != lista && !(aux->deLinha == deLinha && aux->deColuna == deColuna && aux->paraLinha == paraLinha && aux->paraColuna == paraColuna))
        aux = aux->prox;

    if(aux != lista)
        return aux;
    else
        return NULL;
}


Jogada *DestruirListaJogadas(Jogada *lista){
    Jogada *aux = lista;
    lista->ant->prox = NULL;
    while(aux != NULL)
    {
        lista = lista->prox;
        free(aux);
        aux = lista;
    }

    return NULL;
}



void CalculaPeao(Posicao pos,int linha,int coluna, struct Jogada *lista){ 
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


void CalculaCavalo(Posicao pos, int linha, int coluna, Jogada *lista){
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


void CalculaBispo(Posicao pos, int linha, int coluna, Jogada *lista){ 
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

void CalculaTorre(Posicao pos, int linha, int coluna, Jogada *lista){
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

void CalculaRei(Posicao pos, int linha, int coluna, Jogada *lista){
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

void CalculaJogadas(Posicao pos,int linha, int coluna, Jogada *lista){

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


Jogada *CalculaJogadasPossiveis(Posicao pos){
    
    Peca *aux;
    Jogada *listaPossiveisJogadas = CriaListaJogadas();
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

int qtdJogadas(Jogada *lista){

    int qtd = 0;
    Jogada *aux = lista->prox;

    while(aux != lista){
        qtd++;
        aux = aux->prox;
    }

    return qtd;

}

Jogada EscolheJogada(Jogada *lista){
    
    Jogada jogada, *aux = NULL ;
    
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

int ExecutaJogada(Jogada jog, Posicao *pos){
    
    int resp = 0;
    
    Peca *peca = pos->tab[jog.deLinha][jog.deColuna];

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
        if(pos->tab[7][i] != NULL){
            if(pos->tab[7][i]->codigo == PEAO)
                pos->tab[7][i]->codigo = RAINHA;
        }
        if(pos->tab[0][i] != NULL){
            if(pos->tab[0][i]->codigo == -PEAO)
                pos->tab[0][i]->codigo = -RAINHA;
        }
    }


    return resp;
}

Jogada ExecutaIA(Posicao posAtual, int nivel, double alfa, double beta){
    Jogada melhorJogada, jogadaIA;
    double melhorValor = 0.0 , valorJogada = 0.0;
    Jogada *lista, *listaPretas, *listaBrancas, *jogadaAux;
    Posicao posCopia;
    
    int k, ptr = 0;

    if(nivel % 2 == 0)
        melhorValor = -INFINITY;
    else
        melhorValor = INFINITY;

    int podado = 0;


    if(posAtual.jogVez == -1){
        listaPretas = CalculaJogadasPossiveis(posAtual);
        posAtual.jogVez = 1;
        listaBrancas = CalculaJogadasPossiveis(posAtual);
        posAtual.jogVez = -1;
    }else{
        listaBrancas = CalculaJogadasPossiveis(posAtual);
        posAtual.jogVez = -1;
        listaPretas = CalculaJogadasPossiveis(posAtual);
        posAtual.jogVez = 1;
    }

    if(nivel % 2 == 0){
        lista = listaPretas;
    }else{
        lista = listaBrancas;
    }

    jogadaAux = lista->prox;

    while(jogadaAux != lista && podado == 0){
        posCopia = CopiaPosicao(posAtual);  
        k = ExecutaJogada(*jogadaAux, &posCopia);
        ptr = 0;

        if(nivel < MAX_NIVEL){
            
            if(nivel % 2 == 0){
                jogadaIA = ExecutaIA(posCopia, nivel+1, melhorValor, beta);
                ptr++;
            }else{
                jogadaIA = ExecutaIA(posCopia, nivel+1, alfa, melhorValor);
                ptr++;
            }

            if(ptr != 0)
                k = ExecutaJogada(jogadaIA, &posCopia);
        }   

        valorJogada = AvaliaPosicao(posCopia);

        if(valorJogada < alfa || valorJogada > beta)
            podado = 1;
            
        if(nivel % 2 == 0 && valorJogada >= melhorValor){
            melhorValor = valorJogada;
            melhorJogada = *jogadaAux;
        }else if(nivel % 2 != 0 && valorJogada <= melhorValor){
            melhorValor = valorJogada;
            melhorJogada = *jogadaAux;
        }

        LiberaMemoria(posCopia);

        jogadaAux = jogadaAux->prox;
    }

    DestruirListaJogadas(listaPretas);
    DestruirListaJogadas(listaBrancas);


    return melhorJogada;
}





