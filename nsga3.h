#ifndef NSGA3_H_INCLUDED
#define NSGA3_H_INCLUDED

#include "Lite_Matrix.h"

typedef struct params{
    Matrix* Zr;
    int nZr;
    Matrix* zmin;
    Matrix* zmax;
    Matrix* smin;
}paramsBox,*paramsPtr;

/*
params.nPop = nPop;
params.Zr = Zr;
params.nZr = size(Zr,2);
*/

typedef struct individual{
    Matrix* Position;
    Matrix* Cost;
    Matrix* Rank;
    Matrix* DominationSet;
    Matrix* DominatedCount;
    Matrix* NormalizedCost;
    Matrix* AssociatedRef;
    Matrix* DistanceToAssociatedRef;
}individualBox,*individualPtr;

const static int nVar = 5;    // Number of Decision Variables
const static float VarMin = -1.0; //Lower Bound of Variables
const static float VarMax =  1.0; //Upper Bound of Variables

const static int nDivision = 10; //Number of Reference Points

const static int MaxIt = 50; //Maximum Number of Iterations
const static int nPop = 80; //Population Size

const static float pCrossover = 0.5; //Crossover Percentage
const int nCrossover = 2*round_Num(pCrossover*nPop/2); //Number of Parnets (Offsprings)

const static float pMutation = 0.5; //Mutation Percentage
const int nMutation round_Num(pMutation*nPop);////Number of Mutants
const static float mu = 0.02; //Mutation Rate
const float sigma = 0.1*(VarMax-VarMin); // Mutation Step Size


% Number of Objective Functions
nObj = numel(CostFunction(unifrnd(VarMin, VarMax, 1, nVar)));

Zr = GenerateReferencePoints(nObj, nDivision);

#endif // NSGA3_H_INCLUDED
