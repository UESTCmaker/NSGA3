#include <stdio.h>
#include <ctype.h>
#include "Sort_Population.h"
#include "Lite_List.h"
#include "nsga3.h"

#define epsilon 0.001

/*
F Sort_Population(individualPtr *pop){

}
*/

void Normalize_Population(individualPtr *pop){
    int i,j;
    individualPtr p=*pop;
    Matrix fp = zeros_Matrix( p->Cost.row, input.nPop);
    Matrix a,b;
    Update_IdealPoint(p);
    for(j=0;j<input.nPop;j++){
        for(i=0;i<p->Cost.row;i++){
            *(*(fp.Box+i)+j) = *(*(p->Cost.Box+i));
        }
        p++;
    }
    fp = minus_Matrix(fp,repmat_Matrix(param.zmin,1,input.nPop));
    Perform_Scalarizing(fp);
    a = Find_HyperplaneIntercepts();

    b = divide_array(fp,repmat_Matrix(a,1,input.nPop));
    p = *pop;
    for(i=0;i<input.nPop;i++){
        p->NormalizedCost = get_col_Matrix(b,i+1);
        p++;
    }
}

Matrix Find_HyperplaneIntercepts(){
    Matrix a,w;
    w = divide_Matrix(ones_Matrix(1,param.zmax.col),param.zmax);
    a = trans_Matrix(divide_array(ones_Matrix(w.row,w.col),w));
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
    for(j=0;j<input.nObj;j++){
        w = Scalarizing_Vector(input.nObj,j);
        s = zeros_Matrix(1,input.nPop);
        for(i=0;i<input.nPop;i++){
            *(*s.Box+i) = *(*(get_max_row_Matrix(divide_array(get_col_Matrix(fp,i+1),w))->Box)) ;
        }
        temp = get_min_col_Matrix(s);
        sminj = *(*(temp->Box));
        temp++;
        ind = (int)*(*(temp->Box));

        if(sminj < *(*smin.Box+j)){
            for(k=0;k<input.nObj;k++){
                *(*(zmax.Box+k)+j) = *(*(fp.Box+k)+ind);
            }
            *(*smin.Box+j) = sminj;
        }
    }
    param.zmax = zmax;
    param.smin = smin;
}

Matrix Scalarizing_Vector(int nObj, int j){
    Matrix w = somes_Matrix(epsilon, nObj, 1);
    *(*(w.Box+j)) = 1.0;
    return w;
}

void Update_IdealPoint(individualPtr pop){
    int i;
    individualPtr p = pop;
    if(!param.zmin.Box){
        param.zmin = infinity_Matrix(p->Cost.row,p->Cost.col);
    }
    for(i=0;i<input.nPop;i++){
        param.zmin = get_min_Matrix(param.zmin,p->Cost);
        p++;
    }
}



void NonDominatedSorting(individualPtr *pop){
    int i,j;
    individualPtr p,q,m = *pop;
    ListPtr *F;
    for(i=0;i<input.nPop;i++){
        m->DominatedCount=0;
        m++;
    }
    for(i=0;i<input.nPop;i++){
        for(j=0;j<input.nPop;j++){
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
            //F
        }
    }
}

int dominates_Matrix(Matrix a,Matrix b){
    return all_flag_Matrix(a,b,-10) && any_flag_Matrix(a,b,-1);
}


/*
AssociateToReferencePoint(){

}
*/
/*
function [pop, F, params] = SortAndSelectPopulation(pop, params)

    [pop, params] = NormalizePopulation(pop, params);

    [pop, F] = NonDominatedSorting(pop);

    nPop = params.nPop;
    if numel(pop) == nPop
        return;
    end

    [pop, d, rho] = AssociateToReferencePoint(pop, params);

    newpop = [];
    for l=1:numel(F)
        if numel(newpop) + numel(F{l}) > nPop
            LastFront = F{l};
            break;
        end

        newpop = [newpop; pop(F{l})];   %#ok
    end

    while true

        [~, j] = min(rho);

        AssocitedFromLastFront = [];
        for i = LastFront
            if pop(i).AssociatedRef == j
                AssocitedFromLastFront = [AssocitedFromLastFront i]; %#ok
            end
        end

        if isempty(AssocitedFromLastFront)
            rho(j) = inf;
            continue;
        end

        if rho(j) == 0
            ddj = d(AssocitedFromLastFront, j);
            [~, new_member_ind] = min(ddj);
        else
            new_member_ind = randi(numel(AssocitedFromLastFront));
        end

        MemberToAdd = AssocitedFromLastFront(new_member_ind);

        LastFront(LastFront == MemberToAdd) = [];

        newpop = [newpop; pop(MemberToAdd)]; %#ok

        rho(j) = rho(j) + 1;

        if numel(newpop) >= nPop
            break;
        end

    end

    [pop, F] = NonDominatedSorting(newpop);

end
*/
