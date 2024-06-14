#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"
#include "UniaoBusca.h"

void mostra_int(void *p)
{
    printf("%d ", *(int *)p);
}

int inicializa_uniao(UniaoBusca *u)
{
    Lista multi;

    inicializa_lista(&multi, sizeof(Lista));

    u->multi = multi;
}

int compara_int(void *p1, void *p2)
{
    return *(int *)p1 == *(int *)p2;
}

int busca_conjunto(UniaoBusca u, int x)
{
    for (int i = 0; i < u.multi.qtd; i++)
    {
        Lista l;
        le_valor(u.multi, &l, i);
        if (busca(&l, &x, compara_int) != -1)
            return i;
    }
    return -1;
}

int cria_conjunto(UniaoBusca *p, int *x)
{
    if (busca_conjunto(*p, *x) != -1)
        return ERRO_VALOR_REPITIDO;

    Lista sub;

    inicializa_lista(&sub, sizeof(int));

    insere_inicio(&sub, x);

    insere_fim(&(p->multi), &sub);

    return 0;
}

int uniao(UniaoBusca *p, int x, int y)
{
    Lista lista_x, lista_y;
    le_valor(p->multi, &lista_x, x);
    le_valor(p->multi, &lista_y, y);

    concatena(&lista_x, &lista_y);

    Lista temp;
    remove_pos(&p->multi, &temp, y);

    return 1;
}

void mostra_conjuntos(UniaoBusca u)
{
    Elemento *aux = u.multi.cabeca;

    int i = 0;
    while (aux != NULL)
    {
        printf("Lista %d:\n", ++i);
        Lista info = *(Lista *)aux->info;

        mostra_lista(info, mostra_int);

        aux = aux->proximo;
        printf("\n");
    }
}