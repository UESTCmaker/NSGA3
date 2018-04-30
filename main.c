#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Lite_Matrix.h"

int main(){
    srand(time(NULL));

	Matrix M1=random_Matrix(1, 20, 1, 1);
	Matrix M2=random_Matrix(1, 20, 1, 1);
    print_Matrix(M1);
	print_Matrix(M2);
	print_Matrix(get_min_Matrix(M1,M2));
	//print_Matrix(infinity_Matrix(2,2));
	//print_Matrix(get_min_col_Matrix(M1));
	//print_Matrix(get_max_row_Matrix(M1));
	//print_Matrix(get_min_row_Matrix(M1));
/*

	Matrix M2=random_Matrix(1, 4, 2, 2);
	Matrix M3=inverse_Matrix(M1);
	print_Matrix(M3);

	Matrix M4=divide_Matrix(M2,M1);
	print_Matrix(M4);

    print_Matrix(M1);
    printf("Matrix num:%f\n",norm_Matrix(M1));
    print_Matrix(pow_array(M1,3));
*/
	return 0;
}
