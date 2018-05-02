#ifndef NSGA3_H_INCLUDED
#define NSGA3_H_INCLUDED

#include "Lite_Matrix.h"

typedef struct params{
    Matrix Zr;
    int nZr;
    Matrix zmin;
    Matrix zmax;
    Matrix smin;
}paramsBox,*paramsPtr;

typedef struct inputs{
    int nVar;    // Number of Decision Variables
    int nObj;    //Number of Objective Functions
    float* VarMin; //Lower Bound of Variables
    float* VarMax; //Upper Bound of Variables

    int nDivision; //Number of Reference Points

    int MaxIt; //Maximum Number of Iterations
    int nPop; //Population Size

    float pCrossover; //Crossover Percentage
    int nCrossover; //Number of Parnets (Offsprings)

    float pMutation; //Mutation Percentage
    int nMutation;//Number of Mutants
    float mu; //Mutation Rate
    float sigma; // Mutation Step Size
}inputBox,*inputPtr;

typedef struct individual{
    Matrix Position;
    Matrix Cost;
    Matrix Rank;
    Matrix DominationSet;
    Matrix DominatedCount;
    Matrix NormalizedCost;
    Matrix AssociatedRef;
    Matrix DistanceToAssociatedRef;
}individualBox,*individualPtr;

paramsBox param;
inputBox input;

void params_initalize();
void population_initalize(individualPtr *pop);

#endif // NSGA3_H_INCLUDED
