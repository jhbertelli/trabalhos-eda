#include "UniaoBusca.h"
#include "Matriz.h"
#include <stdio.h>

int main()
{
    UniaoBusca u;

    inicializa_uniao(&u);

    int n;
    int modo_entrada;

    printf("Gostaria de carregar os dados de exemplo do sample.txt? (0 - nao | 1 - sim)\n");
    scanf("%d", &modo_entrada);

    Matriz m;

    if (modo_entrada == 0)
    {
        printf("Insira o tamanho da matriz:\n");
        scanf("%d", &n);

        inicializa_matriz(&m, n, n);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                int val;
                printf("Posicao [%d][%d] - ", i + 1, j + 1);
                scanf("%d", &val);
                set_valor(&m, i, j, val);
            }
    }
    else
    {
        n = 10;
        inicializa_matriz(&m, n, n);
        carrega_arquivo("sample.txt", &m);
    }

    mostra_matriz(m);

    for (int i = 1; i <= n; i++)
        cria_conjunto(&u, &i);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (m.dados[i - 1][j - 1] == 1)
            {
                int x = busca_conjunto(u, i);
                int y = busca_conjunto(u, j);
                if (x != y)
                    uniao(&u, x, y);
            }

    mostra_conjuntos(u);
}
