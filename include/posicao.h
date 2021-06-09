#ifndef POSICAO_H
#define POSICAO_H

#include "./headers.h"
#include "./elements.h"

Posicao IniciaTabuleiro();

Posicao CopiaPosicao(Posicao pos);

void LiberaMemoria(Posicao pos);

double AvaliaPosicao(Posicao posAtual);



#endif
