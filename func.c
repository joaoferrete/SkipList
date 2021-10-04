//João Paulo Souza Ferrete - 2018205041 - Ciência da Computação

#include <stdio.h>                                                              //Inclusão das bibliotecas
#include <stdlib.h>
#include "estrut.h"                                                             //Inclusão do arquivo com a estrutura já implementada


int isEmptyList (List * lst){                                                   //Função que verifica se a lista está vazia
    if(!lst) return 0;                                                          //Verificação se a lista existe
    for(int i=0;i<MAXNIVEIS; i++){                                              //Laço que verifica a existência de algum nó na lista. Caso exista é retornado 0 indicando que a lista não está vazia;
        if(lst->first[i]) return 0;
    }
    return 1;                                                                   //Caso o laço não encontre nenhum ítem é retornado 1 indicando que a lista está vazia
}

void freeList(List * lst){                                                      //Função que libera o espaço de memória utilizado pela lista. Como na sublista [0] estão todos os elementos da skiplist, serão liberados a partir dela
    int i;
    Node *aux, *aux2=NULL;
    if(isEmptyList(lst)) return;                                                //Verifica se a lista é nula e, se caso seja, interrompe a função
    aux=lst->first[0];                                                          //Atribui a variável 'aux' o primeiro nó da lista
    while (lst->first[0]){                                                      //Laço responsável por liberar o espaço de todos os nós da lista.
        lst->first[0]=aux->next[0];                                             //A cabeça da lista recebe o próximo elemento da lista
        free(aux->info);
        free(aux);                                                              //O espaço é liberado
        aux=lst->first[0];                                                      //aux recebe o proximo elemento, que é apontado pela cabeça
    }
    free(lst);                                                                  //É liberado o espaço da cabeça da lista
}

Node ** alocaListh(){                                                           //Função que aloca espaço para um vetor de ponteiro
    Node **listh;
    listh=(Node **)malloc(MAXNIVEIS * sizeof(Node *));                          //É alocado o espaço necessário
    if(!listh) return NULL;                                                     //Verifica se o espaço foi alocado corretamente
    for(int i=0;i<MAXNIVEIS;i++) listh[i]=NULL;                                     //Inicia-se os campos do vetor
    return listh;                                                               //É retornado o vetor
}

void createList(List **lst){                                                    //Função responsável por criar a lista (cabeça), alocar os espaços necessários e inicializar os campos
    (*lst)=(List *)malloc(sizeof(List));                                        //Alocação do espaço da lista
    if(!(*lst)) return;                                                         //Verificação de se o espaço foi alocado com sucesso
    (*lst)->first=(Node **) malloc(MAXNIVEIS * sizeof(Node *));                 //Alocação do vetor com as primeiras posições para cada sublista
    (*lst)->size=(int *) malloc(MAXNIVEIS * sizeof(int));                       //Alocação do vetor com o tamanho de cada sublista
    for(int i=0;i<MAXNIVEIS; i++) {                                             //Laço que inicia os campos dos vetores de primeira posição e de tamanho
        (*lst)->first[i]=NULL;
        (*lst)->size[i]=0;
    }
}

Info * createInfo(int a){                                                       //Função responsável por criar um elemento de informação. Recebe como parâmetro um inteiro para atribuir ao campo 'value'
    Info *ptr;
    ptr=(Info *) malloc(sizeof(Info));                                          //Alocação do espaço necessário para o tipo Info
    if(!ptr) return NULL;                                                       //Verifica se o espaço foi alocado com sucesso
    ptr->value=a;                                                               //Atribuíção do inteiro ao elemento do tipo Info
    return ptr;                                                                 //Retorna-se o elemento de informação
}

