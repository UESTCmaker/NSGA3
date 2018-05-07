#ifndef SORT_POPULATION_H_INCLUDED
#define SORT_POPULATION_H_INCLUDED

#include "nsga3.h"

Matrix Find_HyperplaneIntercepts();
void Perform_Scalarizing(Matrix fp);
Matrix Scalarizing_Vector(int nObj, int j);
void Update_IdealPoint(individualPtr pop);
void Normalize_Population(individualPtr *pop);
FListPtr NonDominatedSorting(individualPtr *pop);
int dominates_Matrix(Matrix a,Matrix b);

#endif // SORT_POPULATION_H_INCLUDED
