#include <stdio.h>
#include "aviao.h"
#include "fila.h"

void main() {
    fila_ordenada_t* fila = criar_fila();
    aviao_t* aviao0 = aloca_aviao(100, 0);
    aviao_t* aviao1 = aloca_aviao(50, 1);

    inserir(fila, aviao0);
    inserir(fila, aviao1);
    printf("Primeiro: %d\nUltimo: %d\n", fila->primeiro->dado->id, fila->ultimo->dado->id);
}
