#include "Lista.h"

#define ERRO_VALOR_REPITIDO -1

typedef struct
{
    Lista multi;
} UniaoBusca;

int inicializa_uniao(UniaoBusca *u);
int busca_conjunto(UniaoBusca u, int x);
int cria_conjunto(UniaoBusca *p, int *x);
int uniao(UniaoBusca *p, int x, int y);
void mostra_conjuntos(UniaoBusca u);