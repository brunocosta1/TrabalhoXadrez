#include "../include/pecas.h"
#include "../include/headers.h"

Peca *CriaLista(){

    Peca *sentinela = (Peca*)malloc(sizeof(Peca));
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;
    return sentinela;

}

Peca *CriaPeca(int codigo, int linha, int coluna){

    Peca *resp = (Peca*)malloc(sizeof(Peca));
    resp->codigo = codigo;
    resp->linha = linha;
    resp->coluna = coluna;

    resp->prox = NULL;
    resp->ant = NULL;

    return resp;

}

void InsereInicio(Peca *lista, int codigo, int linha, int coluna){

    Peca *novo = CriaPeca(codigo, linha, coluna);
    novo->prox = lista->prox;
    novo->ant = lista;
    lista->prox->ant = novo;
    lista->prox = novo;

}

Peca *Busca(Peca *lista, int codigo, int linha, int coluna){

    Peca *aux = lista->prox;

    while(aux != lista && aux->codigo != codigo && aux->linha != linha && aux->coluna != coluna)
        aux = aux->prox;

    if(aux != lista)
        return aux;
    else
        return NULL;
    
}

void RemovePeca(Peca *ponteiro){

    ponteiro->prox->ant = ponteiro->ant;
    ponteiro->ant->prox = ponteiro->prox;
    free(ponteiro);

}

Peca *DestruirListaPecas(Peca *lista){

    Peca *aux = lista;

    lista->ant->prox = NULL;

    while(aux != NULL){
        lista = lista->prox;
        free(aux);
        aux = lista;
    }

    return NULL;
}











