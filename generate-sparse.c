#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "matrix.c"

void generate_sparse_matrix(double** matrix, int size, int n) {
    srand(time(NULL));
    int i,j;
    int a,b;
 
    for(i=0;i<n;i++) {
        for(j=0;j<n+1;j++) {
            matrix[i][j] = 0;
        }
    }

    for(i=0;i<n;i++) {
        a = rand() % size;
        b = rand() % size;
        matrix[a][b] = ((double) (rand()%100)) / 10;
    }
}

int main(int argc, char* argv[])
{
    double **matrix;
    char filename[30];
    int size,i,n;
    
    strcpy(filename,argv[1]);
    size = atoi(argv[2]);
    n = atoi(argv[3]);

    matrix = (double**) malloc(size * sizeof(double*));
    for(i=0; i<size; i++) {
        matrix[i] = (double*) malloc((size+1) * sizeof(double));
    }

    generate_sparse_matrix(matrix,size,n);
    write_matrix_file(matrix,size,filename);

    return 0;
}