#ifndef SORT_POPULATION_H_INCLUDED
#define SORT_POPULATION_H_INCLUDED

#include "nsga3.h"

void Normalize_Population(individualPtr *pop);
Matrix Find_HyperplaneIntercepts();
void Perform_Scalarizing(Matrix fp);
Matrix Scalarizing_Vector(int nObj, int j);
void Update_IdealPoint(individualPtr pop);
void Normalize_Population(individualPtr *pop);

#endif // SORT_POPULATION_H_INCLUDED
