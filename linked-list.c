#include <stdio.h>
#include <stdlib.h>

struct Node {
    double value;
    int col;
    struct Node *next;
};

typedef struct Node node;

struct List{
    struct Node *inicio;
    struct Node *fim;
};
typedef struct List List;

void list_init(List *list) {
    list->inicio = (node*)malloc(sizeof(node));
    list->fim = (node*)malloc(sizeof(node));
    list->inicio->next = NULL;
    list->inicio->col = -1;
    list->fim = list->inicio;
}

void list_insert(double v, int c, List *list) {
    node *new;
    List *aux;
    aux = list;
    new = (node*) malloc(sizeof(node));
    if(new == NULL) exit(0);
    if(aux->inicio->col == -1) {
        aux->inicio->value = v;
        aux->inicio->col = c;
        aux->inicio->next = NULL;
    } else {
        new->value = v;
        new->col = c;
        new->next = aux->fim->next;
        aux->fim->next = new;
        aux->fim = new;
    }
}

void somaPar(List **A,List **B,List **C,int n){
node* auxA;
node* auxB;
double sum;
#pragma omp parallel for private(auxA,auxB,sum)
for(int i=0;i<n;i++){
     auxA = A[i]->inicio;
     auxB = B[i]->inicio;
    if(auxA->col == -1){
        auxA = NULL;
    }
    if(auxB->col == -1){
        auxB = NULL;
    }
    while(auxA!=NULL && auxB!=NULL){
        
        sum = 0;
        if(auxA->col == auxB->col){
            
            sum = auxA->value + auxB->value;
            list_insert(sum,auxA->col,C[i]);
            auxA = auxA->next;
            auxB = auxB->next;
                 
        }
        else if(auxA->col < auxB->col){
            list_insert(auxA->value,auxA->col,C[i]);
            auxA = auxA->next;
        }
        else{
            list_insert(auxB->value,auxB->col,C[i]);
            auxB = auxB->next;
        }
    }
    while(auxA!= NULL){
        list_insert(auxA->value,auxA->col,C[i]);
        auxA = auxA->next;
    }
    while(auxB!=NULL){
        list_insert(auxB->value,auxB->col,C[i]);
        auxB = auxB->next;
    }
}
}

void list_print(node *list) {
    node *aux;
    aux = list;
    while(aux != NULL && aux->col != -1) {
        printf("value: %lf  col: %d\n", aux->value, aux->col);
        aux = aux->next;
    }

    printf("\n");
}

/* Descomente main para testar, 
comente main para usar a lista ligada em outros arquivos */

// int main() {
//     List *root;
//     root = (List*) malloc(sizeof(List));
//     list_init(root);
//     list_insert(5.4,1,root);
//     list_insert(0.4,5,root);
//     list_print(root->inicio);

//     List **list,**list2,**listRes;
//     int n = 10;
//     int i;
//     list = (List**) malloc(n * sizeof(List*));
//     list2 = (List**) malloc(n * sizeof(List*));
//     listRes = (List**) malloc(n * sizeof(List*));
//     for(i=0; i<n; i++) {
//        list[i] = (List*) malloc(sizeof(List));
//         list_init(list[i]);
//         list2[i] = (List*) malloc(sizeof(List));
//         list_init(list2[i]);
//         listRes[i] = (List*) malloc(sizeof(List));
//         list_init(listRes[i]);
//     }

//     list_insert(1.45, 5, list[3]);
//     list_insert(3.64, 10, list[3]);
//     list_insert(0.11, 60, list[3]);

//     list_insert(8.64, 9, list[1]);
//     list_insert(3.14, 20, list[1]);
//     list_insert(1.56, 49, list[1]);

//     list_insert(8.64, 9, list2[1]);
     
//     somaPar(list,list2,listRes,n);

//     list_print(listRes[3]->inicio);
    
//     list_print(listRes[1]->inicio);
    
//     return 0;
// }