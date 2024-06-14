#include "Matriz.h"
#include <stdlib.h>
#include <stdio.h>

void inicializa_matriz( Matriz *p, int l, int c ){
	p->lin = l;
	p->col = c;
	p->dados = malloc( sizeof(int*) * l );
	int i, j;
	for( i = 0 ; i < l ; i++ ){
		p->dados[i] = calloc( c, sizeof(int) );
		/*
		p->dados[i] = malloc( sizeof(int) * c );
		for( j = 0 ; j < c ; j++ )
			p->dados[i][j] = 0;
		*/
	}
}

void mostra_matriz( Matriz x ){
	printf("Dados da matriz %dx%d:\n", x.lin, x.col );
	int i, j;
	for( i = 0 ; i < x.lin ; i++ ){
		for( j = 0 ; j < x.col ; j++ )
			printf("%d\t", x.dados[i][j]);
		printf("\n");
	}
	printf("--------------------------------------\n");
}

int set_valor( Matriz *p, int i, int j, int valor ){
	if( i >= p->lin || j >= p->col || i < 0 || j < 0 )
		return ERRO_COORD_INVALIDA;
			
	p->dados[i][j] = valor;
	return 1; // Sucesso.
}

void gera_valores( Matriz *p, int limite ){
	int i, j;
	for( i = 0 ; i < p->lin ; i++ )
		for( j = 0 ; j < p->col ; j++ )
			set_valor( p, i, j, rand() % limite + 1 );
}

void desaloca_matriz( Matriz *p ){
	int i;
	for( i = 0 ; i < p->lin ; i++ )
		free( p->dados[i] );
	free( p->dados );
}

int carrega_arquivo( char *nome_arq, Matriz *p ){
	FILE *f = fopen( nome_arq, "rt" );
	if( f == NULL )
		return 0; // Erro! (função booleana)
		
	int lin, col, x;
	fscanf( f, "%d %d", &lin, &col );
	inicializa_matriz( p , lin, col );
	int i, j;
	for( i = 0 ; i < p->lin ; i++ )
		for( j = 0 ; j < p->col ; j++ ){
			fscanf( f, "%d", &x);
			set_valor( p, i, j, x );
		}

	return 1; // Sucesso!
}

