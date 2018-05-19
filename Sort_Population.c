#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include "Sort_Population.h"
#include "Lite_Matrix.h"
#include "Lite_List.h"
#include "nsga3.h"

#define epsilon 0.001


FListPtr Sort_Population(individualPtr *pop){
    int l,i,j,new_member_ind,MemberToAdd;
    FListPtr F = NULL,FT = NULL;
    ListPtr newpop=NULL,LastFront=NULL,AssociateFromLastFront=NULL,NumList=NULL,LastF;
    individualPtr p = *pop;
    Matrix d,rho,*result;
    Normalize_Population(pop);
    F = NonDominated_Sorting(pop);
    if(input.nPop==input.nPop_Old){return F;}
    result = Associate_ReferencePoint(pop);
    d = *result;
    rho = *(result+1);
    printf("d:\n");
    print_Matrix(d);
    printf("rho:\n");
    print_Matrix(rho);
    FT = F;
    while(FT){
        printf("Rank:%d  Number Set:\t",FT->Rank);
        print_List(FT->dataList);
        printf("\n");
        FT=FT->pNext;
    }
    FT = F;
    while(FT->pNext)FT=FT->pNext;
    while(FT){
        if(number_List(FT->dataList)+number_List(newpop) > input.nPop_Old){
            printf("I win!\n");
            LastFront = FT->dataList;
            break;
        }
        add_List(&newpop,FT->dataList);
        FT=FT->pFront;
    }

    printf("LastFront:\n");
    print_List(LastFront);
    printf("Newpop:\n");
    print_List(newpop);

    NumList = get_min_col_NumList(rho);
    LastF = LastFront;
    while(NumList){
        LastF = LastFront;
        while(LastF){
            i = LastF->data;
            if((p+i)->AssociatedRef == NumList->data){
                add_Data(&AssociateFromLastFront,i);
            }
            LastF = LastF->pNext;
        }
        if(AssociateFromLastFront==NULL){
            *(*rho.Box+j) = MAX;
            continue;
        }

        if(*(*rho.Box+NumList->data)==0.0){

        }
        else{
            new_member_ind = rand() % number_List(AssociateFromLastFront);
        }
        MemberToAdd = find_List(AssociateFromLastFront, new_member_ind);

        delete_List(&LastFront,MemberToAdd);
        add_List(&newpop,MemberToAdd);
        *(*rho.Box+NumList->data)+= 1.0;
        if(number_List(newpop)>=input.nPop_Old){break;}
        NumList = NumList->pNext;
    }


    return F;
}


void Normalize_Population(individualPtr *pop){
    int i,j;
    individualPtr p=*pop;
    Matrix fp = zeros_Matrix( p->Cost.row, input.nPop);
    Matrix a,b;
    Update_IdealPoint(pop);
    for(j=0;j<input.nPop;j++){
        for(i=0;i<p->Cost.row;i++){
            *(*(fp.Box+i)+j) = *(*(p->Cost.Box+i));
        }
        p++;
    }
    //print_Matrix(fp);
    fp = minus_Matrix(fp,repmat_Matrix(param.zmin,1,input.nPop));
    Perform_Scalarizing(fp);
    a = Find_HyperplaneIntercepts();
    //print_Matrix(a);
    b = divide_Array(fp,repmat_Matrix(a,1,input.nPop));
    p = *pop;
    for(i=0;i<input.nPop;i++){
        p->NormalizedCost = get_col_Matrix(b,i+1);
        p++;
    }
    //print_Matrix(b);
}

Matrix Find_HyperplaneIntercepts(){
    Matrix a,w;
    w = divide_Matrix(ones_Matrix(1,param.zmax.col),param.zmax);
    //print_Matrix(w);
    a = trans_Matrix(divide_Array(ones_Matrix(w.row,w.col),w));
    return a;
}

void Perform_Scalarizing(Matrix fp){
    int i,j,ind,k;
    float sminj;
    Matrix zmax,smin,w,s;
    Matrix* temp;
    input.nObj=fp.row;
    input.nPop=fp.col;
    if(!param.smin.Box){
        zmax = zeros_Matrix(input.nObj,input.nObj);
        smin = infinity_Matrix(1,input.nObj);
    }
    else{
        zmax = param.zmax;
        smin = param.smin;
    }
//    print_Matrix(fp);
    for(j=0;j<input.nObj;j++){
        w = Scalarizing_Vector(input.nObj,j);
        s = zeros_Matrix(1,input.nPop);
        for(i=0;i<input.nPop;i++){
            *(*s.Box+i) = *(*(get_max_row_Matrix(divide_Array(get_col_Matrix(fp,i+1),w))->Box)) ;
        }
        //print_Matrix(s);
        temp = get_min_col_Matrix(s);
        sminj = *(*(temp->Box));
        temp++;
        ind = (int)*(*(temp->Box))-1;

        if(sminj < *(*smin.Box+j)){
            for(k=0;k<input.nObj;k++){
                *(*(zmax.Box+k)+j) = *(*(fp.Box+k)+ind);
            }
            *(*smin.Box+j) = sminj;
        }
    }
    param.zmax = zmax;
    param.smin = smin;
    //print_Matrix(zmax);
    //print_Matrix(smin);
}

