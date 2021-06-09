#ifndef ELEMENTS_H
#define ELEMENTS_H

#define PEAO    1
#define CAVALO  2
#define BISPO   3
#define TORRE   4
#define RAINHA  5
#define REI     6
#define MAX_NIVEL 3 

typedef struct Jogada{
    int deLinha,deColuna,paraLinha,paraColuna;
    struct Jogada *prox, *ant;
}Jogada;

typedef struct Peca
{
    int codigo;
    int linha, coluna;
    int ataques;
    struct Peca *prox, *ant;
}Peca;

typedef struct Posicao
{
    int qtdBrancas;
    struct Peca *brancas;
    
    int qtdPretas;
    struct Peca *pretas;

    int jogVez;

    struct Peca *tab[8][8];
}Posicao;

#endif
