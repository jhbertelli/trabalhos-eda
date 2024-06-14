#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista.h"

void inicializa_lista(Lista *p, int t)
{
	p->tamInfo = t;
	p->cabeca = NULL;
	p->qtd = 0;
}

int lista_vazia(Lista l)
{
	return l.cabeca == NULL;
}

// Fun��o privada da biblioteca.
Elemento *aloca_elemento(void *info, int tam)
{
	Elemento *p = malloc(sizeof(Elemento));
	if (p == NULL)
		return NULL; // Erro, falta de mem�ria!
	p->info = malloc(tam);
	if (p->info == NULL)
	{
		free(p);
		return NULL; // Erro, falta de mem�ria!
	}
	memcpy(p->info, info, tam);
	return p; // Sucesso!
}

int insere_inicio(Lista *p, void *info)
{
	Elemento *novo = aloca_elemento(info, p->tamInfo);
	if (novo == NULL)
		return 0; // Erro, falta de mem�ria!

	novo->proximo = p->cabeca;
	p->cabeca = novo;
	p->qtd++;
	return 1; // Sucesso!
}

int insere_fim(Lista *p, void *info)
{
	if (lista_vazia(*p))
		return insere_inicio(p, info);

	Elemento *aux = p->cabeca;
	while (aux->proximo != NULL)
		aux = aux->proximo;

	Elemento *novo = aloca_elemento(info, p->tamInfo);
	if (novo == NULL)
		return 0; // Erro, falta de mem�ria!

	aux->proximo = novo;
	novo->proximo = NULL;
	p->qtd++;
	return 1; // Sucesso!
}

int insere_pos(Lista *p, void *info, int pos)
{
	if (pos < 0 || pos > p->qtd)
		return ERRO_POS_INVALIDA;

	if (pos == 0)
		return insere_inicio(p, info);

	Elemento *aux = p->cabeca;
	int cont;
	for (cont = 0; cont < pos - 1; cont++)
		aux = aux->proximo; // Vai at� elemento em pos-1

	Elemento *novo = aloca_elemento(info, p->tamInfo);
	if (novo == NULL)
		return 0; // Erro, falta de mem�ria!

	novo->proximo = aux->proximo;
	aux->proximo = novo;
	p->qtd++;
	return 1; // Sucesso!
}

int remove_inicio(Lista *p, void *info)
{
	if (lista_vazia(*p))
		return ERRO_LISTA_VAZIA;

	Elemento *aux = p->cabeca;
	memcpy(info, aux->info, p->tamInfo);
	p->cabeca = aux->proximo;
	free(aux->info);
	free(aux);
	p->qtd--;
	return 1; // Sucesso!
}

int remove_fim(Lista *p, void *info)
{
	if (lista_vazia(*p))
		return ERRO_LISTA_VAZIA;

	if (p->qtd == 1)
		return remove_inicio(p, info);

	Elemento *aux = p->cabeca;
	while (aux->proximo->proximo != NULL)
		aux = aux->proximo;

	Elemento *ultimo = aux->proximo;
	memcpy(info, ultimo->info, p->tamInfo);
	free(ultimo->info);
	free(ultimo);
	aux->proximo = NULL;
	p->qtd--;
	return 1; // Sucesso!
}

int remove_pos(Lista *p, void *info, int pos)
{
	if (lista_vazia(*p))
		return ERRO_LISTA_VAZIA;

	if (pos < 0 || pos >= p->qtd)
		return ERRO_POS_INVALIDA;

	if (pos == 0)
		return remove_inicio(p, info);

	Elemento *aux = p->cabeca;
	int cont;
	for (cont = 0; cont < pos - 1; cont++)
		aux = aux->proximo; // Vai at� pos-1

	Elemento *x = aux->proximo;
	aux->proximo = x->proximo;
	memcpy(info, x->info, p->tamInfo);
	free(x->info);
	free(x);
	p->qtd--;
	return 1; // Sucesso!
}

int le_valor(Lista l, void *info, int pos)
{
	if (pos < 0 || pos >= l.qtd)
		return ERRO_POS_INVALIDA;

	Elemento *aux = l.cabeca;
	int cont;
	for (cont = 0; cont < pos; cont++)
		aux = aux->proximo; // Vai at� elemento em pos

	memcpy(info, aux->info, l.tamInfo);
	return 1; // Sucesso!
}

int modifica_valor(Lista l, void *info, int pos)
{
	if (pos < 0 || pos >= l.qtd)
		return ERRO_POS_INVALIDA;

	Elemento *aux = l.cabeca;
	int cont;
	for (cont = 0; cont < pos; cont++)
		aux = aux->proximo; // Vai at� elemento em pos

	memcpy(aux->info, info, l.tamInfo);
	return 1; // Sucesso!
}

void mostra_lista(Lista l, void (*mostra)(void *))
{
	if (lista_vazia(l))
		printf("Lista vazia!\n");
	else
	{
		printf("Dados da lista:\n");
		Elemento *p = l.cabeca;
		while (p != NULL)
		{
			mostra(p->info); // Invoca��o por callback
			p = p->proximo;
		}
	}
}

int busca(Lista *l, void *info, int (*compara)(void *, void *))
{
	Elemento *p = l->cabeca;
	int pos = 0;

	while (p != NULL)
	{
		if (compara(p->info, info) == 1)
			return pos;

		p = p->proximo;
		pos++;
	}

	return -1; // não encontrado
}

void concatena(Lista *l1, Lista *l2)
{
	Elemento *aux_l1 = l1->cabeca;

	if (aux_l1 == NULL)
		l1->cabeca = l2->cabeca;
	else
	{
		while (aux_l1->proximo != NULL)
			aux_l1 = aux_l1->proximo;

		aux_l1->proximo = l2->cabeca;
	}

	l1->qtd += l2->qtd;
	l2->cabeca = NULL;
	l2->qtd = 0;
}

void limpa_lista(Lista *p)
{
	Elemento *aux = p->cabeca;

	while (aux != NULL)
	{
		Elemento *prox = aux->proximo;
		free(aux->info);
		free(aux);
		aux = prox;
	}
	p->cabeca = NULL;
	p->qtd = 0;
}
