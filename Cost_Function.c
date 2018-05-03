#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "Cost_Function.h"
#include "Lite_Matrix.h"

Matrix cost_Function(Matrix a){
     int n = element_Num(a);
     Matrix ones = ones_Matrix(a.row,a.col);
     Matrix temp1 = sum_row_Matrix(pow_array(divide_array(minus_Matrix(a,ones),somes_Matrix(sqrt(n),a.row,a.col)),2));
     Matrix temp2 = sum_row_Matrix(pow_array(divide_array(plus_Matrix(a,ones),somes_Matrix(sqrt(n),a.row,a.col)),2));

    float z1=1-exp(- **temp1.Box);
    float z2=1+exp(- **temp2.Box);
    float z3=2-exp(- **temp2.Box);

    Matrix z;
    int i;

    z.col=1;
    z.row=3;
    z.Box = (float**)malloc(sizeof(float*)*z.row);
    for(i=0;i<z.row;i++){
        *(z.Box+i)=(float*)malloc(sizeof(float)*z.col);
    }

    *(*(z.Box+0)+z.col-1)=z1;
    *(*(z.Box+1)+z.col-1)=z2;
    *(*(z.Box+2)+z.col-1)=z3;

    return z;
}
