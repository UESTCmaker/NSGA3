#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Lite_Matrix.h"

//浮点数四舍五入运算
int round_Num(float num){
    if( (ceil(num)-num) <= (num-floor(num)) ){
        return ceil(num);
    }
    else{
        return floor(num);
    }
}

//产生正态分布随机数
double gaussrand(){
    static double U, V;
    static int phase = 0;
    double Z;

    if(phase == 0)
    {
         U = rand() / (RAND_MAX + 1.0);
         V = rand() / (RAND_MAX + 1.0);
         Z = sqrt(-2.0 * log(U))* sin(2.0 * PI * V);
    }
    else
    {
         Z = sqrt(-2.0 * log(U)) * cos(2.0 * PI * V);
    }

    phase = 1 - phase;
    return Z;
}

//限定范围的随机均匀分布浮点数生成器
float random_Num(float maxNum,float minNum){
	float randnum;
	float interval= maxNum-minNum+1;
	do{
        randnum=fmodf((float)rand(),interval)+minNum+0.00001;
	}while(randnum>maxNum || randnum<minNum);
	return randnum;
}


//随机初始化矩阵
Matrix random_Matrix(float VarMax, float VarMin, int row, int col){
	Matrix M1;
	int i,j;
	M1.Box = (float**)malloc(sizeof(float*)*row);
	M1.col=col;
	M1.row=row;
	for(i=0;i<row;i++){
		*(M1.Box+i)=(float*)malloc(sizeof(float)*col);
		for(j=0;j<col;j++){
			*(*(M1.Box+i)+j)=random_Num(VarMax,VarMin);
		}
	}
	return M1;
}

Matrix zeros_Matrix(int row, int col){
    Matrix M1;
	int i,j;
	M1.Box = (float**)malloc(sizeof(float*)*row);
	M1.col=col;
	M1.row=row;
	for(i=0;i<row;i++){
		*(M1.Box+i)=(float*)malloc(sizeof(float)*col);
		for(j=0;j<col;j++){
			*(*(M1.Box+i)+j)=0.0;
		}
	}
	return M1;
}

Matrix ones_Matrix(int row, int col){
    Matrix M1;
	int i,j;
	M1.Box = (float**)malloc(sizeof(float*)*row);
	M1.col=col;
	M1.row=row;
	for(i=0;i<row;i++){
		*(M1.Box+i)=(float*)malloc(sizeof(float)*col);
		for(j=0;j<col;j++){
			*(*(M1.Box+i)+j)=1.0;
		}
	}
	return M1;
}

Matrix somes_Matrix(float num, int row, int col){
    Matrix M1;
	int i,j;
	M1.Box = (float**)malloc(sizeof(float*)*row);
	M1.col=col;
	M1.row=row;
	for(i=0;i<row;i++){
		*(M1.Box+i)=(float*)malloc(sizeof(float)*col);
		for(j=0;j<col;j++){
			*(*(M1.Box+i)+j)=num;
		}
	}
	return M1;
}

Matrix infinity_Matrix(int row, int col){
    Matrix M1;
	int i,j;
	M1.Box = (float**)malloc(sizeof(float*)*row);
	M1.col=col;
	M1.row=row;
	for(i=0;i<row;i++){
		*(M1.Box+i)=(float*)malloc(sizeof(float)*col);
		for(j=0;j<col;j++){
			*(*(M1.Box+i)+j)=MAX;
		}
	}
	return M1;
}

//求矩阵元素个数
int element_Num(Matrix M1){
	return M1.col*M1.row;
}

//销毁矩阵(有问题)
void delete_Matrix(Matrix *a){
    int i;
    Matrix b=*a;
    //释放一维数组指针
    for(i=b.row-1;i>0;i--){
        free(*(b.Box+i));
    }
    free(b.Box);
    b.col=0;
    b.row=0;
}

int all_flag_Matrix(Matrix a, Matrix b, int flag){
    int i,j;
    int result=1;
    if(a.col==b.col && a.row==b.row){
        for(i=0;i<a.row;i++){
            for(j=0;j<a.col;j++){
                switch(flag){
                    //大于
                    case 1:
                        if( *(*(a.Box+i)+j) <= *(*(b.Box+i)+j) ){
                            result=0;
                            return result;
                        }
                        break;
                    //大于等于
                    case 10:
                        if( *(*(a.Box+i)+j) < *(*(b.Box+i)+j) ){
                            result=0;
                            return result;
                        }
                        break;
                    //小于
                    case -1:
                        if( *(*(a.Box+i)+j) >= *(*(b.Box+i)+j) ){
                            result=0;
                            return result;
                        }
                        break;
                    //小于等于
                    case -10:
                        if( *(*(a.Box+i)+j) > *(*(b.Box+i)+j) ){
                            result=0;
                            return result;
                        }
                        break;
                }

            }
        }
        return result;
    }
    else{
        printf("Error: wrong matrix compare operation.\n");
        exit(-1);
    }
}

