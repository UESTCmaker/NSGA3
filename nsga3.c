#include <stdio.h>
#include "nsga3.h"

void params_initalize(){
   nCrossover = 2*round_Num(pCrossover*nPop/2);
   nMutation  = round_Num(pMutation*nPop);
   sigma  = 0.1*(VarMax-VarMin);
}
