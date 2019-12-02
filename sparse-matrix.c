#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
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
    List **M;

    struct timeval inic,fim;
    struct rusage r1, r2; 

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
        matrix[i] = (double*) malloc((n+1) * sizeof(double));
    }

    read_matrix_file(matrix, n, filename);
    // print_matrix(matrix, n);


    M = (List**) malloc(n * sizeof(List*));
    for(i=0; i<n; i++) {
        M[i] = (List*) malloc(sizeof(List));
        list_init(M[i]);
    }

    gettimeofday(&inic,0);
    getrusage(RUSAGE_SELF, &r1);

    for(i=0;i<n;i++) {
        for(j=0;j<n+1;j++) {
            if(matrix[i][j] != 0) {
                list_insert(matrix[i][j], j, M[i]);
            }       
        }
    }

    gettimeofday(&fim,0);
    getrusage(RUSAGE_SELF, &r2);

    printf("Sequencial:\nElapsed time:%f sec\nUser time:%f sec\nSystem time:%f sec\n\n",
		(fim.tv_sec + fim.tv_usec/1000000.) - (inic.tv_sec + inic.tv_usec/1000000.),
		(r2.ru_utime.tv_sec + r2.ru_utime.tv_usec/1000000.) - (r1.ru_utime.tv_sec + r1.ru_utime.tv_usec/1000000.),
		(r2.ru_stime.tv_sec + r2.ru_stime.tv_usec/1000000.) - (r1.ru_stime.tv_sec + r1.ru_stime.tv_usec/1000000.));

    // print_sparse_matrix(M,n);

    return 0;
}