int any_flag_Matrix(Matrix a, Matrix b, int flag){
    int i,j;
    int result=0;
    if(a.col==b.col && a.row==b.row){
        for(i=0;i<a.row;i++){
            for(j=0;j<a.col;j++){
                switch(flag){
                    //大于
                    case 1:
                        if( *(*(a.Box+i)+j) > *(*(b.Box+i)+j) ){
                            result=1;
                            return result;
                        }
                        break;
                    //大于等于
                    case 10:
                        if( *(*(a.Box+i)+j) >= *(*(b.Box+i)+j) ){
                            result=1;
                            return result;
                        }
                        break;
                    //小于
                    case -1:
                        if( *(*(a.Box+i)+j) < *(*(b.Box+i)+j) ){
                            result=1;
                            return result;
                        }
                        break;
                    //小于等于
                    case -10:
                        if( *(*(a.Box+i)+j) <= *(*(b.Box+i)+j) ){
                            result=1;
                            return result;
                        }
                        break;
                }

            }
        }
        return result;
    }
    else{
        printf("Error: wrong matrix compare operation.\n");
        exit(-1);
    }
}

Matrix* get_max_col_Matrix(Matrix a){
    Matrix b[2];
    int i,j,k,number=-1;
    float max = MIN;
    for(k=0;k<2;k++){
        b[k].col=1;
        b[k].row=a.row;
        b[k].Box=(float**)malloc(sizeof(float*)*b[k].row);
    }
    for(i=0;i<a.row;i++){
        for(k=0;k<2;k++){
            *(b[k].Box+i)=(float*)malloc(sizeof(float)*b[k].col);
        }
        max = MIN;
        number = -1;
        for(j=0;j<a.col;j++){
            if( *(*(a.Box+i)+j) >= max){
                max = *(*(a.Box+i)+j);
                number = j;
            }
        }
        *(*(b[0].Box+i))=max;
        *(*(b[1].Box+i))=number+1;
    }
    return b;
}


ListPtr get_min_col_NumList(Matrix a){
    int i,j,Nmin=-1;
    float M = MAX;
    Matrix b = a;
    ListPtr l=NULL;
    if(b.row==1){
        for(j=0;j<b.col;j++){
            M = MAX;
            Nmin=-1;
            for(i=0;i<b.col;i++){
                if(*(*b.Box+i)<M ){
                    Nmin = i;
                    M = *(*b.Box+i);
                }
            }
            *(*b.Box+Nmin) = MAX;
            add_Data(&l,Nmin);
        }
        return l;
    }
    else{
        printf("Error: wrong matrix min rank operation.\n");
        exit(-1);
    }
}

Matrix* get_min_col_Matrix(Matrix a){
    Matrix b[2];
    int i,j,k,number=-1;
    float min = MAX;
    for(k=0;k<2;k++){
        b[k].col=1;
        b[k].row=a.row;
        b[k].Box=(float**)malloc(sizeof(float*)*b[k].row);
    }
    for(i=0;i<a.row;i++){
        for(k=0;k<2;k++){
            *(b[k].Box+i)=(float*)malloc(sizeof(float)*b[k].col);
        }
        min = MAX;
        number = -1;
        for(j=0;j<a.col;j++){
            if( *(*(a.Box+i)+j) < min){
                min = *(*(a.Box+i)+j);
                number = j;
            }
        }
        *(*(b[0].Box+i))=min;
        *(*(b[1].Box+i))=number+1;
    }
    return b;
}

Matrix* get_max_row_Matrix(Matrix a){
    Matrix b[2];
    int j,k,number=-1;
    float max = MIN;
    for(k=0;k<2;k++){
        b[k].col=a.col;
        b[k].row=1;
        b[k].Box=(float**)malloc(sizeof(float*)*b[k].row);
        *(b[k].Box)=(float*)malloc(sizeof(float)*b[k].col);
    }
    for(j=0;j<a.col;j++){
        max = MIN;
        number=-1;
        for(k=0;k<a.row;k++){
            if( *(*(a.Box+k)+j) >= max){
                max = *(*(a.Box+k)+j);
                number = k;
            }
        }
        *(*(b[0].Box)+j)=max;
        *(*(b[1].Box)+j)=number+1;
    }
    return b;
}

