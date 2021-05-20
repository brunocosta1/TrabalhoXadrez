#ifndef FUNCOESJOGADAS_H
#define FUNCOESJOGADAS_H

struct Jogada{
    int deLinha,deColuna,paraLinha,paraColuna;
    struct Jogada *prox, *ant;
};


struct Jogada *CriaListaJogadas();

struct Jogada *CriaJogada(int deLinha, int deColuna, int paraLinha, int paraColuna);

struct Jogada *BuscaJogada(struct Jogada *lista, int deLinha, int deColuna, int paraLinha, int paraColuna);

struct Jogada *DestruirListaJogadas(struct Jogada *lista);

void CalculaJogadas(struct Posicao pos,int linha, int coluna, struct Jogada *lista);

struct Jogada *CalculaJogadasPossiveis(struct Posicao pos);

void InsereJogadaInicio(struct Jogada *lista, int deLinha, int deColuna, int paraLinha, int paraColuna);

struct Jogada ExecutaIA(struct Posicao posAtual, int nivel, double alfa, double beta);

#endif
