#include "fila.h"

elemento_t* aloca_elemento(aviao_t* dado) {
    elemento_t* el = malloc(sizeof(elemento_t));
    el->dado = dado;
    return el;
}

void desaloca_elemento(elemento_t* elemento) {
    free(elemento);
}

fila_ordenada_t* criar_fila() {
    fila_ordenada_t* fila = (fila_ordenada_t*)malloc(sizeof(fila_ordenada_t));
    fila->n_elementos = 0;
    return fila;
}

void desaloca_fila(fila_ordenada_t* fila) {
    elemento_t* el = fila->primeiro;

    for (size_t i = 0; i < fila->n_elementos; i++) {
        elemento_t* prox = el->proximo;
        free(el);
        el = prox;
    }

    free(fila);
}

void inserir(fila_ordenada_t* fila, aviao_t* dado) {
    elemento_t* el = aloca_elemento(dado);

    if (fila->n_elementos == 0) {
        fila->primeiro = el;
        fila->ultimo = el;
    } else {
        elemento_t* ultimo = fila->ultimo;
        ultimo->proximo = el;
        fila->ultimo = el;
    }
    fila->n_elementos++;
}

aviao_t* remover(fila_ordenada_t* fila) {
    elemento_t* el = fila->primeiro;
    aviao_t* aviao = el->dado;
    fila->primeiro = el->proximo;
    free(el);
    return aviao;
}