Matrix* get_min_row_Matrix(Matrix a){
    Matrix b[2];
    int j,k,number=-1;
    float min = MAX;
    for(k=0;k<2;k++){
        b[k].col=a.col;
        b[k].row=1;
        b[k].Box=(float**)malloc(sizeof(float*)*b[k].row);
        *(b[k].Box)=(float*)malloc(sizeof(float)*b[k].col);
    }
    for(j=0;j<a.col;j++){
        min = MAX;
        number=-1;
        for(k=0;k<a.row;k++){
            if( *(*(a.Box+k)+j) < min){
                min = *(*(a.Box+k)+j);
                number = k;
            }
        }
        *(*(b[0].Box)+j)=min;
        *(*(b[1].Box)+j)=number+1;
    }
    return b;
}

Matrix get_max_Matrix(Matrix a, Matrix b){
    Matrix c;
    int i,j;
    if(a.col==b.col && a.row==b.row){
        c.row = a.row;
        c.col = a.col;
        c.Box = (float**)malloc(sizeof(float*)*c.row);
        for(i=0;i<c.row;i++){
            *(c.Box+i)=(float*)malloc(sizeof(float)*c.col);
            for(j=0;j<c.col;j++){
                *(*(c.Box+i)+j)= *(*(a.Box+i)+j) >= *(*(b.Box+i)+j) ? *(*(a.Box+i)+j) : *(*(b.Box+i)+j);
            }
        }
        return c;
    }
    else{
        printf("Error: wrong matrix max get operation.\n");
        exit(-1);
    }
}

Matrix get_min_Matrix(Matrix a, Matrix b){
    Matrix c;
    int i,j;
    if(a.col==b.col && a.row==b.row){
        c.row = a.row;
        c.col = a.col;
        c.Box = (float**)malloc(sizeof(float*)*c.row);
        for(i=0;i<c.row;i++){
            *(c.Box+i)=(float*)malloc(sizeof(float)*c.col);
            for(j=0;j<c.col;j++){
                *(*(c.Box+i)+j)= *(*(a.Box+i)+j) < *(*(b.Box+i)+j) ? *(*(a.Box+i)+j) : *(*(b.Box+i)+j);
            }
        }
        return c;
    }
    else{
        printf("Error: wrong matrix min get operation.\n");
        exit(-1);
    }
}

//平铺矩阵
Matrix repmat_Matrix(Matrix a, int row, int col){
    Matrix b;
    int i,j;
    b.row = a.row * row;
    b.col = a.col * col;
    b.Box = (float**)malloc(sizeof(float*)*b.row);
    for(i=0;i<b.row;i++){
        *(b.Box+i)=(float*)malloc(sizeof(float)*b.col);
        for(j=0;j<b.col;j++){
            *(*(b.Box+i)+j)=*(*(a.Box+i%a.row)+j%a.col);
        }
    }
    return b;
}

//取矩阵特定列
Matrix get_col_Matrix(Matrix a, int col){
    Matrix b;
    int i,j;
    if(col<=a.col){
        b.col=1;
        b.row=a.row;
        b.Box=(float**)malloc(sizeof(float*)*b.row);
        for(i=0;i<b.row;i++){
            *(b.Box+i)=(float*)malloc(sizeof(float)*b.col);
            for(j=0;j<b.col;j++){
                *(*(b.Box+i)+j)=*(*(a.Box+i)+col-1);
            }
        }
        return b;
    }
    else{
        printf("Error: wrong matrix column get operation.\n");
        exit(-1);
    }
}

//取矩阵特定行
Matrix get_row_Matrix(Matrix a, int row){
    Matrix b;
    int i,j;
    if(row<=a.row){
        b.col=a.col;
        b.row=1;
        b.Box=(float**)malloc(sizeof(float*)*b.row);
        for(i=0;i<b.row;i++){
            *(b.Box+i)=(float*)malloc(sizeof(float)*b.col);
            for(j=0;j<b.col;j++){
                *(*(b.Box+i)+j)=*(*(a.Box+row-1)+j);
            }
        }
        return b;
    }
    else{
        printf("Error: wrong matrix row get operation.\n");
        exit(-1);
    }
}

//矩阵元素求和
float sum_Matrix(Matrix a){
    int i,j;
    float result=0.0;
    for(i=0;i<a.row;i++){
        for(j=0;j<a.col;j++){
            result+=*(*(a.Box+i)+j);
        }
    }
    return result;
}

