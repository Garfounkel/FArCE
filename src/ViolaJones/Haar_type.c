# include <stdio.h>
# include "Haar_type.h"

// Creates a Struct Haar, and initialize its attributes
Haar create_Haar(int type, int i, int j, int w, int h, long sum){
  Haar haar; //= malloc(sizeof(int) * 5 + sizeof(unsigned long));
  haar.type = type;
  haar.i = i;
  haar.j = j;
  haar.w = w;
  haar.h = h;
  haar.sum = sum;
  haar.sum_normalized = -1;
  return haar;
}

void fill_Haar(Haar* haar, int type, int i, int j, int w, int h, long sum){
  haar->type = type;
  haar->i = i;
  haar->j = j;
  haar->w = w;
  haar->h = h;
  haar->sum = sum;
  haar->sum_normalized = -1;
}

// Print a haar feature for debug purpose
void print_Haar(Haar h){
  printf(
    "| type = %d | i = %2d | j = %2d | w = %2d | h = %2d | sum = %ld | sum_normalized = %ld\n",
         h.type, h.i, h.j, h.w, h.h, h.sum, h.sum_normalized);
}

// Creates a Struc Haar Vect, and initialize its attributes
Haar_vect create_Haar_vect(Haar haar){
  Haar_vect haar_vect;
  haar_vect.haar = haar;
  haar_vect.next = 0;
  return haar_vect;
}

// Print a haar vect feature for debug purpose
void print_Haar_vect(Haar_vect h){
  print_Haar(h.haar);
  if (h.next != 0) {
    print_Haar_vect(*h.next);
  }
}
