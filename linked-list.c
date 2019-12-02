#include <stdio.h>
#include <stdlib.h>

struct Node {
    double value;
    int col;
    struct Node *next;
};

typedef struct Node node;

void list_init(node *list) {
    list->next = NULL;
    list->col = -1;
}

void list_insert(double v, int c, node *list) {
    node *new, *aux;
    aux = list;
    new = (node*) malloc(sizeof(node));
    if(new == NULL) exit(0);
    if(aux->col == -1) {
        aux->value = v;
        aux->col = c;
        aux->next = NULL;
    } else {
        new->value = v;
        new->col = c;
        new->next = aux->next;
        aux->next = new;
    }
}

void list_print(node *list) {
    node *aux;
    aux = list;
    while(aux != NULL) {
        printf("value: %lf  col: %d\n", aux->value, aux->col);
        aux = aux->next;
    }

    printf("\n");
}

int main() {
    node *root;
    root = (node*) malloc(sizeof(node));
    list_init(root);
    list_insert(5.4,1,root);
    list_insert(0.4,5,root);
    list_print(root);

    node **list;
    int n = 10;
    int i;
    list = (node**) malloc(n * sizeof(node*));
    for(i=0; i<n; i++) {
        list[i] = (node*) malloc(sizeof(node));
        list_init(list[i]);
    }

    list_insert(1.45, 5, list[3]);
    list_insert(3.64, 10, list[3]);
    list_insert(0.11, 60, list[3]);

    list_insert(8.64, 9, list[1]);
    list_insert(3.14, 20, list[1]);
    list_insert(1.56, 49, list[1]);

    list_print(list[3]);
    
    list_print(list[1]);
    
    return 0;
}