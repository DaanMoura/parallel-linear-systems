// Objetivo: resolver sistemas lineares de ordem n usando o 
// método Eliminação de Gauss

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int main(int argc, char* argv[])
{
  int i,j,k,n;
  double **A;
  double *X;
  double c, sum=0;
 
  // Verificando input
  if(argc != 2) {
    n = SIZE;
  } else {
    n = atoi(argv[1]);
  }
 
  // Alocando matriz A e vetor X
  A = (double**) malloc(n * sizeof(double*));
  for(i=0; i<n; i++){
    A[i] = (double*) malloc((n+1) * sizeof(double));
  }  
  X = (double*) malloc(n * sizeof(double));

  // Preenchendo X com zeros
  for(i=0; i<n; i++)
    X[i] = 0;

  srand(time(NULL));  

  // Preenchendo A com valores aleatórios entre 0 e 10
  for(i=0;i<n;i++) {
    for(j=0; j<n+1; j++) {
      A[i][j] = ((float) (rand()%100)) / 10; 
    }
  }

  // Visualização da Matriz Aumentada
  for(i=0;i<n;i++) {
    for(j=0; j<n+1; j++) {
      printf("%f\t", A[i][j]);
    }
    printf("\n");
  }

  // Geração da matriz triangular superior
  for(j=0;j<n;j++) {
    for(i=0;i<n;i++) {
      if(i>j){
        c=A[i][j]/A[j][j];
        for(k=0; k<n+1; k++){
          A[i][k] = A[i][k] - c*A[j][k];
        }
      }
    }
  }
  

  X[n-1] = A[n-1][n]/A[n-1][n-1];
  
  // Substituções
  for(i=n-1; i>=0; i--) {
    sum=0;
    for(j=i+1; j<n; j++) {
      sum = sum + A[i][j] * X[j];
    }
    X[i]=(A[i][n] - sum)/A[i][i];
  }

  printf("\n\nSolution:\n");
  for(i=0; i<n; i++){
    printf("x[%d]: %f\n", i, X[i]);
  }

  return 0;
}
