#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include "Sort_Population.h"
#include "Lite_Matrix.h"
#include "Lite_List.h"
#include "nsga3.h"

#define epsilon 0.001


FListPtr Sort_Population(individualPtr *pop){
    int i,j,MemberToAdd;
    float M = MAX;
    FListPtr F = NULL,FT = NULL;
    ListPtr newpop=NULL,LastFront=NULL,AssociateFromLastFront=NULL,NumList=NULL,Numl=NULL,LastF=NULL,AssociateF=NULL;
    individualPtr p = *pop;
    Matrix d,rho,ddj,*result;
    Normalize_Population(pop);
    F = NonDominated_Sorting(pop);
    if(input.nPop==input.nPop_Old){return F;}
    result = Associate_ReferencePoint(pop);
    d = *result;
    rho = *(result+1);
/*
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
*/
    FT = F;
    while(FT->pNext)FT=FT->pNext;
    while(FT){
        if(number_List(FT->dataList)+number_List(newpop) > input.nPop_Old){
            LastFront = FT->dataList;
            break;
        }
        add_List(&newpop,FT->dataList);
        FT=FT->pFront;
    }
/*
    printf("LastFront:\n");
    print_List(LastFront);
    printf("Newpop:\n");
    print_List(newpop);
*/
    NumList = get_min_col_NumList(rho);
    Numl = NumList;

    while(1){
        if(!Numl){
            Numl=NumList;
        }
        LastF = LastFront;
        while(LastF){
            i = LastF->data;
            //printf("LastFront data:%d\n",i);
            //printf("(p+i)->AssociatedRef:%d\n",(p+i)->AssociatedRef);
            AssociateFromLastFront=NULL;
            if((p+i)->AssociatedRef == Numl->data){
                add_Data(&AssociateFromLastFront,i);
            }
            LastF = LastF->pNext;
        }
        if(AssociateFromLastFront==NULL){
            *(*rho.Box+Numl->data) = MAX;
            Numl = Numl->pNext;
            continue;
        }
        //print_List(AssociateFromLastFront);
        MemberToAdd=-1;
        if(*(*rho.Box+NumList->data)==0.0){
            ddj = get_col_Matrix(d,Numl->data);
            AssociateF = AssociateFromLastFront;
            M = MAX;
            while(AssociateF){
                if( *(*(ddj.Box+AssociateF->data))<M ){
                    M = *(*(ddj.Box+AssociateF->data));
                    MemberToAdd = AssociateF->data;
                }
                AssociateF=AssociateF->pNext;
            }
        }
        else{
            MemberToAdd = find_List(AssociateFromLastFront, rand() % number_List(AssociateFromLastFront)+1);
        }
        delete_List(&LastFront,MemberToAdd);
        add_Data(&newpop,MemberToAdd);
        *(*rho.Box+NumList->data)+= 1.0;
        Numl = Numl->pNext;
        if(number_List(newpop)>=input.nPop_Old){
            break;
        }
    }
    Update_Population(pop, newpop);
    input.nPop = input.nPop_Old;
    F = NonDominated_Sorting(pop);
    return F;
}

void  Update_Population(individualPtr* pop, ListPtr newpop){
    individualPtr Newp = (individualPtr*)malloc(sizeof(individualBox)*number_List(newpop)), Np=Newp;
    individualPtr p;
    while(newpop){
        p = (*pop)+newpop->data;
        Np->Cost = p->Cost;
        Np->Position = p->Position;
        Np++;
        newpop=newpop->pNext;
    }
    *pop = Newp;
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
    //print_Matrix(fp);
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
            //print_Matrix(get_col_Matrix(fp,ind+1));
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
        *(*(rho.Box)+jmin) = *(*(rho.Box)+jmin) + 1.0;
        p->AssociatedRef = jmin+1;
        p->DistanceToAssociatedRef = dmin;

        //print_Matrix(rho);
    }
    return result;
}
