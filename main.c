#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Cost_Function.h"
#include "Lite_Matrix.h"
#include "nsga3.h"

int main(){
    srand(time(NULL));
	print_Matrix(cost_Function(random_Matrix(VarMin, VarMax, 1, nVar)));
	return 0;
}
