#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <math.h>

#define SIZE  2000
#define MAX_ITER  1000
int main(int argc, char* argv[]){
    int convergencia = 0;
    int diagonal_dominante = 0;
    int i,j,k,n;
    double sum,diagonal,diferenca;
    int correto;
    struct timeval inic,fim;
    struct rusage r1, r2; 

    double **A;
    double *X;
     if(argc != 2) {
    n = SIZE;
  } else {
    n = atoi(argv[1]);
  }
 
    //alocar matriz A e vetor X
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
  while(!diagonal_dominante){
  for(i=0;i<n;i++) {
    for(j=0; j<n+1; j++) {
      A[i][j] = ((float) (rand()%100)) / 10;
      if(i == j){
          A[i][i] = A[i][i] * (n*n*n);//tentar tornar a matriz diagonal dominante
      } 
    }
  }
    //Checando convergência;
#pragma omp parallel for private(j,sum,diagonal)
for(i=0;i<n;i++){
    sum = 0;
    for(j=0;j<n;j++){
        if(j!=i){
            sum += fabs(A[i][j]);
        }
        else{
            diagonal = fabs(A[i][i]);
        }
    }
//    printf("soma linha %d: %f\n",i,sum);
  //  printf("diagonal linha %d: %f\n",i,diagonal);
    if(diagonal < sum){
        diagonal_dominante = 0;
    }
    else{
        diagonal_dominante = 1;
    }
}

  }
gettimeofday(&inic,0);
getrusage(RUSAGE_SELF, &r1);

if(diagonal_dominante){
    printf("A matriz converge\n");
}
else{
    printf("Não se pode provar que a matriz converge");
}

if(diagonal_dominante){
  //Método de Jacobi
  for(k=0;k<MAX_ITER;k++){
  #pragma omp parallel for private(sum,j)
    for(i=0;i<n;i++){
        sum = 0;
        for(j=0;j<n;j++){
            if(j!= i){
            sum += A[i][j] * X[i]; 
            }
            else{
            diagonal = A[j][j];    
            }    
        }
    X[i] = (A[i][n] - sum)/diagonal;
    }
  }
  gettimeofday(&fim,0);
  getrusage(RUSAGE_SELF, &r2);

  printf("paralelo:\nElapsed time:%f sec\nUser time:%f sec\nSystem time:%f sec\n\n",
		(fim.tv_sec + fim.tv_usec/1000000.) - (inic.tv_sec + inic.tv_usec/1000000.),
		(r2.ru_utime.tv_sec + r2.ru_utime.tv_usec/1000000.) - (r1.ru_utime.tv_sec + r1.ru_utime.tv_usec/1000000.),
		(r2.ru_stime.tv_sec + r2.ru_stime.tv_usec/1000000.) - (r1.ru_stime.tv_sec + r1.ru_stime.tv_usec/1000000.));

  //imprime resposta
   for(i=0;i<n;i++){
    sum = 0;
     for(j=0;j<n;j++){
       sum += A[i][j] * X[j];
     }
     diferenca = fabs(sum - A[i][n]);
     //comparação  com o operador == costuma não  funcionar devido a erros de arredondamento
     if(diferenca > 0.1){
       correto = 0;     
       printf("erro no paralelo!:diferença entre valor calculado:%f e valor esperado:%f é %f ",sum,A[i][n],diferenca);
       break;
     }

  }
}

//sequencial


gettimeofday(&inic,0);
getrusage(RUSAGE_SELF, &r1);

if(diagonal_dominante){
    printf("A matriz converge\n");
}
else{
    printf("Não se pode provar que a matriz converge");
}

if(diagonal_dominante){
  //Método de Jacobi
  for(k=0;k<MAX_ITER;k++){
    for(i=0;i<n;i++){
        sum = 0;
        for(j=0;j<n;j++){
            if(j!= i){
            sum += A[i][j] * X[i]; 
            }
            else{
            diagonal = A[j][j];    
            }    
        }
    X[i] = (A[i][n] - sum)/diagonal;
    }
  }
  gettimeofday(&fim,0);
  getrusage(RUSAGE_SELF, &r2);

  printf("sequencial:\nElapsed time:%f sec\nUser time:%f sec\nSystem time:%f sec\n\n",
		(fim.tv_sec + fim.tv_usec/1000000.) - (inic.tv_sec + inic.tv_usec/1000000.),
		(r2.ru_utime.tv_sec + r2.ru_utime.tv_usec/1000000.) - (r1.ru_utime.tv_sec + r1.ru_utime.tv_usec/1000000.),
		(r2.ru_stime.tv_sec + r2.ru_stime.tv_usec/1000000.) - (r1.ru_stime.tv_sec + r1.ru_stime.tv_usec/1000000.));

  //imprime resposta
   for(i=0;i<n;i++){
    sum = 0;
     for(j=0;j<n;j++){
       sum += A[i][j] * X[j];
     }
     diferenca = fabs(sum - A[i][n]);
     //comparação  com o operador == costuma não  funcionar devido a erros de arredondamento
     if(diferenca > 0.1){
       correto = 0;     
       printf("erro no sequencial!:diferença entre valor calculado:%f e valor esperado:%f é %f ",sum,A[i][n],diferenca);
       break;
     }

  }
}
    return 0;
}