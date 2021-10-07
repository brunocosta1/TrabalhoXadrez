#ifndef PECAS_H
#define PECAS_H


#include "./elements.h"

Peca *CriaLista();

Peca *CriaPeca();

void InsereInicio(Peca *lista, int codigo, int linha, int coluna);

Peca *Busca(Peca *lista, int codigo, int linha, int coluna);

void RemovePeca(Peca *ponteiro);

Peca *DestruirListaPecas(Peca *lista);

#endif
