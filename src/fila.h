#pragma once

#include "stdafx.h"
#include "aviao.h"

typedef struct elemento_t {
    struct elemento_t* anterior;
    struct elemento_t* proximo;
    aviao_t* dado;
} elemento_t;

typedef struct {
    elemento_t* primeiro;
    elemento_t* ultimo;
    size_t n_elementos;
} fila_ordenada_t;

fila_ordenada_t* criar_fila();
void desaloca_fila(fila_ordenada_t* fila);
elemento_t* aloca_elemento(aviao_t* dado);
void desaloca_elemento(elemento_t* elemento);
void inserir(fila_ordenada_t* fila, aviao_t* dado);
aviao_t* remover(fila_ordenada_t* fila);
