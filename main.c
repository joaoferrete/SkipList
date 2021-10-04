//João Paulo Souza Ferrete - 2018205041 - Ciência da Computação


#include <stdio.h>                                                              //Inclusão das bibliotecas
#include <stdlib.h>
#include "func.c"                                                               //Inclusão do arquivo com as funções implementadas

int main(){
    List * lst;
    char a;
    int c, h;
    Node **listh;
    createList(&lst);                                                           //Criação da cabeça da lista, atribuindo-a à variável lst
    while(scanf("%c", &a)!=EOF){                                                //Laço que será executado enquanto a entrada for diferente do fim do arquivo
        if(a=='I'||a=='i'){                                                     //Caso seja digitado a letra 'I', será solicitado dois inteiros: 'c' que corresponde à chave, ou valor, a ser inserido e h que corresponde à maior hierarquia em que ele estará
            scanf("%d %d", &c, &h);
            insere(createNode(createInfo(c)), h, lst);                          //Os valores lidos serão passados como parâmetros para as funções que criam um elemento de informação, um nó e inserem na lista
        }else if(a=='r' || a=='R'){                                             //Caso seja inserido a letra 'R', será lido um inteiro que deverá estar no elemento de informação do nó a ser removido
            scanf("%d", &c);
            removeList(createInfo(c), lst);                                     //O inteiro lido é passado para função de criar Info e então esse ponteiro é passado como parâmetro para a função de remover um elemento, juntamente com o ponteiro para a lista
        }else if(a=='b'||a=='B'){                                               //Caso o usuário digite a letra 'B', será alocado um espaço para um vetor de ponteiros
            listh=alocaListh();
            scanf("%d", &c);                                                    //Será solicitado um inteiro, que será procurado
            if(listh) searchList(createInfo(c), lst, listh, 1);                 //E então, será chamada a função searchList com 1 no parâmetro de impressão, para que seja impresso o caminho percorrido para encontrar, ou não, o elemento
            free(listh);                                                        //É liberado o espaço utilizado por LISTH
        }else if(a=='p' || a=='P'){                                             //Caso seja inserido a letra 'P', será solicitado ao usuário um inteiro entre 0 e MAXNIVEIS-1 para que seja impresso o nível correspondente, através da função printListh
            scanf("%d", &h);
            printListh(lst, h);
        }else if(a=='a'||a=='A'){                                               //Caso seja inserido 'A', será impresso todos os elementos da lista, através da função printList
            printList(lst);
        }else if(a=='s' || a=='S'){
            freeList(lst);                                                      //Caso seja digitado 'S' será apagada a lista e encerrado o programa (utilizado para execução sem arquivo de entrada)
            return 0;
        }
    }
    freeList(lst);                                                              //Ao fim da execução do programa é liberado todo o espaço utilizado pela SkipList e então o programa é encerrado
    return 0;
}



