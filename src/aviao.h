#pragma once

#include "stdafx.h"

typedef struct {
    pthread_t thread;
    size_t combustivel;
    size_t id;
} aviao_t;

aviao_t* aloca_aviao(size_t combustivel, size_t id);
void desaloca_aviao(aviao_t* aviao);
