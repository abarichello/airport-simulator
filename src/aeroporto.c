#include "aeroporto.h"

aeroporto_t* iniciar_aeroporto (size_t* args, size_t n_args) {
    aeroporto_t* aeroporto = malloc(sizeof(aeroporto_t));
    aeroporto->n_pistas = args[0];
    aeroporto->n_portoes = args[1];
    aeroporto->n_esteiras = args[2];
    aeroporto->n_max_avioes_esteira = args[3];
    aeroporto->t_pouso_decolagem = args[4];
    aeroporto->t_remover_bagagens = args[5];
    aeroporto->t_inserir_bagagens = args[6];
    aeroporto->t_bagagens_esteira = args[7];

    aeroporto->fila_pouso = criar_fila();
    sem_init(&aeroporto->pistas, 0, aeroporto->n_pistas);
    sem_init(&aeroporto->portoes, 0, aeroporto->n_portoes);

    return aeroporto;
}

int finalizar_aeroporto (aeroporto_t* aeroporto) {
    free(aeroporto);
    return 1;
}

void aproximacao_aeroporto (aeroporto_t* aeroporto, aviao_t* aviao) {
    inserir(aeroporto->fila_pouso, aviao);
}

void pousar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(&aeroporto->pistas);
    aviao_t* pouso = remover(aeroporto->fila_pouso);
    sleep(aeroporto->t_pouso_decolagem);
    sem_post(&aeroporto->pistas);
}

void acoplar_portao (aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(&aeroporto->portoes);
    sem_post(&aeroporto->portoes);
}

void transportar_bagagens (aeroporto_t* aeroporto, aviao_t* aviao) {

}

void adicionar_bagagens_esteira (aeroporto_t* aeroporto, aviao_t* aviao) {

}

void decolar_aviao (aeroporto_t* aeroporto, aviao_t* aviao) {

}
