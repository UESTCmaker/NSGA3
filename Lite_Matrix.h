#ifndef LITE_MATRIX_H_INCLUDED
#define LITE_MATRIX_H_INCLUDED

#include "Lite_List.h"

#define MIN -3.40E+38
#define MAX +3.40E+38
#define PI 3.141592654

typedef struct Matrix{
	float** Box;
	int row;
	int col;
}Matrix,*MatrixPtr;

double gaussrand();
int round_Num(float num);
int element_Num(Matrix M1);
float random_Num(float maxNum,float minNum);

ListPtr get_min_col_NumList(Matrix a);

Matrix* get_max_col_Matrix(Matrix a);
Matrix* get_min_col_Matrix(Matrix a);
Matrix* get_max_row_Matrix(Matrix a);
Matrix* get_min_row_Matrix(Matrix a);

Matrix get_max_Matrix(Matrix a, Matrix b);
Matrix get_min_Matrix(Matrix a, Matrix b);

Matrix zeros_Matrix(int row, int col);
Matrix ones_Matrix(int row, int col);
Matrix infinity_Matrix(int row, int col);
Matrix somes_Matrix(float num, int row, int col);
Matrix random_Matrix(float VarMax, float VarMin, int row, int col);

Matrix pow_Array(Matrix a,int times);
Matrix divide_Array(Matrix a,Matrix b);
Matrix multply_Array(Matrix a,Matrix b);

int all_flag_Matrix(Matrix a, Matrix b, int flag);
int any_flag_Matrix(Matrix a, Matrix b, int flag);

Matrix get_col_Matrix(Matrix a, int col);
Matrix get_row_Matrix(Matrix a, int row);

Matrix sum_col_Matrix(Matrix a);
Matrix sum_row_Matrix(Matrix a);

Matrix repmat_Matrix(Matrix a, int row, int col);

float sum_Matrix(Matrix a);
float norm_Matrix(Matrix a);
Matrix pow_Matrix(Matrix a, int times);
Matrix trans_Matrix(Matrix a);
Matrix inverse_Matrix(Matrix a);
Matrix plus_Matrix(Matrix a, Matrix b);
Matrix minus_Matrix(Matrix a, Matrix b);
Matrix multply_Matrix(Matrix a, Matrix b);
Matrix divide_Matrix(Matrix a, Matrix b);

void delete_Matrix(Matrix *a);
void print_Matrix(Matrix M1);

#endif // LITE_MATRIX_H_INCLUDED
