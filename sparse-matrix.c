#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked-list.c"
#include "matrix.c"

void print_sparse_matrix(node** matrix, int n) {
    int i;
    for(i=0;i<n;i++) {
        printf("row %d:\n", i);
        list_print(matrix[i]);
    }
}

int main(int argc, char* argv[])
{
    int i,j,k,n;
    double **matrix;
    char filename[30];
    node **M;

    if(argc!=2) {
        printf("Não passou o nome do arquivo\n");
        return -1;
    } else {
        strcpy(filename,argv[1]);
    }

    sscanf(filename,"matrices/%d",&n);
    printf("%d\n",n);

    matrix = (double**) malloc(n * sizeof(double*));
    for(i=0; i<n; i++) {
        matrix[i] = (double*) malloc((n+1) * sizeof(node));
    }

    read_matrix_file(matrix, n, filename);
    print_matrix(matrix, n);

    M = (node**) malloc(n * sizeof(node*));
    for(i=0; i<n; i++) {
        M[i] = (node*) malloc(sizeof(node));
        list_init(M[i]);
    }

    for(i=0;i<n;i++) {
        for(j=0;j<n+1;j++) {
            if(matrix[i][j] != 0) {
                list_insert(matrix[i][j], j, M[i]);
            }       
        }
    }

    print_sparse_matrix(M,n);

    return 0;
}
