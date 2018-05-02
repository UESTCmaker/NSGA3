#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Lite_Matrix.h"

#define MIN -3.40E+38
#define MAX +3.40E+38

//浮点数四舍五入运算
int round_Num(float num){
    if( (ceil(num)-num) <= (num-floor(num)) ){
        return ceil(num);
    }
    else{
        return floor(num);
    }
}

//限定范围的随机数生成器
float random_Num(float maxNum,float minNum){
	float randnum;
	float interval= maxNum-minNum+0.99999;
	do{
        randnum=fmodf((float)rand(),interval)+minNum+0.00001;
	}while(randnum>maxNum || randnum<minNum);
	return randnum;
}

//随机初始化矩阵
Matrix random_Matrix(float VarMin, float VarMax, int row, int col){
	Matrix M1;
	int i,j;
	M1.Box = (float**)malloc(sizeof(float*)*row);
	M1.col=col;
	M1.row=row;
	for(i=0;i<row;i++){
		*(M1.Box+i)=(float*)malloc(sizeof(float)*col);
		for(j=0;j<col;j++){
			*(*(M1.Box+i)+j)=random_Num(VarMin,VarMax);
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
        perror("wrong matrix compare operation:");
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
        perror("wrong matrix compare operation.\n");
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
        *(*(b[1].Box+i))=number;
    }
    return b;
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
        *(*(b[1].Box+i))=number;
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
        *(*(b[1].Box)+j)=number;
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
        *(*(b[1].Box)+j)=number;
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
        perror("wrong matrix get operation.\n");
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
        perror("wrong matrix get operation.\n");
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
        perror("wrong matrix column get operation.\n");
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
        perror("wrong matrix row get operation.\n");
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
Matrix pow_array(Matrix a,int times){
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

//数组除法运算
Matrix divide_array(Matrix a,Matrix b){
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
        perror("wrong array divide operation:");
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
    float times;
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
            for(j=i;j<b.row;j++){
                if( *(*(b.Box+j)+i)!=0.0 ){
                    temp = *(b.Box+j);
                    *(b.Box+j) = *(b.Box+i);
                    *(b.Box+i) = temp;
                    break;
                }
            }
            if(j==b.row){
                perror("wrong matrix inverse operation:");
                exit(-1);
            }
        }
    }

    //对角元单位化
    for(i=0;i<b.row;i++){

        times = *(*(b.Box+i)+i);
        for(j=0;j<b.col;j++){
            *(*(b.Box+i)+j) /= times;
        }

        for(j=0;j<b.row;j++){
            if(i!=j){
                times= *(*(b.Box+j)+i);
                for(k=i;k<b.col;k++){
                    *(*(b.Box+j)+k)-= times * (*(*(b.Box+i)+k));
                }
            }
        }
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
		perror("wrong matrix plus operation:");
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
		perror("wrong matrix minus operation:");
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
		perror("wrong matrix multply operation:");
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

