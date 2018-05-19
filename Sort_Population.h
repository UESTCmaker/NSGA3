#ifndef SORT_POPULATION_H_INCLUDED
#define SORT_POPULATION_H_INCLUDED

#include "nsga3.h"

Matrix Find_HyperplaneIntercepts();
void Perform_Scalarizing(Matrix fp);
Matrix Scalarizing_Vector(int nObj, int j);
void Update_IdealPoint(individualPtr *pop);

void  Update_Population(individualPtr* pop, ListPtr newpop);
FListPtr Sort_Population(individualPtr *pop);
void Normalize_Population(individualPtr *pop);
FListPtr NonDominated_Sorting(individualPtr *pop);
int dominates_Matrix(Matrix a,Matrix b);
Matrix* Associate_ReferencePoint(individualPtr *pop);


#endif // SORT_POPULATION_H_INCLUDED
