#include "eda.h"

tLista *criarLista (char *id){
  tLista *elem = (tLista*)malloc(sizeof(tLista));
  if (elem != NULL){
    memcpy(elem->id, id, MAXID);
    elem->proximo = NULL;
  }
  return elem;
}

void insereTipo(tLista *head, TIPO tipo){
  if (head != NULL){
    head->tipo = tipo;
  }
}

void insereLista(tLista *head, char *id){
  if(head->proximo == NULL){
    head->proximo = (tLista *)malloc(sizeof(tLista));
    if(head->proximo != NULL){
      memcpy(head->proximo->id,id,MAXID);
      head->proximo->proximo = NULL;
    }
  }
  else{
    insereLista(head->proximo,id);
  }
}

void printLista(tLista *cabeca){
  int cond = 0;
  if (cabeca == NULL){
    printf(";\n");
    return;
  }
  else {
    if (cabeca->tipo == T_INT){
      printf("int");
      cond = 1;
    }
    if (cabeca->tipo == T_FLOAT){
      printf("float");
      cond = 1;
    }
    if (cabeca->tipo == T_STRING){
      printf("String");
      cond = 1;
    }
    if(cabeca->proximo == NULL)
    printf(" %s",(char*)cabeca->id );
    else
    printf(" %s,",(char*)cabeca->id );
    printLista(cabeca->proximo);
  }
}

tArvore * criarArvore(){
  tArvore * elem = (tArvore*)malloc(sizeof(tArvore));
  elem->raiz = NULL;
  elem->qtd = 0;
  return elem;
}

void insereArvore(tArvore *arv, char *valor){
  if(arv->raiz == NULL){
    arv->raiz = criaNo(valor, arv->qtd);
    arv->qtd++;
    return;
  }
  else{
    insereArvoreInterna(arv->raiz,valor,arv->qtd);
    arv->qtd++;
    return;
  }
}

void insereArvoreInterna(tNo *no, char *valor, int posicao){
  int elem = strcmp(no->valor, valor);
  if(elem == 0){
    printf("Símbolo %s já existe\n", valor);
    exit(-1);
  }
  if(elem > 0 && no->direita == NULL){
    no->direita = criaNo(valor,posicao);
    return;
  }
  if(elem<0 && no->esquerda == NULL){
    no->esquerda = criaNo(valor,posicao);
    return;
  }
  if(elem<0){
    insereArvoreInterna(no->esquerda,valor,posicao);
  }
  else {
    insereArvoreInterna(no->direita,valor,posicao);
  }
}

tNo * criaNo(char* valor, int num){
  tNo * elem = (tNo*)malloc(sizeof(tNo));
  elem-> valor = malloc(sizeof(char)*100);
  strcpy(elem->valor,valor);
  elem->valor[99] = '\0';
  elem->tipo = NDEFINIDO;
  elem->num = num;
  elem->direita = NULL;
  elem->esquerda = NULL;
  return elem;
}

void printArvore(tArvore *arv){
  printNos(arv->raiz, 0);
}

void printNos(tNo *no, int nivel){
  if(no == NULL) return;
  for(int j=0;j<nivel;j++){ printf("\t");}
  //printf("%s", no->valor);
  printNos(no->direita, nivel+1);
  printNos(no->esquerda, nivel+1);
}

void insereListaNaArvore(tLista *lista, tArvore *arv){
  if(lista == NULL) return;
  if(arv == NULL) return;
  insereArvore(arv,(char *)lista->id);
  insereListaNaArvore((tLista*)lista->proximo,arv);
}

tAST *criar_ast_id(char *id){
  tAST *elem = (tAST*)malloc(sizeof(tAST));
  elem->id = id;
  elem->pt1 = NULL;
  elem->pt2 = NULL;
  return elem;
}

tAST *criar_ast_int(int valor_int){
  tAST *elem = (tAST*)malloc(sizeof(tAST));
  elem->ConstInt = valor_int;
  elem->id = NULL;
  elem->pt1 = NULL;
  elem->pt2 = NULL;
  return elem;
}

tAST *criar_ast_float(float valor_float){
  tAST *elem = (tAST*)malloc(sizeof(tAST));
  elem->ConstFloat = valor_float;
  elem->id = NULL;
  elem->pt1 = NULL;
  elem->pt2 = NULL;
  return elem;
}

tAST *cria_ast_op(tAST *exp_esq, tAST *exp_dir, int cod){
  int  dir=0, esq=0;
  float dirf=0.0, esqf=0.0, resultado;
  tAST *elem = (tAST*)malloc(sizeof(tAST));
  elem->pt1 = exp_esq;
  elem->pt2 = exp_dir;
  elem-> cod = cod;
  elem->id = NULL;
}

void printa_arv_exp(tAST *cabeca){

  if(cabeca->pt1 != NULL) printa_arv_exp(cabeca->pt1);
  if(cabeca->pt2 != NULL) printa_arv_exp(cabeca->pt1);

  if(cabeca->id != NULL) printf("%s ", cabeca->id);
  else{
    if(cabeca->ConstInt != 0) printf("%d ", cabeca->ConstInt);
    if(cabeca->ConstFloat != 0.0) printf("%.1f ", cabeca->ConstFloat);
  }

}

/*
  if (elem->pt1->id != NULL){
    if(elem->id->tipo == T_INT) esq = elem->id->num;
    else{
      if(elem->id->tipo == T_FLOAT) esqf = elem->id->num;
    }
  }
  else{
    if(elem->pt1->ConstInt != 0) esq = elem->pt1->ConstInt;
    else{
      if(elem->pt1->ConstFloat != 0.0) esqf = elem->pt1->ConstFloat;
    }
  }
  if (elem->pt2->id != NULL){
    if(elem->id->tipo == T_INT) dir = elem->id->num;
    else{
      if(elem->id->tipo == T_FLOAT) dirf = elem->id->num;
    }
  }
  else{
    if(elem->pt2->ConstInt != 0) dir = elem->id->ConstInt;
    else{
      if(elem->pt2->ConstFloat != 0.0) dirf = elem->id->ConstFloat;
    }
  }

  if(cod == ADD){
    if(esq != 0 && dir != 0) resultado = esq + dir;
  }
  */
