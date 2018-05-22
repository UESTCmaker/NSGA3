#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include "Cost_Function.h"
#include "Reference_Points.h"
#include "Sort_Population.h"
#include "Lite_Matrix.h"
#include "Lite_List.h"
#include "nsga3.h"

int main(){
    int i;
    individualPtr pop=NULL,popm=NULL,popc=NULL;
    FListPtr F,FT;
    params_initalize();
    population_initalize(&pop);
    F = Sort_Population(&pop);
    for(i=0;i<input.MaxIt;i++){
        crossover_population(&popc,pop);
        mutation_population(&popm,pop);
        pop = merge_population(pop,popc,popm);
        input.nPop += (input.nCrossover+input.nMutation);
        F = Sort_Population(&pop);
        FT = F;
/*        while(FT->pNext)FT=FT->pNext;
        while(FT){
            while(FT->dataList){
                print_Matrix( (pop+FT->dataList->data)->Cost);
                FT->dataList = FT->dataList->pNext;
            }
            FT=FT->pFront;
        }
        Sleep(2000);
*/
        system("cls");
        while(FT){
            while(FT->dataList){
                    print_Matrix( (pop+FT->dataList->data)->Cost);
                    FT->dataList = FT->dataList->pNext;
                }
            FT = FT->pNext;
        }
    Sleep(2000);
    }


	return 0;
}
