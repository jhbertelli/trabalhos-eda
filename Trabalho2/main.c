#include "Fila.h"
#include "Pilha.h"
#include "Matriz.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, vert_a, vert_b;
    int modo_entrada;

    printf("Gostaria de carregar os dados de exemplo do sample.txt? (0 - nao | 1 - sim)\n");
    scanf("%d", &modo_entrada);

    Matriz m;

    if (modo_entrada == 0)
    {
        printf("Insira o tamanho da matriz:\n");
        scanf("%d", &n);
        
        inicializa_matriz(&m, n, n);

        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
            {
                int val;
                printf("Valor de m[%d][%d] : ", i + 1, j + 1);
                scanf("%d", &val);
                set_valor(&m, i, j, val);
            }
    }
    else
    {
        n = 8;
        inicializa_matriz(&m, n, n);
        carrega_arquivo("sample.txt", &m);
    }

    printf("Insira o vertice A:\n");
    scanf("%d", &vert_a);

    printf("Insira o vertice B:\n");
    scanf("%d", &vert_b);

    vert_a--;
    vert_b--;

    int *va = calloc(n, sizeof(int));
    int *vs = calloc(n, sizeof(int));

    Fila f;

    inicializa_fila(&f, n);

    vs[vert_a] = 1;

    inserir(&f, vert_a);

    int achou = 0;
    int x;

    while (!fila_vazia(f) && !achou)
    {
        remover(&f, &x);

        if (x == vert_b)
            achou = 1;
        else
            for (int i = 0; i < n; i++)
                if (m.dados[x][i] == 1 && vs[i] == 0)
                {
                    vs[i] = 1;
                    va[i] = x;
                    inserir(&f, i);
                }
    }
    
    if (achou)
    {
        Pilha p;

        inicializa_pilha(&p, n);

        while (x != 0)
        {
            empilha(&p, x);
            x = va[x];
        }

        printf("-----------------\n");
        printf("Vertices visitados:\n");

        while (!pilha_vazia(p))
        {
            desempilha(&p, &x);
            printf("%d\n", ++x);
        }
    }
    else
        printf("B nao eh alcancavel a partir de A!");
}