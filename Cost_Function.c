#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "Cost_Function.h"
#include "Lite_Matrix.h"

#define Pi 3.14159

Matrix Cost_Function(Matrix a)
{
    int n = element_Num(a);
    Matrix ones = ones_Matrix(a.row,a.col);
    Matrix temp1 = sum_row_Matrix(pow_Array(minus_Matrix(a,somes_Matrix(1.0/sqrt(n),a.row,a.col)),2));
    Matrix temp2 = sum_row_Matrix(pow_Array(plus_Matrix(a,somes_Matrix(1.0/sqrt(n),a.row,a.col)),2));
    //Matrix temp3 = sum_row_Matrix(pow_Array(a,2));

    float z1=1.0-exp(- **temp1.Box);
    float z2=1.0-exp(- **temp2.Box);
    //float z3=1.0+exp(-sin(2*Pi*z1)-cos(2*Pi*z2));

    Matrix z;
    int i;

    z.col=1;
    z.row=2;
    z.Box = (float**)malloc(sizeof(float*)*z.row);
    for(i=0; i<z.row; i++)
    {
        *(z.Box+i)=(float*)malloc(sizeof(float)*z.col);
    }

    *(*(z.Box+0)+z.col-1)=z1;
    *(*(z.Box+1)+z.col-1)=z2;
    //*(*(z.Box+2)+z.col-1)=z3;

    return z;
}
