/*
  None of this functionality has been tested
*/

//return square of n, i.e; n^2
int square(int n){
  return n*n;
}

//retruns area of triangle
int triangle_area(int base, int height){
  return (height*base)>>1; 
}

//return area of triangle, defined by base and height
int triangle_area2(int base, int height){
  int area = base / 2;
  area *= height;
  return area; 
}

//increments value of n
void increment(int n){
  n=n+1;
}

//increments value of n
void increment2(int* n){
  n = n+1;
}

//increments value of n
void increment3(int* n){
  *(n)=*(n)+1;
}