Matrix Scalarizing_Vector(int nObj, int j){
    Matrix w = somes_Matrix(epsilon, nObj, 1);
    *(*(w.Box+j)) = 1.0;
    return w;
}

void Update_IdealPoint(individualPtr *pop){
    int i;
    individualPtr p = *pop;
    if(!param.zmin.Box){
        param.zmin = infinity_Matrix(p->Cost.row,p->Cost.col);
    }
    for(i=0;i<input.nPop;i++){
        param.zmin = get_min_Matrix(param.zmin,(p+i)->Cost);
    }
}

FListPtr NonDominated_Sorting(individualPtr *pop){
    int i,j,k;
    individualPtr p,q,m = *pop;
    ListPtr a,b;
    FListPtr Q,R,F = (FListPtr)malloc(sizeof(FListBox));
    F->dataList = NULL;
    F->pNext = NULL;
    F->pFront =NULL;
    F->Rank = 1;
    for(i=0;i<input.nPop;i++){
        m->DominatedCount=0;
        m++;
    }
    m = *pop;
    for(i=0;i<input.nPop;i++){
        for(j=i+1;j<input.nPop;j++){
            p = m+i;
            q = m+j;
            if(dominates_Matrix(p->Cost,q->Cost)){
                add_Data(&p->DominationSet,j);
                q->DominatedCount++;
            }
            if(dominates_Matrix(q->Cost,p->Cost)){
                add_Data(&q->DominationSet,i);
                p->DominatedCount++;
            }
        }
        if(p->DominatedCount==0){
            add_Data( &F->dataList, i);
            p->Rank=1;
        }
    }
    k=1;
    while(1){
        Q = (FListPtr)malloc(sizeof(FListBox));
        Q->dataList = NULL;
        Q->pNext = NULL;
        Q->pFront = NULL;
        Q->Rank = k+1;
        R = F;
        while(R->Rank!=k)R=R->pNext;
        a = R->dataList;
        while(a){
            p = m+(a->data);
            b=p->DominationSet;
            while(b){
                q = m+(b->data);
                q->DominatedCount--;
                if(q->DominatedCount==0){
                    add_Data( &Q->dataList, b->data);
                    q->Rank=k+1;
                }
                b = b->pNext;
            }
            a=a->pNext;
        }
        if(Q->dataList==NULL)break;

        R->pNext = Q;
        Q->pFront = R;
        k++;
    }
    return F;
}

int dominates_Matrix(Matrix a,Matrix b){
    return all_flag_Matrix(a,b,-10) && any_flag_Matrix(a,b,-1);
}

Matrix* Associate_ReferencePoint(individualPtr *pop){
    int i,j,jmin,
    nZr = param.nZr;
    individualPtr p,m = *pop;
    float dmin;
    Matrix w,z,*x,*result,
    Zr = param.Zr,
    rho = zeros_Matrix(1,nZr),
    d = zeros_Matrix(input.nPop,nZr);
    result = (Matrix*)malloc(sizeof(Matrix)*2);
    *result = d;
    *(result+1) = rho;
    for(i=0;i<input.nPop;i++){
        p = m+i;
        z = p->NormalizedCost;
        for(j=0;j<nZr;j++){
            w = divide_Array(get_col_Matrix(Zr,j+1), somes_Matrix(norm_Matrix(get_col_Matrix(Zr,j+1)),Zr.row,1));
            *(*(d.Box+i)+j) = norm_Matrix(minus_Matrix(z, multply_Array(repmat_Matrix(multply_Matrix(trans_Matrix(w),z),w.row,w.col), w)));
        }
        //print_Matrix(get_row_Matrix(d,i+1));
        x = get_min_col_Matrix(get_row_Matrix(d,i+1));
        dmin = (float)*(*(x->Box));
        x++;
        jmin = (int)*(*(x->Box))-1;
        p->AssociatedRef = jmin;
        p->DistanceToAssociatedRef = dmin;
        *(*(rho.Box)+jmin) = *(*(rho.Box)+jmin) + 1.0;
        //print_Matrix(rho);
    }
    return result;
}
