#include "aeroporto.h"

aeroporto_t* iniciar_aeroporto(size_t* args, size_t n_args) {
    aeroporto_t* aeroporto = malloc(sizeof(aeroporto_t));
    aeroporto->n_pistas = args[0];
    aeroporto->n_portoes = args[1];
    aeroporto->n_esteiras = args[2];
    aeroporto->n_max_avioes_esteira = args[3];
    aeroporto->t_pouso_decolagem = args[4];
    aeroporto->t_remover_bagagens = args[5];
    aeroporto->t_inserir_bagagens = args[6];
    aeroporto->t_bagagens_esteira = args[7];

    aeroporto->esteiras = malloc(sizeof(aeroporto->esteiras));

    aeroporto->fila_pouso = criar_fila();
    sem_init(&aeroporto->pistas, 0, aeroporto->n_pistas);
    sem_init(&aeroporto->portoes, 0, aeroporto->n_portoes);
    for (size_t i = 0; i < aeroporto->n_esteiras; i++) {
        sem_init(&aeroporto->esteiras[i], 0, aeroporto->n_max_avioes_esteira);
    }

    return aeroporto;
}

int finalizar_aeroporto(aeroporto_t* aeroporto) {
    free(aeroporto);
    return 1;
}

void aproximacao_aeroporto(aeroporto_t* aeroporto, aviao_t* aviao) {
    printf(" - Aviao %lu entrou na fila na posição %lu com [%lu] Fuel.\n",
           aviao->id, aeroporto->fila_pouso->n_elementos, aviao->combustivel);
    inserir(aeroporto->fila_pouso, aviao);
}

void pousar_aviao(aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(&aeroporto->pistas);
    printf("-> Aviao %lu pousou.\n", aviao->id);
    remover(aeroporto->fila_pouso);
    usleep(aeroporto->t_pouso_decolagem * 1000);
    sem_post(&aeroporto->pistas);
}

void acoplar_portao(aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(&aeroporto->portoes);
    int portao = 0;
    sem_getvalue(&aeroporto->portoes, &portao);
    printf("=> Aviao %lu acoplou portão %u.\n", aviao->id, portao);
}

void transportar_bagagens(aeroporto_t* aeroporto, aviao_t* aviao) {
    size_t i = 0;

    while(1) {
        sem_t sem = aeroporto->esteiras[i];
        int tmp = 0;
        sem_getvalue(&sem, &tmp);
        if (tmp) {
            sem_wait(&sem);
            printf("-( Aviao %lu pegou esteira #%d.\n", aviao->id, tmp);
            adicionar_bagagens_esteira(aeroporto, aviao);
            sem_post(&sem);
            break;
        }

        ++i;
        if (i == aeroporto->n_esteiras) {
            i = 0;
        }
    }

    sem_post(&aeroporto->portoes);
}

void adicionar_bagagens_esteira(aeroporto_t* aeroporto, aviao_t* aviao) {
    printf(" ( Aviao %lu inserindo bagagens.\n", aviao->id);
    usleep(aeroporto->t_inserir_bagagens * 1000);
    usleep(aeroporto->t_bagagens_esteira * 1000);
    printf(" ) Aviao %lu removendo bagagens.\n", aviao->id);
    usleep(aeroporto->t_remover_bagagens * 1000);
}

void decolar_aviao(aeroporto_t* aeroporto, aviao_t* aviao) {
    sem_wait(&aeroporto->pistas);
    printf(" <-Aviao %lu decolando.\n", aviao->id);
    usleep(aeroporto->t_pouso_decolagem * 1000);
    free(aviao);
    sem_post(&aeroporto->pistas);
}
