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
    params_initalize();
    population_initalize(&pop);
    F = Sort_Population(&pop);
	return 0;
}
