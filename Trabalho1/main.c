#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha.h"

int precedencia(char c);
char *converter_para_posfixo(char *e);

int main()
{
    char *e;

    scanf("%s", e);
    
    converter_para_posfixo(e);
}

int precedencia(char c)
{
    switch (c)
    {
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 1;
    }
}

char *converter_para_posfixo(char *e)
{
    char s[999]; // temp, tentar fazer de outro jeito depois
    int deu_erro = 0;
    
    Pilha p;
    inicializa_pilha(&p, 100);

    int i = 0, j = 0;
    int x;

    while (e[i] != '\0' && !deu_erro)
    {
        char c = e[i];
        switch (c)
        {
            // case ' ': // TODO
            //     continue;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            {
                // Coloque c na string S;
                s[j] = c;
                j++;
                break;
            }

            case '(':
            {
                empilha(&p, c);
                break;
            }
            case ')':
            {
                while (le_topo(p, &x) != ERRO_PILHA_VAZIA && x != '(')
                {
                    desempilha(&p, &x);
                    // coloque x na string S
                    s[j] = x;
                    j++;
                }

                if (pilha_vazia(p))
                {
                    printf("Erro: ')' sem '('!");
                    deu_erro = 1;
                }
                else
                    desempilha(&p, &x);

                break;
            }
            case '-':
            case '*':
            case '/':
            case '+':
            {
                le_topo(p, &x);

                if (pilha_vazia(p) || x == '(')
                    empilha(&p, c);
                else
                {
                    while (le_topo(p, &x) != ERRO_PILHA_VAZIA && precedencia(x) >= precedencia(c))
                    {
                        desempilha(&p, &x);
                        // coloque x na string S
                        s[j] = x;
                        j++;
                    }
                    
                    empilha(&p, c);
                }
                
                break;
            }
            
            default:
            {
                printf("Erro: caractere inválido: %c!", c);
                deu_erro = 1;
                break;
            }
        }

        i++;
    }

    if (!deu_erro)
    {
        while (le_topo(p, &x) != ERRO_PILHA_VAZIA && x != '(')
        {
            desempilha(&p, &x);
            // coloque x na string S
            s[j] = x;
            j++;
        }
        
        if (pilha_vazia(p))
        {
            s[j] = '\n';
            j++;
            printf("String: %s\n", s);
            // chama função para avaliar expressão em S; // próximo algoritmo
        }
        else
            printf("Erro: '(' não foi fechado!");
    }
    
    return s;
}