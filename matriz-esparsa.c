#include <stdlib.h>
#include <stdio.h>
struct MatEsparsa{
    //a matriz em si
    double ** dados;
    //a dimensão da matriz
    int row,col;
    //numero de elementos
    int tam;

};

void inicializarMatEsparsa(int row,int col,struct MatEsparsa* mat){
    mat->row = row;
    mat->col = col;
    mat->tam = 0;
    int max = row*col;
    // max é o número máximo de elementos que a matriz suportará;
    mat->dados = (double **)malloc(3 * sizeof(double*));
    for(int i = 0;i<3;i++){
        mat->dados[i] = (double*)malloc(max*sizeof(double));
    }
}
void desalocaMatEsparsa(struct MatEsparsa*mat){
    for(int i=0;i<(mat->tam);i++)
        free(mat->dados[i]);
    free(mat->dados);
}

void insereMatEsparsa(int row,int col,float val,struct MatEsparsa *mat){
    mat->dados[0][mat->tam] = row;
    mat->dados[1][mat->tam] = col;
    mat->dados[2][mat->tam] = val;
    mat->tam++;
}

void somaMatEsparsa(struct MatEsparsa *A,struct MatEsparsa *B,struct MatEsparsa *C ){
    int aPos=0,bPos=0;
    while(aPos < A->tam && bPos < B->tam){
        if(A->dados[0][aPos] > B->dados[0][bPos] || ( (A->dados[0][aPos] == B->dados[0][bPos]) && A->dados[1][aPos] > B->dados[1][bPos])){
            insereMatEsparsa(B->dados[0][bPos],B->dados[1][bPos],B->dados[2][bPos],C);
            bPos++;
        }
        else if(A->dados[0][aPos] < B->dados[0][bPos] || ( (A->dados[0][aPos] == B->dados[0][bPos]) && A->dados[1][aPos] < B->dados[1][bPos])){
            insereMatEsparsa(A->dados[0][aPos],A->dados[1][aPos],A->dados[2][aPos],C);
            aPos++;
    }
    else{
        printf("teste\n");
        int add = A->dados[2][aPos] + B->dados[2][bPos];
        if(add){
            insereMatEsparsa(A->dados[0][aPos],A->dados[0][aPos],add,C);
        }
        aPos++;
        bPos++;
    }
    }
    for(aPos;aPos<A->tam;aPos++){
        insereMatEsparsa(A->dados[0][aPos],A->dados[1][aPos],A->dados[2][aPos],C);
    }
    for(bPos;bPos<B->tam;bPos++){
        insereMatEsparsa(B->dados[0][bPos],B->dados[1][bPos],B->dados[2][bPos],C);
    }
    
}



int main(){
struct MatEsparsa mat,mat2,matRes;

inicializarMatEsparsa(3,4,&mat);
inicializarMatEsparsa(3,4,&mat2);
inicializarMatEsparsa(3,4,&matRes);

insereMatEsparsa(0,3,23.3,&mat);
insereMatEsparsa(1,2,32.25,&mat);
insereMatEsparsa(1,2,5,&mat2);
insereMatEsparsa(2,3,15,&mat2);

somaMatEsparsa(&mat,&mat2,&matRes);

printf("teste:\nnúmero de linhas:%d\nnúmero de colunas:%d\nnúmero de elementos:%d\n",mat.row,mat.col,mat.tam);
for(int i = 0;i<matRes.tam;i++){
printf("elemento %d de mat:\nlin:%f\ncol:%f\nval:%f\n",i,matRes.dados[0][i],matRes.dados[1][i],matRes.dados[2][i]);

}
desalocaMatEsparsa(&mat);
return 0;
}