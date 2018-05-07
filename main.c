#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Cost_Function.h"
#include "Reference_Points.h"
#include "Sort_Population.h"
#include "Lite_Matrix.h"
#include "Lite_List.h"
#include "nsga3.h"

int main(){

    individualPtr pop=NULL;
    FListPtr F;
    srand(time(NULL));
    params_initalize();
    population_initalize(&pop);
    Normalize_Population(&pop);
    F = NonDominatedSorting(&pop);
    while(F){
        printf("Rank:%d  Number Set:\t",F->Rank);
        print_List(F->dataList);
        printf("\n");
        F=F->pNext;
    }
	return 0;
}