//矩阵列求和
Matrix sum_col_Matrix(Matrix a){
    Matrix b;
    int i,j,k;
    float result=0.0;
    b.col=a.col;
    b.row=1;
    b.Box=(float**)malloc(sizeof(float*)*b.row);
    for(i=0;i<b.row;i++){
        *(b.Box+i)=(float*)malloc(sizeof(float)*b.col);
        for(j=0;j<b.col;j++){
            result=0.0;
            for(k=0;k<a.row;k++){
                result+=*(*(a.Box+k)+j);
            }
            *(*(b.Box+i)+j)=result;
        }
    }
    return b;
}

//矩阵行求和
Matrix sum_row_Matrix(Matrix a){
    Matrix b;
    int i,j,k;
    float result=0.0;
    b.col=1;
    b.row=a.row;
    b.Box=(float**)malloc(sizeof(float*)*b.row);
    for(i=0;i<b.row;i++){
        *(b.Box+i)=(float*)malloc(sizeof(float)*b.col);
        for(j=0;j<b.col;j++){
            result=0.0;
            for(k=0;k<a.col;k++){
                result+=*(*(a.Box+i)+k);
            }
            *(*(b.Box+i)+j)=result;
        }
    }
    return b;
}

//求矩阵欧几里得范数
float norm_Matrix(Matrix a){
    int i,j;
    float result=0.0;
    for(i=0;i<a.row;i++){
        for(j=0;j<a.col;j++){
            result+=pow(*(*(a.Box+i)+j),2);
        }
    }
    return sqrt(result);
}

//数组乘方运算
Matrix pow_Array(Matrix a,int times){
    Matrix b;
    int i,j;
    b.col=a.col;
    b.row=a.row;
    b.Box=(float**)malloc(sizeof(float*)*b.row);
    for(i=0;i<a.row;i++){
        *(b.Box+i)=(float*)malloc(sizeof(float)*b.col);
        for(j=0;j<a.col;j++){
            *(*(b.Box+i)+j) = pow(*(*(a.Box+i)+j),times);
        }
    }
    return b;
}

//数组乘法运算
Matrix multply_Array(Matrix a,Matrix b){
    Matrix c;
    int i,j;
    c.col=b.col;
    c.row=b.row;
    c.Box=(float**)malloc(sizeof(float*)*c.row);
    for(i=0;i<c.row;i++){
        *(c.Box+i)=(float*)malloc(sizeof(float)*c.col);
        for(j=0;j<c.col;j++){
            *(*(c.Box+i)+j)=*(*(a.Box+i)+j) * *(*(b.Box+i)+j);
        }
    }
    return c;
}

//数组除法运算
Matrix divide_Array(Matrix a,Matrix b){
    Matrix c;
    int i,j;
    if(a.col==b.col && a.row==b.row){
        c.col=a.col;
        c.row=a.row;
        c.Box=(float**)malloc(sizeof(float*)*c.row);
        for(i=0;i<c.row;i++){
            *(c.Box+i)=(float*)malloc(sizeof(float)*c.col);
            for(j=0;j<c.col;j++){
                *(*(c.Box+i)+j)=*(*(a.Box+i)+j) / *(*(b.Box+i)+j);
            }
        }
    }
    else{
        printf("Error: wrong array divide operation.\n");
        exit(-1);
    }
    return c;
}


//矩阵乘方运算
Matrix pow_Matrix(Matrix a,int times){
    int i;
    Matrix b = a;
    for(i=0;i<times-1;i++){
        b = multply_Matrix(b,a);
    }
    return b;
}

