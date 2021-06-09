#include "../include/setup.h"

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

void DesenhaTabuleiro(Posicao posAtual){
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

void IniciaJogo(){

    Jogada jogada, *jogadasPossiveis = NULL; 
    
    Posicao posAtual;
    int vencedor = 0;
    posAtual = IniciaTabuleiro();
   
    jogadasPossiveis = CalculaJogadasPossiveis(posAtual);

    /*FILE *arq;*/
    
    /*arq = fopen("jogadas.bin", "wb");*/
    /*fclose(arq);*/



    while(vencedor==0){
        
        DesenhaTabuleiro(posAtual);
        
        if(posAtual.jogVez == 1){
            jogadasPossiveis = CalculaJogadasPossiveis(posAtual);
            jogada = EscolheJogada(jogadasPossiveis);
            jogadasPossiveis = DestruirListaJogadas(jogadasPossiveis);
        }else{
            jogada = ExecutaIA(posAtual, 0, -INFINITY, INFINITY);
        }
        
        /*SalvaJogada("jogadas.bin", &jogada);*/

        vencedor = ExecutaJogada(jogada,&posAtual);
    }

    if (posAtual.jogVez== -1){
        printf("Brancas venceram!");
    }else printf("Pretas venceram!");

    DestruirListaPecas(posAtual.brancas);
    DestruirListaPecas(posAtual.pretas);


}
