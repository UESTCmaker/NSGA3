#include <stdio.h>
#include <ctype.h>
#include "Sort_Population.h"
#include "nsga3.h"

/*
F Sort_Population(individualPtr *pop){

}
*/

void Normalize_Population(individualPtr *pop){
    int i,j;
    individualPtr p=*pop;
    Matrix fp = zeros_Matrix( p->Cost.row, input.nPop);
    Update_IdealPoint(p);
    for(j=0;j<input.nPop;j++){
        for(i=0;i<p->Cost.row;i++){
            *(*(fp.Box+i)+j) = *(*(p->Cost.Box+i));
        }
        p++;
    }
    print_Matrix(fp);
    fp = minus_Matrix(fp,repmat_Matrix(param.zmin,1,input.nPop));
    print_Matrix(fp);
    Perform_Scalarizing(fp);
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
        print_Matrix(s);
        temp = get_min_col_Matrix(s);
        sminj = *(*(temp->Box));
        temp++;
        ind = (int)*(*(temp->Box));

        printf("*****************%f %d\n",sminj,ind);

        if(sminj < *(*smin.Box+j)){
            for(k=0;k<input.nObj;k++){
                *(*(zmax.Box+k)+j) = *(*(fp.Box+k)+ind);
            }
            *(*smin.Box+j) = sminj;
        }
    }
    param.zmax = zmax;
    param.smin = smin;
    print_Matrix(param.zmax);
    print_Matrix(param.smin);
}

Matrix Scalarizing_Vector(int nObj, int j){
    float epsilon = 0.0001;
    Matrix w = somes_Matrix(epsilon, nObj, 1);
    *(*(w.Box+j)) = 1.0;
    return w;
}


/*
function params = PerformScalarizing(z, params)

    nObj = size(z,1);
    nPop = size(z,2);

    if ~isempty(params.smin)
        zmax = params.zmax;
        smin = params.smin;
    else
        zmax = zeros(nObj, nObj);
        smin = inf(1,nObj);
    end

    for j = 1:nObj

        w = GetScalarizingVector(nObj, j);

        s = zeros(1,nPop);
        for i = 1:nPop
            s(i) = max(z(:,i)./w);
        end

        [sminj, ind] = min(s);

        if sminj < smin(j)
            zmax(:, j) = z(:, ind);
            smin(j) = sminj;
        end

    end

    params.zmax = zmax;
    params.smin = smin;

end
*/

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

/*
function [pop, params] = NormalizePopulation(pop, params)

    params.zmin = UpdateIdealPoint(pop, params.zmin);

    fp = [pop.Cost] - repmat(params.zmin, 1, numel(pop));

    params = PerformScalarizing(fp, params);

    a = FindHyperplaneIntercepts(params.zmax);

    for i = 1:numel(pop)
        pop(i).NormalizedCost = fp(:,i)./a;
    end

end

function a = FindHyperplaneIntercepts(zmax)

    w = ones(1, size(zmax,2))/zmax;

    a = (1./w)';

end
*/

/*
F NonDominatedSorting(){

}
*/
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
