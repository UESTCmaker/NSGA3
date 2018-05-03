#include <stdio.h>
#include <malloc.h>
#include "Cost_Function.h"
#include "Reference_Points.h"
#include "nsga3.h"

void params_initalize(){
    int i;
    input.nVar = 5;
    input.nObj = 2;
    input.VarMin =(float*)malloc(sizeof(float)*input.nVar);
    input.VarMax =(float*)malloc(sizeof(float)*input.nVar);
    for(i=0;i<input.nVar;i++){
        *(input.VarMin+i)=-1.0;
        *(input.VarMax+i)=1.0;
    }

    input.nDivision = 10;

    input.MaxIt = 50;
    input.nPop = 10;
    input.pCrossover = 0.5;
    input.nCrossover = 2*round_Num(input.pCrossover*input.nPop/2);
    input.pMutation = 0.5;
    input.nMutation = round_Num(input.pMutation*input.nPop);
    input.mu = 0.02;
    input.sigma = 0.1*(*input.VarMax-*input.VarMin);

    param.Zr = Generate_Points(input.nObj, input.nDivision);
    param.nZr = param.Zr.col;
}


void population_initalize(individualPtr *pop){
    int i,j;
    individualPtr p;
    *pop = (individualPtr)malloc(sizeof(individualBox)*input.nPop);
    p = *pop;
    for(i = 0;i<input.nPop;i++){
        p->Position = zeros_Matrix(1, input.nVar);
        for(j=0;j<input.nVar;j++){
            *(*(p->Position.Box)+j) = random_Num(*(input.VarMax+j),*(input.VarMin+j));
        }
        p->Cost = cost_Function(p->Position);
        p++;
    }
}


