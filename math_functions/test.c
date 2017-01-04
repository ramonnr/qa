#include "untested_math.h"
#include <stdio.h>
#include <stdbool.h>

bool square_test(void);
bool square_test(void){
  bool result = true;

  if(square(2) != 4) result = false;
  if(square(-1)!=1)  result = false;
  if(square(10)!=100)result = false;
  return result;
}

int main(){
  if(square_test()) printf("square() : pass\n");
  else printf("square() : fail\n");
}
