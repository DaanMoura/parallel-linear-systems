// Objetivo: resolver sistemas lineares de ordem n usando o 
// método Eliminação de Gauss

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <xmmintrin.h>
#include <sys/resource.h>
#include <sys/time.h>
#define SIZE 2000

int main(int argc, char* argv[])
{
  int i,j,k,n;
  double **A;
  double *X;
  double c, sum=0;
 
  struct timeval inic,fim;
  struct rusage r1, r2; 
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
 /*
  // Visualização da Matriz Aumentada
  for(i=0;i<n;i++) {
    for(j=0; j<n+1; j++) {
      printf("%f\t", A[i][j]);
    }
    printf("\n");
  }

  
*/

gettimeofday(&inic,0);
getrusage(RUSAGE_SELF, &r1);
  // Geração da matriz triangular superior
  for(j=0;j<n;j++) {
      #pragma omp parallel for private(k)
    for(i=0;i<n;i++) {
        if(i != j){
        c=A[i][j]/A[j][j];
        #pragma GCC ivdep
        for(k=0; k<n+1; k++){
          A[i][k] = A[i][k] - c*A[j][k];
        }
        }
    }
  }
  #pragma opm parallel for
  for(j=0;j<n;j++){
      X[j] = A[j][n]/A[j][j];
  }
  gettimeofday(&fim,0);
  getrusage(RUSAGE_SELF, &r2);
/*
  X[n-1] = A[n-1][n]/A[n-1][n-1];
  
  // Substituções
  for(i=n-1; i>=0; i--) {
    sum=0;
    for(j=i+1; j<n; j++) {
      sum = sum + A[i][j] * X[j];
    }
    X[i]=(A[i][n] - sum)/A[i][i];
  }
  */

  /*
  //imprimir
  printf("\n\nSolution:\n");
  for(i=0; i<n; i++){
    printf("x[%d]: %f\n", i, X[i]);
  }
 */

printf("paralelo sem substituição:\nElapsed time:%f sec\nUser time:%f sec\nSystem time:%f sec\n\n",
		(fim.tv_sec + fim.tv_usec/1000000.) - (inic.tv_sec + inic.tv_usec/1000000.),
		(r2.ru_utime.tv_sec + r2.ru_utime.tv_usec/1000000.) - (r1.ru_utime.tv_sec + r1.ru_utime.tv_usec/1000000.),
		(r2.ru_stime.tv_sec + r2.ru_stime.tv_usec/1000000.) - (r1.ru_stime.tv_sec + r1.ru_stime.tv_usec/1000000.));

gettimeofday(&inic,0);
getrusage(RUSAGE_SELF, &r1);
  // Geração da matriz triangular superior
  for(j=0;j<n;j++) {
    for(i=j+1;i<n;i++) {
        c=A[i][j]/A[j][j];
        for(k=0; k<n+1; k++){
          A[i][k] = A[i][k] - c*A[j][k];
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
   gettimeofday(&fim,0);
  getrusage(RUSAGE_SELF, &r2);

printf("sequencial:\nElapsed time:%f sec\nUser time:%f sec\nSystem time:%f sec\n\n",
		(fim.tv_sec + fim.tv_usec/1000000.) - (inic.tv_sec + inic.tv_usec/1000000.),
		(r2.ru_utime.tv_sec + r2.ru_utime.tv_usec/1000000.) - (r1.ru_utime.tv_sec + r1.ru_utime.tv_usec/1000000.),
		(r2.ru_stime.tv_sec + r2.ru_stime.tv_usec/1000000.) - (r1.ru_stime.tv_sec + r1.ru_stime.tv_usec/1000000.));

gettimeofday(&inic,0);
getrusage(RUSAGE_SELF, &r1);
// Geração da matriz triangular superior
  for(j=0;j<n;j++) {
      #pragma omp parallel for private(k)
    for(i=j+1;i<n;i++) {
        c=A[i][j]/A[j][j];
        #pragma GCC ivdep
        for(k=0; k<n+1; k++){
          A[i][k] = A[i][k] - c*A[j][k];
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

    gettimeofday(&fim,0);
  getrusage(RUSAGE_SELF, &r2);

printf("paralelo com substituição(trecho sequencial):\nElapsed time:%f sec\nUser time:%f sec\nSystem time:%f sec\n\n",
		(fim.tv_sec + fim.tv_usec/1000000.) - (inic.tv_sec + inic.tv_usec/1000000.),
		(r2.ru_utime.tv_sec + r2.ru_utime.tv_usec/1000000.) - (r1.ru_utime.tv_sec + r1.ru_utime.tv_usec/1000000.),
		(r2.ru_stime.tv_sec + r2.ru_stime.tv_usec/1000000.) - (r1.ru_stime.tv_sec + r1.ru_stime.tv_usec/1000000.));
  double diferenca;
  int correto = 1;
  //verificar solução
  for(i=0;i<n;i++){
    sum = 0;
     for(j=0;j<n;j++){
       sum += A[i][j] * X[j];
     }
     diferenca = fabs(sum - A[i][n]);
     //comparação  com o operador == costuma não  funcionar devido a erros de arredondamento
     if(diferenca > 0.0001){
       correto = 0;     
       printf("\nerro!:diferença entre valor calculado:%f e valor esperado:%f é ",sum,A[i][n],diferenca);
     }

  }
  if(correto){
  printf("\nOs valores encontrados estão corretos!");
  }
  return 0;
}