Node * createNode(Info * info){                                                 //Função responsável por criar um nó (elemento tipo Node). Recebe um elemento de informação como parâmetro e retorna um ponteiro do tipo Node
    if(!info) return NULL;
    Node * ptr;
    ptr=(Node*)malloc(sizeof(Node));                                            //Alocação do espaço necessário para um Node
    if(!ptr) return NULL;                                                       //É verificado se o espaço foi alocado corretamente
    ptr->info=info;                                                             //O endereço do elemento de informação é atribuído ao campo 'info' do Node
    ptr->next=(Node **) malloc(MAXNIVEIS * sizeof(Node *));                     //È alocado o espaço necessário para o vetor de ponteiros Next
    for(int i=0; i<MAXNIVEIS; i++){                                             //Laço que inicia os campos do vetor Next com NULL
        ptr->next[i]=NULL;
    }
    return ptr;                                                                 //É retornado o ponteiro para a nova área alocada
}

int searchList(Info * inf, List * lst, Node **listh, int imprimir){             //Função responsável por buscar um elemento na SkipList e retorna 0 caso o elemento não esteja e 1 caso contrário
    if(isEmptyList(lst) || !inf || !listh){                                     //Verifica-se se a lista é vazia ou se os parâmetros passados são inválidos. Caso positivo, é impresso 'false' e retornado 0
        printf("false\n");
        return 0;
    }
    Node * aux = lst->first[MAXNIVEIS-1];
    for(int i=MAXNIVEIS-1;i>=0;i--){                                            //Loop responsável por buscar os elementos
        if(lst->first[i]){
            if(!aux || (i<MAXNIVEIS-1 && aux->info->value >= inf->value))aux=lst->first[i]; //Verificação para agilizar a procura na Skiplist. Caso não seja a primeira iteração e o elemento que está sendo  acessado é maior ou igual ao buscado a busca inicia do início. Caso contrário, a busca continua da posição atual.
            while((aux)&&(aux->next[i])&&(aux->next[i]->info->value < inf->value)) aux=aux->next[i]; //Enquanto o elemento posterior for menor que o elemento buscado, a variável 'aux' avança, até parar ao elemento anterior ao buscado, ou o proprio elemento buscado caso seja o primeiro.
            listh[i]=aux;                                                       //Atribuímos o elemento anterior ao buscado à um vetor de ponteiros, para facilitar a inserção ou remoção
            if(imprimir) printf("%d %d\n", aux->info->value, i);                //Caso imprimir seja maior que 1, é impresso o maior elemento menor que o elemento buscado.
        }
    }
    if(lst->first[0] ){                                                         //Caso a lista não seja nula
             if(aux && (aux->next[0] && aux->next[0]->info->value == inf->value)){ //Caso o elemento posterior ao ultimo elemento verificado seja o elemento verificado
             if(imprimir) printf("%d 0\n", aux->next[0]->info->value);          //Caso imprimir seja maior que 1, é impresso o elemento encontrado
             printf("true\n");
             return 1;
        }else if (aux->next[0]==lst->first[0]->next[0] && aux->info->value == inf->value){  //Caso o elemento buscado seja o primeiro da lista
            if(imprimir) printf("%d 0\n", aux->info->value);
            printf("true\n");
            return 1;
        }
    }

    printf("false\n");                                                          //Caso as condições anteriores não sejam satisfeitas, é impresso falso e retornado 0
    return 0;
}

