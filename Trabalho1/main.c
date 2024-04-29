#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha.h"

int precedencia(char c);
int avaliar_funcao(char *expression);
char *converter_para_posfixo(char *e);

int main()
{
    char e[200];
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
            return 2;
    }
}

char *converter_para_posfixo(char *e)
{
    char *s = malloc(strlen(e) + 1);
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
                s[j++] = c;
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
                    s[j++] = x;
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
                        s[j++] = x;
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
            s[j++] = x;
        }
        
        if (pilha_vazia(p))
        {
            s[j++] = '\0';
            printf("String: %s\n", s);
            int res = avaliar_funcao(s);
            printf("%d", res);
        }
        else
            printf("Erro: '(' não foi fechado!");
    }
    
    desaloca_pilha(&p);
    return s;
}

int eh_digito(char c)
{
    switch (c)
    {
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
            return 1;
        default:
            return 0;
    }
}

int avaliar_funcao(char *expression)
{
    Pilha p;
    int i = 0;

    inicializa_pilha(&p, strlen(expression));

    while (expression[i] != '\0')
    {
        char c = expression[i];
        if (eh_digito(c))
        {
            int converted = c - 48;
            empilha(&p, converted);
        }
        else
        {
            int aux1, aux2, result;
            desempilha(&p, &aux2);
            desempilha(&p, &aux1);

            switch (c)
            {
                case '+':
                    result = aux1 + aux2;
                    break;
                case '-':
                    result = aux1 - aux2;
                    break;
                case '/':
                    result = aux1 / aux2;
                    break;
                case '*':
                    result = aux1 * aux2;
                    break;
            }

            empilha(&p, result);
        }

        i++;
    }

    int res;

    desempilha(&p, &res);

    desaloca_pilha(&p);

    return res;
}