#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void generate_matrix(double** matrix, int n) {
  int i,j;
  for(i=0;i<n;i++) {
    for(j=0; j<n+1; j++) {
      if(i==j) {
        matrix[i][j] = ((double) (rand()%1000)) / 10;
      } else {
        matrix[i][j] = ((double) (rand()%100)) / 10;
      }
    }
  }
}

void print_matrix(double** matrix, int n) {
  int i,j;
  for(i=0;i<n;i++) {
    for(j=0; j<n+1; j++) {
      printf("%.2f\t", matrix[i][j]);
    }
    printf("\n");
  }
}

void write_matrix_file(double** matrix, int n, char* filename) {
  int i,j;
  
  FILE *f; 
  f = fopen(filename, "w");
  if(f == NULL) {
    printf("Erro ao abrir arquivo!\n");
    return;
  }

  for(i=0;i<n;i++) {
    for(j=0; j<n+1; j++) {
      fprintf(f,"%.2f ", matrix[i][j]);
    }
    fprintf(f,"\n");
  }

  fclose(f);
}

void read_matrix_file(double** matrix, int n, char* filename) {
  int i,j;
  double temp;

  FILE *f;
  f = fopen(filename, "r");
  if(f == NULL) {
    printf("Erro ao abrir arquivo!\n");
    return;
  }

  for(i=0;i<n;i++) {
    for(j=0; j<n+1;j++) {
      fscanf(f,"%lf",&temp);
      matrix[i][j] = temp;
    }
  }

  fclose(f);  
}

void print_vector(double* vector, int n) {
  int i;
  for(i=0;i<n;i++) {
    printf("#%d %.2f\n", i, vector[i]);
  }
}

// int main() {
//   int i,j,n;
//   char filename[30];
//   double **M;

//   n = 5;

//   M = (double**) malloc(n * sizeof(double*));
//   for(i=0; i<n; i++) {
//     M[i] = (double*) malloc((n+1) * sizeof(double));
//   }

//   for(i=0;i<10;i++) {
//     sprintf(filename,"matrices/5-%d.txt",i);
//     generate_matrix(M,n);
//     write_matrix_file(M,n,filename);
//   }

//   for(i=1;i<10;i++) {
//     n = 10 * i;
//     M = (double**) malloc(n * sizeof(double*));
//     for(j=0; j<n; j++) {
//       M[j] = (double*) malloc((n+1) * sizeof(double));
//     }
//     for(j=0; j<10;j++) {
//       sprintf(filename,"matrices/%d-%d.txt",n,j);
//       generate_matrix(M,n);
//       write_matrix_file(M,n,filename);
//     }
//   }

//   for(i=1;i<10;i++) {
//     n = 100 * i;
//     M = (double**) malloc(n * sizeof(double*));
//     for(j=0; j<n; j++) {
//       M[j] = (double*) malloc((n+1) * sizeof(double));
//     }
//     for(j=0; j<10;j++) {
//       sprintf(filename,"matrices/%d-%d.txt",n,j);
//       generate_matrix(M,n);
//       write_matrix_file(M,n,filename);
//     }
//   }

//   return 0;
// }