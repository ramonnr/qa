/*
  This is a example test client for the untested_math.c functions.
  All tests highly rely on random stimuli. This simplyfies the choice of testcases.
  If the tester suspects there to be erronous behavior at some certain range of possible input
  then additional tests should be done around this range.
  (note that random in the digital world is only pseudo random!)

  Most of the tests in this file will fail due to singed overflow problems.

  This would be a good start for a test client, later you would have to inspect each failing test. 
  To determine what causes the tests to fail. This could be done by:
  - printing input, output and expected results
  - single stepping in the debugger and inspecting variables

  If the student finds testmethodology to be highly interesting, then a suggestion is to 
  read up on testbenches for VHDL/Verilog. These will be more detailed in describing the 
  methodology than most programming books will be. 
  Also hardware description languages are stupid fun. You can create your own processor, just saying.

  If you have feedback or questions, feel free to contact me at ramon.nordin.rodriguez@avaloninnovation.com
*/


#include "untested_math.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

void output_test_result(const char*, bool);
bool square_test(void);
bool triangle_area_test(void);
bool triangle_area2_test(void);
bool increment_test(void);
bool increment2_test(void);
bool increment3_test(void);

int main(){
  //seed pseudo random generator
  srand(time(NULL));

  //test square function
  output_test_result("square()",square_test());

  //test triangle_area function
  output_test_result("triangle_area()",triangle_area_test());

  //test triangle_area2 function
  output_test_result("triangle_area2()",triangle_area2_test());

  //test increment function
  output_test_result("increment()", increment_test());

  //test increment2 function
  output_test_result("increment2()", increment2_test());

  //test increment3 function
  output_test_result("increment3()", increment3_test());

}

//this function is only used to clean up the main function
void output_test_result(const char* str, bool result){
  if(result == true)printf("%s : pass\n",str);
  else printf("%s : failed\n",str);
}

bool square_test(void){
  bool result = true;
  //testing one edge case and two simple cases
  if(square(2) != 4) result = false;
  if(square(-1)!=1)  result = false;
  if(square(10)!=100)result = false;
  //run test on random input
  for(int i = 0; i < 10000; i++){
    int rnd = rand();
    if(square(rnd) != rnd*rnd) result = false;
    //a square can never be negative
    //this should fail since square retuns singed integer, should be unsigned
    //also no bounds checks, this will overflow
    if(square(rnd) < 0) result = false;
  }
  
  return result;
}

bool triangle_area_test(void){
  bool result = true;
  int area;
  //with integer math a = floor[ (b*h)/2 ]
  //test some know results
  //b = 2, h = 1 => a = 1
  area = triangle_area(2,1);
  if(area != 1) result = false;
  //b = 4, h = 3 => a = 6
  area = triangle_area(4,3);
  if(area != 6) result = false;
  //b = 3, h = 3 => a = 4
  area = triangle_area(3,3);
  if(area != 4) result = false;

  //since triangle_area returns an int, there is not much to be done about
  //error correction, caller must be responsible for checking against negative area
  //comments about this should be added to the source code
  
  //testing for random input
  for(int i = 0; i < 10000; i++){
    int r1 = rand();
    int r2 = rand();
    
    area = triangle_area(r1, r2);
    //rand returns values [0, RAND_MAX], result cannot be negative
    if(area < 0 ){
      result = false;
    }
    //r1 & r2 > 0, area must be > 0
    else if( ( (r1 != 0) && (r2 != 0) ) && area == 0){
      result = false;
    }
    else if(area != (r1*r2)/2){
      result = false;
      //added output here so you can inspect som overflow problems
      //uncommenting will add alot of output!
      //printf("error triangle_area() with params: %d\t%d\n",r1,r2);
      //printf("(r1*r2)/2 = %d, ret value was: %d\n",(r1*r2)/2, area);
    }
  }
  
  return result;
  
}


bool triangle_area2_test(void){
  //same expected functionality as triangle_area
  //by inspection line 17 & 18 splits the calculation
  //this is a common risk, test this explicitly!
  
  bool result = true;
  int area;
  //with integer math a = floor[ (b*h)/2 ]
  //test some know results
  //b = 2, h = 1 => a = 1
  area = triangle_area(2,1);
  if(area != 1) result = false;
  //b = 4, h = 3 => a = 6
  area = triangle_area(4,3);
  if(area != 6) result = false;
  //b = 3, h = 3 => a = 4
  area = triangle_area(3,3);
  if(area != 4) result = false;

  //attempt to force error from line 17
  //result should be 2
  area = triangle_area(1,2);
  if(area != 2) result = false;
  
  
  //since triangle_area returns an int, there is not much to be done about
  //error correction, caller must be responsible for checking against negative area
  //comments about this should be added to the source code
  
  //testing for random input
  for(int i = 0; i < 10000; i++){
    int r1 = rand();
    int r2 = rand();
    
    area = triangle_area(r1, r2);
    //rand returns values [0, RAND_MAX], result cannot be negative
    if(area < 0 ){
      result = false;
    }
    //r1 & r2 > 0, area must be > 0
    else if( ( (r1 != 0) && (r2 != 0) ) && area == 0){
      result = false;
    }
    else if(area != (r1*r2)/2){
      result = false;
    }
  }
  
  return result; 
}
bool increment_test(void){
  bool result = true;

  for(int i = 0; i < 10000; i++){
    int n = rand();
    int n_old = n;
    increment(n);
    if(n != n_old +1 )result = false;
  }
  return result;
}


bool increment2_test(void){
  bool result = true;

  for(int i = 0; i < 10000; i++){
    int n = rand();
    int n_old = n;
    increment2(&n);
    if(n != n_old +1 )result = false;
  }
  return result;
}

  
bool increment3_test(void){
  bool result = true;

  for(int i = 0; i < 10000; i++){
    int n = rand();
    int n_old = n;
    increment3(&n);
    if(n != n_old +1 )result = false;
  }
  return result;
}





