#include "../include/headers.h"

Posicao IniciaTabuleiro()
{
    int i,j;
    Posicao posInicial;
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

Posicao CopiaPosicao(Posicao pos){
    
    Posicao copia;
    Peca *aux;
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

void LiberaMemoria(Posicao pos){
    pos.brancas = DestruirListaPecas(pos.brancas);
    pos.pretas = DestruirListaPecas(pos.pretas);
}

double AvaliaPosicao(Posicao posAtual){
    
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
            if(posAtual.tab[i][j] != NULL){
                
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
    }    

    return avaliacao;
}
