#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED
#include <iostream>
template<typename TIPO>
struct TElementoP
{
    TIPO dado;
    TElementoP<TIPO> *proximo;
};

template<typename TIPO>
struct TPilha
{
    TElementoP<TIPO> * inicio;
    int qntd;
};

template<typename TIPO>
void inicializa_pilha(TPilha<TIPO> &lista)
{
    lista.inicio = NULL;
    lista.qntd = 0;
}

template <typename TIPO>
bool push_pilha(TPilha<TIPO> &lista, TIPO dado){
  TElementoP<TIPO> *novo = new TElementoP<TIPO>;
  novo->dado = dado;
  novo->proximo = lista.inicio;
  lista.inicio = novo;
  lista.qntd++;
  return true;
}

template <typename TIPO>
TIPO pop_pilha(TPilha<TIPO> &lista){
    TIPO dado;
if (lista.inicio != NULL){
    TElementoP<TIPO> * deletado = lista.inicio;
    lista.inicio=deletado->proximo;
    dado = deletado->dado;
    delete deletado;
    lista.qntd--;
    return dado;
}
}

template <typename TIPO>
int qntd_pilha(TPilha<TIPO> &lista){
    return lista.qntd;
}

template <typename TIPO>
TIPO Top_pilha(TPilha<TIPO> &lista){
    TIPO item;
    if (lista.inicio != NULL){
        item = lista.inicio->dado;
        return item;
    }
}


#endif // PILHA_H_INCLUDED
