%{
#include <stdio.h>
#include <stdlib.h>
#include "eda.h"

tArvore * tabelaSimbolos;

typedef struct Atributo{
  tLista *listaId;
  char id[MAXID];
  int tipo;
  int ConstInt;
  float ConstFloat;
  tAST *ast;
//
}tAtributo;

#define YYSTYPE tAtributo
int __linha__ = 1;
%}

%token TADD TSUB TMUL TDIV TMENOR TMAIOR TATB TMENORIG TMAIORIG TCOM TDIF TCEE TCOU TNEG TIF TWHILE TELSE TAPAR TFPAR TACOL TFCOL TACHA TFCHA TASP TINT TFLOAT TSTRING TID TDIGITO TPV TV TRET TPRINT TREAD TVOID TLITERAL TRUE FALSE TFLOAT TEND T_FIM TNINT

%%
Programa: ListaFuncoes BlocoPrincipal
    | BlocoPrincipal;

ListaFuncoes: ListaFuncoes Funcao
    | Funcao;

Funcao: TipoRetorno TID TAPAR DeclParametros TFPAR BlocoPrincipal
    | TipoRetorno TID TAPAR TFPAR BlocoPrincipal;

TipoRetorno: Tipo
    | TVOID;

DeclParametros: DeclParametros TV Parametro
    | Parametro;

Parametro: Tipo TID;

BlocoPrincipal: TACHA Declaracoes ListaCmd TFCHA
    | TACHA ListaCmd TFCHA;

Declaracoes: Declaracoes Declaracao
    | Declaracao;

Declaracao: Tipo ListaId TPV {insereTipo($2.listaId, $1.tipo); printLista($2.listaId); insereListaNaArvore($2.listaId, tabelaSimbolos);};

Tipo: TINT {$$.tipo = T_INT;}
    | TSTRING {$$.tipo = T_STRING;}
    | TFLOAT {$$.tipo = T_FLOAT;};

ListaId: ListaId TV TID {insereLista($1.listaId, $3.id); $$.listaId = $1.listaId;}
    | TID {$$.listaId = criarLista($1.id);};

Bloco: TACHA ListaCmd TFCHA;

ListaCmd: ListaCmd Comando
    | Comando;

Comando: CmdSe
    | CmdEnquanto
    | CmdAtrib
    | CmdEscrita
    | CmdLeitura
    | ChamadaProc
    | Retorno;

Retorno: TRET ExpressaoAritimetica TPV
    | TRET TLITERAL TPV;

CmdSe: TIF TAPAR ExpressaoLogica TFPAR Bloco
    | TIF TAPAR ExpressaoLogica TFPAR Bloco TELSE Bloco

CmdEnquanto: TWHILE TAPAR ExpressaoLogica TFPAR Bloco;

CmdAtrib: TID TATB ExpressaoAritimetica TPV
    | TID TATB TLITERAL;

CmdEscrita: TPRINT TAPAR TASP ExpressaoAritimetica TASP TFPAR TPV
    | TPRINT TAPAR ExpressaoAritimetica TFPAR TPV
    | TPRINT TAPAR TLITERAL TFPAR TPV;

CmdLeitura: TREAD TAPAR TID TFPAR TPV
    | TREAD TAPAR TEND TID TFPAR TPV;

ChamadaProc: ChamadaFuncao TPV;

ChamadaFuncao: TID TAPAR ListaParametros TFPAR
    | TID TAPAR TFPAR;

ListaParametros: ListaParametros TV ExpressaoAritimetica
    | ListaParametros TV TLITERAL
    | ExpressaoAritimetica 
    | TLITERAL;

//Expressões
ExpressaoAritimetica: ExpressaoAritimetica TADD TExpressaoAritimetica { $$.ast = cria_ast_op($1.ast, $3.ast, ADD); printa_arv_exp($$.ast);}
    | ExpressaoAritimetica TSUB TExpressaoAritimetica { $$.ast = cria_ast_op($1.ast, $3.ast, SUB); }
    | TExpressaoAritimetica { $$.ast = $1.ast; } ;

TExpressaoAritimetica: TExpressaoAritimetica TMUL FExpressaoAritmetica { $$.ast = cria_ast_op($1.ast, $3.ast, MUL); }
    | ExpressaoAritimetica TDIV FExpressaoAritmetica { $$.ast = cria_ast_op($1.ast, $3.ast, DIV); }
    | FExpressaoAritmetica  { $$.ast = $1.ast; } ;

FExpressaoAritmetica: TAPAR ExpressaoAritimetica TFPAR { $$.ast = $2.ast; }
    | TFLOAT {$$.ast = criar_ast_float($1.ConstFloat);}
    | TINT {$$.ast = criar_ast_int($1.ConstInt);}
    | TID {$$.ast = criar_ast_id($1.id);};

ExpressaoLogica: ExpressaoLogica TCEE FExpressaoLogica
    | ExpressaoLogica TCOU FExpressaoLogica
    | FExpressaoLogica;

FExpressaoLogica: TNEG FExpressaoLogica
    | TAPAR FExpressaoLogica TFPAR
    | TRUE
    | FALSE
    | ExpressaoRelacional;

ExpressaoRelacional: ExpressaoAritimetica TMAIOR ExpressaoAritimetica
    | ExpressaoAritimetica TMAIORIG ExpressaoAritimetica
    | ExpressaoAritimetica TMENOR ExpressaoAritimetica
    | ExpressaoAritimetica TMENORIG ExpressaoAritimetica
    | ExpressaoAritimetica TCOM ExpressaoAritimetica
    | ExpressaoAritimetica TDIF ExpressaoAritimetica;

%%
#include "lex.yy.c"

int yyerror (char *str)
{
	printf("[Linha%d]\tTipo de erro: %s\t antes do caracter: %s\n", __linha__,str, yytext);
}

int yywrap()
{
	return 1;
}
