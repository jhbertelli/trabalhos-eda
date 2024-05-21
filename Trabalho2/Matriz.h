#define ERRO_COORD_INVALIDA -1

typedef struct{
	int **dados;
	int lin, col;
} Matriz;

void inicializa_matriz( Matriz *p, int l, int c );
void mostra_matriz( Matriz x );
int set_valor( Matriz *p, int i, int j, int valor );
void gera_valores( Matriz *p, int limite );
void desaloca_matriz( Matriz *p );
int carrega_arquivo( char *nome_arq, Matriz *p );

