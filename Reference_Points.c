#include <stdio.h>
#include <math.h>
#include "Reference_Points.h"
#include "nsga3.h"

int step_multply(int m)
{
    int i,result=1;
    for(i=1; i<=m; i++)
    {
        result *= i;
    }
    return result;
}

int step_plus(int m)
{
    int i,result=0;
    for(i=1; i<=m; i++)
    {
        result += i;
    }
    return result;
}

int permutation(int m, int n)
{
    int i,result=1;
    for(i=0; i<m; i++)
    {
        result*=n-i;
    }
    result /= step_multply(m);
    return result;
}

//初始化参考点（仅适用于二维及三维）
Matrix Generate_Points(int obj, int division)
{
    float step = 1.0/(float)division;
    int nPoint = division+1,div = division,last = 0;
    int j;
    Matrix a = zeros_Matrix(obj,permutation(division,obj+division-1));
    for(j=0; j<a.col; j++)
    {
        if(j==last+nPoint)
        {
            last=last+nPoint;
            nPoint--;
            div--;
        }
        *(*(a.Box+0)+j) = step*(j-last);
        *(*(a.Box+1)+j) = step*(div-(j-last));
        if(a.row==3)
        {
            *(*(a.Box+2)+j) = 1.0 - *(*(a.Box+0)+j) - *(*(a.Box+1)+j);
        }
    }
    return a;
}


