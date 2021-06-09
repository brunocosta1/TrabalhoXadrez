#ifndef JOGADAS_H
#define JOGADAS_H

#include "./headers.h"
#include "./elements.h"

Jogada *CriaListaJogadas();

Jogada *CriaJogada(int deLinha, int deColuna, int paraLinha, int paraColuna);

void InsereJogadaInicio(Jogada *lista, int deLinha, int deColuna, int paraLinha, int paraColuna);

Jogada *BuscaJogada(Jogada *lista, int deLinha, int deColuna, int paraLinha, int paraColuna);

Jogada *DestruirListaJogadas(Jogada *lista);

void CalculaPeao(Posicao pos, int linha, int coluna, Jogada *lista);

void CalculaBispo(Posicao pos, int linha, int coluna, Jogada *lista);

void CalculaCavalo(Posicao pos, int linha, int coluna, Jogada *lista);

void CalculaTorre(Posicao pos, int linha, int coluna, Jogada *lista);

void CalculaRei(Posicao pos, int linha, int coluna, Jogada *lista);

void CalculaJogadas(Posicao pos, int linha, int coluna, Jogada *lista);

Jogada *CalculaJogadasPossiveis(Posicao pos);

int qtdJogadas(Jogada *lista);

Jogada EscolheJogada(Jogada *lista);

int ExecutaJogada(Jogada jog, Posicao *pos);

Jogada ExecutaIA(Posicao posAtual, int nivel, double alfa, double beta);

#endif
