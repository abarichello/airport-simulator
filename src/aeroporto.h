#pragma once

#include "stdafx.h"
#include "aviao.h"
#include "fila.h"

typedef size_t tempo_t;
typedef struct {
    size_t n_pistas;
    size_t n_portoes;
    size_t n_esteiras;
    size_t n_max_avioes_esteira;
    tempo_t t_pouso_decolagem;
    tempo_t t_remover_bagagens;
    tempo_t t_inserir_bagagens;
    tempo_t t_bagagens_esteira;
    fila_ordenada_t* fila_pouso;
    sem_t pistas;
    sem_t portoes;
    sem_t* esteiras;
} aeroporto_t;

aeroporto_t* iniciar_aeroporto(size_t* args, size_t n_args);
int finalizar_aeroporto(aeroporto_t* aeroporto);

void aproximacao_aeroporto(aeroporto_t* aeroporto, aviao_t* aviao);
void pousar_aviao(aeroporto_t* aeroporto, aviao_t* aviao);
void acoplar_portao(aeroporto_t* aeroporto, aviao_t* aviao);
void transportar_bagagens(aeroporto_t* aeroporto, aviao_t* aviao);
void adicionar_bagagens_esteira(aeroporto_t* aeroporto, aviao_t* aviao);
void decolar_aviao(aeroporto_t* aeroporto, aviao_t* aviao);
