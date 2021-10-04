//João Paulo Souza Ferrete - 2018205041 - Ciência da Computação

#include <stdio.h>                                                              //Inclusão das bibliotecas utilizadas no programa
#include <stdlib.h>

#define MAXNIVEIS 6                                                             //Definimos uma macro que corresponde ao número máximo de níveis possíveis no programa

typedef struct{                                                                 //Implementação da estrutura do tipo Info
    int value;
}Info;

typedef struct tNode{                                                           //Implementação da estrutura do tipo Node
    struct tNode ** next;
    Info * info;
}Node;

typedef struct{                                                                 //Implementação da estrutura do tipo List
    Node ** first;
    int *size;
}List;
