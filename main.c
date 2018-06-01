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

int main()
{

    int i;
    individualPtr pop=NULL,popm=NULL,popc=NULL;
    FListPtr F,FT;
    ListPtr pFT;
    params_initalize();
    population_initalize(&pop);
    F = Sort_Population(&pop);
    for(i=0; i<input.MaxIt; i++)
    {
        system("cls");
        printf("Generation No.%d \n",i+1);
        popm=NULL;
        popc=NULL;
        crossover_population(&popc,pop);
        mutation_population(&popm,pop);
        pop = merge_population(&pop,&popc,&popm);
        F = Sort_Population(&pop);

        FT = F;
        while(FT)
        {
            //printf("Rank No.%d:",FT->Rank);
            //printf("\n");
            pFT = FT->dataList;
            while(pFT)
            {
                //printf("%d\t",pFT->data);
                print_Matrix(trans_Matrix((pop+pFT->data)->Cost));
                pFT = pFT->pNext;
            }
            //printf("\n");
            FT = FT->pNext;
        }
        //Sleep(2000);

    }
    return 0;
}