int insere (Node * node, int h, List * lst){                                    //Função responsável por inserir um elemento na lista na hierarquia passada como parâmetro
    Node **ptr, *aux=NULL;
    int i;
    ptr=alocaListh();                                                           //Alocação do espaço do vetor de ponteiros passado como parâmetro para função search que auxilia na inserção
    if(!node || !lst || !ptr || h>MAXNIVEIS-1){                                 //Caso os elementos da função sejam inválidos a função é encerrada
        printf("false\n");
         return 0;
    }
    if(searchList(node->info, lst, ptr, 0)){                                    //É chamada a função Search. Caso o elemento que se deseja inserir já exista na lista, ou seja, caso seja retornado 0 da função search, a função é encerrada, caso contrário continua-se a execução
        printf("false\n");
        free(ptr);
        return 0;
    }
    for(i=h; i>-1; i--){                                                        //Caso o elemento ainda não exista na lista, ele é adicionado com um laço a partir da hierarquia escolhida até a 0
        if(ptr[i]==lst->first[i] && lst->first[i] && lst->first[i]->info->value > node->info->value){ //Caso o elemento retornado seja o primeiro elemento e o elemento a ser adicionado é menor que o elemento já existente na lista, ele é adicionado na primeira posição, fazendo que continue de forma crescente
            aux=lst->first[i];
            lst->first[i]=node;
            node->next[i]=aux;
            lst->size[i]++;                                                     //É acrescido em uma unidade a quantidade de elementos naquela hierarquia
        }else if(ptr[i]==lst->first[i] && !lst->first[i]){                      //Caso o elemento seja o primeiro a ser adicionado, é feito a cabeça apontar para esse elemento
            lst->first[i]=node;
            node->next[i]=NULL;
            lst->size[i]++;
        }else{                                                                  //Caso contrário, o elemento é inserido na posição retornada
            aux=ptr[i]->next[i];
            ptr[i]->next[i]=node;
            node->next[i]=aux;
            lst->size[i]++;
        }
    }
    free(ptr);                                                                  //É liberado o espaço do vetor de ponteiros
    printf("true\n");
    return 1;                                                                   //É retornado 1 pois a inserção foi bem feita
}

int removeList(Info * inf, List * lst){                                         //Função responsável responsável por remover um elemento específico da skiplist
    Node **ptr;
    Node *aux;
    int i;
    ptr=alocaListh();                                                           //Alocação de espaço do vetor de ponteiros passado por parâmetro à função search
    if(!inf || isEmptyList(lst) || !ptr){                                       //Verifica se a alocação foi bem sucedida e se os elementos são válidos
         printf("false\n");
         return 0;
    }
    if(searchList(inf, lst, ptr, 0)==0){
        printf("false\n");
        return 0;
    }
    if(lst->first[0]->info->value == inf->value) aux=lst->first[0];             //Verifica se o elemento a ser deletado é o primeiro ou não, e atribuí esse elemento à variável 'aux' para ser eletado
    else aux=ptr[0]->next[0];
    for(i=MAXNIVEIS-1; i>-1; i--){                                              //Laço para remover os elementos
        if(lst->first[i] && lst->first[i]==aux){                                //Caso o elemento a ser apagado seja o primeiro, são feitos os reapontamentos da cabeça e a diminuíção da quantidade de elementos
            lst->first[i]=aux->next[i];
            lst->size[i]--;
        }
        else if(ptr[i] && ptr[i]->next[i] && ptr[i]->next[i] == aux){           //Caso não seja o primeiro, é feito o reapontamento à partir do vetor de ponteiros
            ptr[i]->next[i]=aux->next[i];
            lst->size[i]--;
        }
    }

    free(aux->info);                                                            //É liberado o espaço utilizado pelo elemento de informação
    free(aux);                                                                  //É liberado o espaço utilizado pelo nó que deve ser apagado
    free(ptr);
    printf("true\n");
    return 1;                                                                   //É retornado 1 informando que a remoção ocorreu com sucesso
}

void printListh(List * lst, int h){                                             //Função que imprime uma hierarquia específica da Skiplist
    Node * aux;
    if(h>MAXNIVEIS-1) return;                                                   //Caso a hierarquia inserida seja maior que o máximo de hierarquias a função é encerrada
    if(isEmptyList(lst) || !lst->first[h]) return;                              //Caso a lista não possua elementos a função é encerrada
    aux=lst->first[h];                                                          // A variável 'aux' recebe o primeiro elemento da lista
    while(aux){                                                                 //Enquanto Aux for diferente de NULL é impresso o conteúdo e a chave da sublista e aux avança
        printf("%d %d\n", aux->info->value, h);
        aux=aux->next[h];
    }
}

void printList(List * lst){                                                     //Função que imprime toda a Skiplist
    if(isEmptyList(lst)) return;                                                //Caso a lista esteja vazia a função é interrompida
    for(int i=MAXNIVEIS-1; i>-1;i--) printListh(lst, i);                        //Caso contrário, a função printListh é chamada para cada hierarquia
}
