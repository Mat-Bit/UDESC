#include <stdio.h>
#include "eda.h"
extern FILE *yyin;
extern tArvore *tabelaSimbolos;

int main(int c, char *argv[])
{
	FILE *file;
	file = fopen (argv[1], "r");
	if ( file == NULL){
		printf("Arquivo \"%s\" não econtrado.\n", argv[1] );
		return 1;
	}
	tabelaSimbolos = criarArvore();
	yyin = file;
	yyparse();
	printArvore(tabelaSimbolos);
	return 0;
}
