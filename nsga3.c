#include <stdio.h>
#include <time.h>
#include <math.h>
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
        *(input.VarMin+i)=0.1;
        *(input.VarMax+i)=2.0;
    }

    input.nDivision = 10;

    input.MaxIt = 50;
    input.nPop_Old = 10;
    input.nPop = input.nPop_Old;
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
    srand(time(NULL));
    for(i = 0;i<input.nPop;i++){
        p->Position = zeros_Matrix(1, input.nVar);
        for(j=0;j<input.nVar;j++){
            *(*(p->Position.Box)+j) = random_Num(*(input.VarMax+j),*(input.VarMin+j));
        }
        p->Cost = Cost_Function(p->Position);
        p->DominationSet=NULL;
        p++;
    }
}


void crossover_population(individualPtr *popc, individualPtr pop){
    int k,i1=-1,i2=-1,nCross = input.nCrossover/2;
    individualPtr pc,p,p1,p2;
    Matrix alpha;
    *popc = (individualPtr)malloc(sizeof(individualBox)*input.nCrossover);
    pc = *popc;
    p = pop;
    printf("begin crossover!!!\n");
    for(k=0;k<nCross;k++){
        i1 = rand() % input.nPop;
        do{
            i2 = rand() % input.nPop;
        }while(i1 == i2);
        p1 = p + i1;
        p2 = p + i2;
        alpha = random_Matrix(1.0,0.0,1,input.nVar);
        pc->Position = plus_Matrix(multply_Array(alpha,p1->Position),multply_Array(minus_Matrix(ones_Matrix(alpha.row,alpha.col),alpha),p2->Position));
        pc->Cost = Cost_Function(pc->Position);
        pc++;
        pc->Position = plus_Matrix(multply_Array(alpha,p2->Position),multply_Array(minus_Matrix(ones_Matrix(alpha.row,alpha.col),alpha),p1->Position));
        pc->Cost = Cost_Function(pc->Position);
        pc++;
    }
}

void mutation_population(individualPtr *popm, individualPtr pop){
    int k,i,j,serial,nMu,flag[50]={0};
    individualPtr p,pm;
    nMu = (int)ceil(input.mu * input.nVar);
    *popm = (individualPtr)malloc(sizeof(individualBox)*input.nMutation);
    pm = *popm;
    printf("begin mutation!!!\n");
    for(k=0;k<input.nMutation;k++){
        i = rand() % input.nPop;
        p = pop + i;
        for(j=0;j<input.nVar;j++){
            flag[j]=0;
        }
        pm->Position = repmat_Matrix(p->Position,1,1);
        for(j=0;j<nMu;j++){
            serial = rand() % input.nVar;
            while(flag[serial]!=0){
                serial = rand() % input.nVar;
            }
            flag[serial]=1;
            *(*((pm->Position).Box)+serial) += input.sigma * (double)gaussrand();
        }
        pm->Cost = Cost_Function(pm->Position);
        pm++;
    }
}

void merge_population(individualPtr *pop, individualPtr *popc, individualPtr *popm){
    individualPtr p,q,newpop,popAr[3]={*pop,*popc,*popm};
    int j,i,last=0,nNewPop = input.nPop + input.nCrossover + input.nMutation;
    int num[3]={input.nPop,input.nCrossover,input.nMutation};
    newpop = (individualPtr)malloc(sizeof(individualBox)*nNewPop);
    printf("begin merge!!!  number:%d\n",nNewPop);
    for(j=0;j<3;j++){
        for(i=0;i<num[j];i++){
            (newpop+last+i)->Position = (popAr[j]+i)->Position;
            (newpop+last+i)->Cost = (popAr[j]+i)->Cost;
            (newpop+last+i)->DominationSet = NULL;
        }
        last+=i;
    }
    input.nPop += (input.nCrossover+input.nMutation);
    free(*pop);
    free(*popc);
    free(*popm);
    *pop = newpop;

    i=0;
    //p = newpop;
    while(newpop){
        i++;
        newpop++;
    }
    printf("newpop number after merge:%d\n",i);


    p=*pop;
    q = p;
    i=0;
    while(q){
        i++;
        q++;
    }
    printf("pop number after merge:%d\n",i);
}