//矩阵求逆运算
Matrix inverse_Matrix(Matrix a){
    Matrix b,c;
    int i,j,k;
    float times1,times2;
    float* temp=NULL;
    b.col=a.col*2;
    b.row=a.row;
    b.Box=(float**)malloc(sizeof(float*)*b.row);
    //建立増广矩阵
    for(i=0;i<b.row;i++){
        *(b.Box+i)=(float*)malloc(sizeof(float)*b.col);
        for(j=0;j<a.col;j++){
            *(*(b.Box+i)+j)=*(*(a.Box+i)+j);
        }
        for(j=a.col;j<b.col;j++){
            if(i==j-a.col){
                *(*(b.Box+i)+j)=1.0;
            }
            else{
                *(*(b.Box+i)+j)=0.0;
            }
        }
    }

    //找到不为零的对角元
    for(i=0;i<b.row;i++){
        if( *(*(b.Box+i)+i)==0.0 ){
            for(j=i+1;j<b.row;j++){
                if( *(*(b.Box+j)+i)!=0.0 ){
                    temp = *(b.Box+j);
                    *(b.Box+j) = *(b.Box+i);
                    *(b.Box+i) = temp;
                    break;
                }
            }
            if(j==b.row){
                printf("Error: wrong matrix inverse operation.\n");
                exit(-1);
            }
        }
    }

    //对角元单位化
    for(i=0;i<b.row;i++){
        times1 = *(*(b.Box+i)+i);
        if(times1!=0){
            for(j=0;j<b.col;j++){
                *(*(b.Box+i)+j) /= times1;
            }
            //print_Matrix(b);
            for(j=0;j<b.row;j++){
                times2= *(*(b.Box+j)+i);
                if(i!=j && times2!=0){
                    for(k=i;k<b.col;k++){
                        *(*(b.Box+j)+k)-= times2 * (*(*(b.Box+i)+k));
                    }
                }
            }
        }
        else{
            printf("Error: wrong matrix inverse operation.\n");
            exit(-1);
        }
        //print_Matrix(b);
    }

    c.col=a.col;
    c.row=a.row;
    c.Box=(float**)malloc(sizeof(float*)*c.row);
    for(i=0;i<c.row;i++){
        *(c.Box+i)=(float*)malloc(sizeof(float)*c.col);
        for(j=0;j<c.col;j++){
            *(*(c.Box+i)+j)=*(*(b.Box+i)+(j+c.col));
        }
    }

    return c;
}

//矩阵转置运算
Matrix trans_Matrix(Matrix a){
    Matrix b;
    int i,j;
    b.row=a.col;
    b.col=a.row;
    b.Box=(float**)malloc(sizeof(float*)*b.row);
    for(i=0;i<b.row;i++){
        *(b.Box+i)=(float*)malloc(sizeof(float)*b.col);
        for(j=0;j<b.col;j++){
            *(*(b.Box+i)+j)=*(*(a.Box+j)+i);
        }
    }
    return b;
}

//矩阵加法运算
Matrix plus_Matrix(Matrix a, Matrix b){
	Matrix result = {NULL,0,0};
	int i,j;
	if(a.row==b.row && a.col==b.col){
		result.col=a.col;
		result.row=a.row;
		result.Box=(float**)malloc(sizeof(float*)*result.row);
		for(i=0;i<result.row;i++){
			*(result.Box+i)=(float*)malloc(sizeof(float)*result.col);
			for(j=0;j<result.col;j++){
				*(*(result.Box+i)+j)=*(*(a.Box+i)+j) + *(*(b.Box+i)+j);
			}
		}
	}
	else{
        printf("Error: wrong matrix plus operation.\n");
		exit(-1);
	}
	return result;
}

//矩阵减法运算
Matrix minus_Matrix(Matrix a, Matrix b){
	Matrix result = {NULL,0,0};
	int i,j;
	if(a.row==b.row && a.col==b.col){
		result.col=a.col;
		result.row=a.row;
		result.Box=(float**)malloc(sizeof(float*)*result.row);
		for(i=0;i<result.row;i++){
			*(result.Box+i)=(float*)malloc(sizeof(float)*result.col);
			for(j=0;j<result.col;j++){
				*(*(result.Box+i)+j)=*(*(a.Box+i)+j) - *(*(b.Box+i)+j);
			}
		}
	}
	else{
        printf("Error: wrong matrix minus operation.\n");
		exit(-1);
	}
	return result;
}

//矩阵乘法运算
Matrix multply_Matrix(Matrix a, Matrix b){
	Matrix result = {NULL,0,0};
	int i,j,k;
	float sum=0.0;
	if(a.col==b.row){
		result.row=a.row;
		result.col=b.col;
		result.Box=(float**)malloc(sizeof(float*)*result.row);
		for(i=0;i<result.row;i++){
			*(result.Box+i)=(float*)malloc(sizeof(float)*result.col);
			for(j=0;j<result.col;j++){
                sum=0.0;
				for(k=0;k<a.col;k++){
					sum +=(*(*(a.Box+i)+k)) * (*(*(b.Box+k)+j));
				}
				*(*(result.Box+i)+j)=sum;
			}
		}
	}
	else{
        printf("Error: wrong matrix multply operation.\n");
		exit(-1);
	}
	return result;
}

//矩阵除法运算
Matrix divide_Matrix(Matrix a, Matrix b){
    Matrix c = inverse_Matrix(b);
    Matrix d = multply_Matrix(a,c);
    return d;
}

//打印矩阵元素
void print_Matrix(Matrix M1){
	int i=0,j=0;
	for(i=0;i<M1.row;i++){
		for(j=0;j<M1.col;j++){
			printf("\t%f",*(*(M1.Box+i)+j));
		}
		printf("\n");
	}
	printf("\n");
}

