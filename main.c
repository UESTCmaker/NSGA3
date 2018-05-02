#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Cost_Function.h"
#include "Reference_Points.h"
#include "Lite_Matrix.h"
#include "nsga3.h"

int main(){
    int i;
    individualPtr pop=NULL;
    srand(time(NULL));
    params_initalize();
    population_initalize(&pop);
    for(i=0;i<input.nPop;i++){
        print_Matrix(pop->Position);
        pop++;
    }

	return 0;
}
