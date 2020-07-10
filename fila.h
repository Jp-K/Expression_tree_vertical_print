#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
#include <iostream>
using namespace std;
template <typename TIPO>
struct TElementoF {
TIPO dado;
TElementoF<TIPO> * proximo;
};

template <typename TIPO>
struct TFilaF {
TElementoF<TIPO> * primeiro;
int qtd;
};

template <typename TIPO>
bool inicializa_fila (TFilaF<TIPO> &fila){
   fila.primeiro = NULL;
   fila.qtd = 0;
   return true;
}

template <typename TIPO>
int fila_qtd (TFilaF<TIPO> &fila){
    return fila.qtd;
}

template <typename TIPO>
TIPO fila_prox(TFilaF<TIPO> &fila){
    return fila.primeiro->dado;
}


template <typename TIPO>
bool fila_queue (TFilaF<TIPO> &fila, TIPO dado){
    TElementoF <TIPO> * nav = fila.primeiro;
    if(fila.primeiro != NULL)
    {
        while (nav->proximo != NULL){
            nav = nav->proximo;
        }
        TElementoF<TIPO> * novo = new TElementoF<TIPO>;
        novo->dado = dado;
        novo->proximo = NULL;
        nav->proximo = novo;
        fila.qtd = fila.qtd + 1;
        return true;
    }
    else {
        TElementoF<TIPO> * novo = new TElementoF<TIPO>;
        novo->dado = dado;
        novo->proximo = NULL;
        fila.primeiro = novo;
        fila.qtd = fila.qtd + 1;
        return true;
    }
}

    template <typename TIPO>
TIPO fila_unqueue (TFilaF<TIPO> &fila){
    TIPO dado;

    if (fila.primeiro != NULL)
    {
        TElementoF<TIPO> * deletado = fila.primeiro;
        fila.primeiro=deletado->proximo;
        dado = deletado->dado;
        delete deletado;
        fila.qtd = fila.qtd - 1;
        return dado;
    }
}


#endif // FILA_H_INCLUDED
