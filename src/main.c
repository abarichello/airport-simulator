#include "stdafx.h"
#include "aeroporto.h"
#include "fila.h"

#define NOVO_AVIAO_MIN 30
#define NOVO_AVIAO_MAX 120
#define COMBUSTIVEL_MIN 1
#define COMBUSTIVEL_MAX 100
#define TEMPO_POUSO_DECOLAGEM 40
#define TEMPO_REMOVER_BAGAGENS 90
#define TEMPO_INSERIR_BAGAGENS 110
#define TEMPO_BAGAGENS_ESTEIRA 200
#define TEMPO_SIMULACAO 10000

typedef struct {
    aeroporto_t* aeroporto;
    aviao_t* aviao;
} unidade_t;

void* thread_aviao(void* arg) {
    unidade_t* unidade = (unidade_t*)arg;
    aproximacao_aeroporto(unidade->aeroporto, unidade->aviao);
    pousar_aviao(unidade->aeroporto, unidade->aviao);
    acoplar_portao(unidade->aeroporto, unidade->aviao);
    transportar_bagagens(unidade->aeroporto, unidade->aviao);
    adicionar_bagagens_esteira(unidade->aeroporto, unidade->aviao);
    decolar_aviao(unidade->aeroporto, unidade->aviao);
    return 0;
}

long long current_timestamp() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long long milliseconds = tv.tv_sec * 1000LL + tv.tv_usec / 1000LL;
    return milliseconds;
}

int main(int argc, char** argv) {
    srand(time(NULL));

    size_t t_novo_aviao_min, t_novo_aviao_max;
    size_t t_pouso_decolagem;
    size_t t_remover_bagagens, t_inserir_bagagens;
    size_t t_bagagens_esteira, t_simulacao;

    size_t n_pistas, n_portoes;
    size_t n_max_avioes_esteira, n_esteiras;
    size_t n_args;

    size_t p_combustivel_min, p_combustivel_max;

    if (argc == 5) {
        t_novo_aviao_min = NOVO_AVIAO_MIN;
        t_novo_aviao_max = NOVO_AVIAO_MAX;
        t_pouso_decolagem = TEMPO_POUSO_DECOLAGEM;
        t_remover_bagagens = TEMPO_REMOVER_BAGAGENS;
        t_inserir_bagagens = TEMPO_INSERIR_BAGAGENS;
        t_bagagens_esteira = TEMPO_BAGAGENS_ESTEIRA;
        t_simulacao = TEMPO_SIMULACAO;
        p_combustivel_min = COMBUSTIVEL_MIN;
        p_combustivel_max = COMBUSTIVEL_MAX;
        n_pistas = atoi(argv[1]);
        n_portoes = atoi(argv[2]);
        n_max_avioes_esteira = atoi(argv[3]);
        n_esteiras = atoi(argv[4]);
    } else if (argc == 14) {
        int i = 0;
        t_novo_aviao_min = atoi(argv[++i]);
        t_novo_aviao_max = atoi(argv[++i]);
        p_combustivel_min = atoi(argv[++i]);
        p_combustivel_max = atoi(argv[++i]);
        t_pouso_decolagem = atoi(argv[++i]);
        n_pistas = atoi(argv[++i]);
        t_remover_bagagens = atoi(argv[++i]);
        t_inserir_bagagens = atoi(argv[++i]);
        n_portoes = atoi(argv[++i]);
        n_max_avioes_esteira = atoi(argv[++i]);
        t_bagagens_esteira = atoi(argv[++i]);
        n_esteiras = atoi(argv[++i]);
        t_simulacao = atoi(argv[++i]);

    } else {
        printf("Todas as entradas são inteiros positivos!!\nUso:\n");
        printf("./aeroporto  NOVO_AVIAO_MIN  NOVO_AVIAO_MAX\n");
        printf("COMBUSTIVEL_MIN COMBUSTIVEL_MAX\n");
        printf("TEMPO_POUSO_DECOLAGEM  NUMERO_PISTAS  TEMPO_REMOVER_BAGAGENS\n");
        printf("TEMPO_INSERIR_BAGAGENS  NUMERO_PORTOES  MAXIMO_AVIOES_ESTEIRA\n");
        printf("TEMPO_BAGAGENS_ESTEIRA  NUMERO_ESTEIRAS  TEMPO_SIMULACAO\n");
        printf("----------OU----------\n");
        printf("./airport  NUMERO_PISTAS  NUMERO_PORTOES  MAXIMO_AVIOES_ESTEIRA  NUMERO_ESTEIRAS\n");
        return 0;
    }

    printf("Simulação iniciada com tempo total: %lu\n", t_simulacao);
    printf("Tempo para criação de aviões: %lu - %lu\n", t_novo_aviao_min, t_novo_aviao_max);
    printf("Número de pistas de pouso: %lu\n", n_pistas);
    printf("Tempo de pouso e decolagem: %lu\n", t_pouso_decolagem);
    printf("Número de portões de embarque: %lu\n", n_portoes);
    printf("Tempo de inserção (%lu) e remoção (%lu) de bagagens\n", t_inserir_bagagens, t_remover_bagagens);
    printf("Número de esteiras: %lu, com %lu aviões por esteira\n", n_esteiras, n_max_avioes_esteira);
    printf("Tempo das bagagens nas esteiras: %lu\n\n", t_bagagens_esteira);

    n_args = 8;
    size_t args[8] = {n_pistas, n_portoes, n_esteiras,
                      n_max_avioes_esteira,
                      t_pouso_decolagem, t_remover_bagagens,
                      t_inserir_bagagens, t_bagagens_esteira};

    aeroporto_t* meu_aeroporto = iniciar_aeroporto(args, n_args);
    pthread_t thread_vector[100];

    long long tempo_inicial, tempo_final, tempo_total;
    tempo_t proximo_aviao = rand() % t_novo_aviao_max + t_novo_aviao_min;

    int id = 0;
    tempo_inicial = current_timestamp();

    do {
        if (tempo_total >= proximo_aviao) {
            int rnd = rand() % p_combustivel_max + p_combustivel_min;
            aviao_t* aviao = aloca_aviao(rnd, id);
            unidade_t* unidade = malloc(sizeof(unidade_t));
            unidade->aeroporto = meu_aeroporto;
            unidade->aviao = aviao;
            pthread_create(&thread_vector[id++], NULL, thread_aviao, (void*)unidade);
            proximo_aviao = tempo_total + rand() % t_novo_aviao_max + t_novo_aviao_min;
        }
        tempo_final = current_timestamp();
        tempo_total = difftime(tempo_final, tempo_inicial);
    } while (tempo_total < t_simulacao);

    finalizar_aeroporto(meu_aeroporto);
    return 1;
}