/*
                                INTRODUÇÃO
    O programa proposto e implementado anteriormente tem como foco a implementa-
ção e o funcionamento de uma skiplist, que consiste em uma lista encadeada onde,
cada elemento (ou nó) possuí ponteiros para o próximo elemento baseados em uma
hierarquia, ou seja, uma lista com várias sub-listas na qual a sublista mais in-
ferior possuí todas os elementos das superiores e, se um elemento está numa sub-
lista, obrigatoriamente ele está contido nas sublistas inferiores.
    A implementação foi feita de forma que o usuário consiga inserir, remover,
buscar e imprimir elementos da skiplist.

                                IMPLEMENTAÇÃO
    O código foi montado a partir da estrutura presente no arquivo 'estrur.h', que
consiste na criação de três tipos específicos: tipo Info (o tipo do elemento de
informação, que contém um único campo para armazenar informações do tipo inteiro),
tipo Node (o tipo nó, que é o elemento da lista em si. Possuí dois campos, um pon-
teiro para ponteiros de elementos do mesmo tipo, que será utilizado para alocação
de espaço para um vetor de ponteiros que armazena o endereço do nó posterior em
cada sublista ou hierarquia, e um ponteiro para elementos do tipo Info, onde será
armazenado o endereço para o elemento de informação daquele nó) e o tipo List (
que representa a 'cabeça' da lista. Possui dois campos, um ponteiro para pontei-
ros do tipo Node, onde será alocado espaço para um vetor de ponteiros q armazena
um ponteiro para o primeiro elemento de cada hierarquia, e um ponteiro para pon-
teiros do tipo inteiro, onde será alocado um vetor para armazenar o tamanho de ca-
da sublista). Na estrutura, também, foi criada uma macro que define o número má-
ximo de sublistas possíveis no programa.
No que diz respeito a funções, podemos dividir em dois tipos: funções principais
(que são as funções que fazem as alterações, propriamente ditas, na skiplist) e
as funções secundárias (que são as funções que dão um suporte às outras funções).
Pode-se classificar como funções principais as funções 'searchList', 'insere',
'removeList' e a função main.
    A função 'searchList' é a função essencial do programa. Ela é responsável por
buscar um elemento dentro da lista e é utilizada para inserção e remoção de ele-
mentos.São passados como parâmetros obrigatórios para sua execução um elemento de
informação a ser procurado, um ponteiro para a 'cabeça' da lista, um ponteiro para
ponteiros do tipo Node e um inteiro. A sua execução consiste em, primeiramente,
verificar se os parâmetros inseridos são válidos para iniciar a execução. Em caso
positivo, um ponteiro do tipo Node recebe o endereço de memória para o primeiro ele-
mento da sublista mais superior ṕara começar a percorrer a lista, a partir de um
laço. A primeira verificação dentro do laço é se o endereço para qual o ponteiro
aponta é inválido ou se a execução do programa não é a primeira e o elemento que
está sendo apontado é maior que o elemento buscado. Como a lista é ordenada crescen-
temente, se a verificação for verdadeira, o ponteiro passa a apontar para a pri-
meira posição da sublista atual, caso contrário ele continua apontando para o
mesmo local. Após este passo, o programa entra em um laço que fará o ponteiro
avançar até o maior elemento menor que o elemento procurado ou, caso o elemento
buscado esteja na primeira posição, para o próprio elemento buscado. Este ele-
mento será salvo no vetor (representado pelo ponteiro de ponteiros) passado como
parâmetro. Caso o inteiro passado por parâmetro seja maior que zero, será impres-
so esse elemento. Este loop acontecerá até que seja percorrida toda a skiplist,
ou seja, enquanto a hierarquia for maior ou igual a zero. Ao sair deste laço, a
função verifica se o elemento está ou não na lista. Em caso positivo é verificado
se a variável para impressão é maior que zero para imprimir o elemento encontrado,
então imprime-se "true" e é retornado 1. Em caso negativo, é impresso "false" e
retornado 0.
    A função 'insere' é a função responsável por inserir elementos na skiplist.
Ela recebe como parâmetros obrigatórios um ponteiro para o nó que deve ser inserido,
um inteiro que representa o maior nível em que o nó deve ser inserido e o ponteiro
para a lista. Ao ser iniciada, a função aloca o espaço necessário para o vetor de
ponteiros que será passado para a função search a partir de outra função, a
'alocaListh'. Após a chamada da função de busca, se o elemento que será inserido
estiver na lista, a função é encerrada. Caso contrário, o elemento será inserido.
A inserção ocorre através de um laço que inicia no nível passado como parâmetro
até o nível 0, onde existem 3 casos possiveis: Caso o ponteiro retornado ao vetor
pela função search seja o primeiro da lista e o elemento a ser adicionado é menor
que o elemento que já está na lista, reapontamos a cabeça para o novo nó e então
reapontamos o nó para a próxima posição da lista. Caso o elemento a ser adicionado
é o primeiro elemento da lista naquele nível, também reapontamos a cabeça. Já, caso
não seja nenhum dos casos anteriores, temos que o elemento deve ser adicionado
após a posição apontada pelo vetor. Neste caso, fazemos os reapontamentos a partir
do vetor que foi retornado pela função de busca. Ao fim da inserção, é liberado o
espaço utilizado pelo vetor e então retornamos 1, indicando que a inserção foi
feita.
    Já, a função 'removeList' é responsável por remover elementos da lista. Ela
recebe como parâmetro um ponteiro para o elemento de informação que contém a chave
a ser removida e o ponteiro para a lista. Da mesma forma que a função insere, é alocado,
a partir da função 'alocaListh' o espaço para o vetor de ponteiros onde são armaze-
nados os ponteiros, dos elementos anteriores ao elemento a ser removido, pela função
search. Caso a função de busca não encontre o elemento a ser removido, a função é
encerrada, caso contrário é executado um loop que inicia no numero máximo de níveis
até o nível 0 em que os elementos são apagados de duas formas: Caso o elemento seja
o primeiro é feito o reapontamento da cabeça para o próximo elemento. Caso ele não
seja o primeiro, usamos o nó apontado pela posição do vetor de ponteiros e o fazemos
apontar para o nó posterior ao elemento que desejamos deletar. Ao fim do laço é
liberado o espaço utilizado pelo nó e pelo vetor e, então, retornamos 1 simbolizando
que a remoção foi efetuada.
    A função 'main' é a principal função e é responsável pela execução, propriamente
dita, do programa. Ela é iniciada com a função 'createList' que aloca e inicia os
campos de uma lista e então entra-se em um loop até que seja lido o fim do arquivo
'EOF'. Então são aguardadas instruções, que são: 'I' para inserir um elemento,
'R' para remover um elemento, 'B' para buscar um elemento, 'P' para imprimir um
nível específico da skiplist, 'A' para imprimir toda a skiplist, e 'S' para sair
do programa (utilizada, apenas, para utilização do programa com entrada a partir
do stdin). Após a leitura de cada comando é solicitada a entrada de cada um dos
parâmetros obrigatórios para a execução da função específica. No caso da função
de busca, também é alocado o espaço para o vetor de ponteiros e, após sua execução,
o espaço é liberado. Note, também, que o parâmetro responsável pela impressão é 1.
Após a execução do programa, ou caso seja inserido a letra 'S', o programa libera
o espaço utilizado pela skiplist através da função 'freeList' e então é encerrado
o programa.
    Foram implementadas, também, outras funções para a execução do programa, as
funções secundárias. Elas são 'isEmptyList'(responsável por verificar se a lista está
vazia), 'freeList' (responsável por liberar o espaço utilizado pela lista),
'alocaListh'(responsável por alocar o espaço para o vetor de ponteiros), 'createList'
(responsável por alocar e inicializar os campos de uma lista), 'createInfo'(respon-
sável por alocar e atribuir os elementos de informação), 'createNode'(responsável
por alocar e inicializar os campos de um nó), 'printListh'(responsável por imprimir
os elementos de uma sublista específica) e 'printList' (responsável por imprimir
toda a lista).
                                CONCLUSÃO
    Durante a implementação do programa foi possível colocar em prática os conhe-
cimentos, adquiridos em sala, sobre a estrutura de dados 'lista' e suas derivadas.
Foi possível, também, aprimorar a utilização de estratégias para a implementação da
mesma.
    Como principais dificuldades, é possível destacar o funcionamento, de maneira
correta, da função 'searchList', já que o bom funcionamento de todo o programa de-
pende, veementemente, da correta implementação desta função. Porém, com certa de-
dicação, foi possível ultrapassar tal problema e atingir um funcionamento esperado
para todo o programa.


*/
