# include <stdio.h>
# include "Haar_type.h"

// Creates a Struct Haar, and initialize its attributes
Haar create_Haar(int type,
                 int i, int j,
                 int w, int h,
                 long sum,
                 int polarity,
                 long threshold){
  Haar haar;
  haar.type           = type;
  haar.i              = i;
  haar.j              = j;
  haar.w              = w;
  haar.h              = h;
  haar.sum            = sum;
  haar.sum_normalized = -1;
  haar.polarity       = polarity;
  haar.threshold      = threshold;
  return haar;
}

Haar create_Full_Haar(int type,
                      int i, int j,
                      int w, int h,
                      long sum,
                      long sum_normalized,
                      int polarity,
                      long threshold,
                      float error,
                      int margin) {
  Haar haar;
  haar.type           = type;
  haar.i              = i;
  haar.j              = j;
  haar.w              = w;
  haar.h              = h;
  haar.sum            = sum;
  haar.sum_normalized = sum_normalized;
  haar.polarity       = polarity;
  haar.threshold      = threshold;
  haar.error          = error;
  haar.margin         = margin;
  return haar;

}

void fill_Haar(Haar* haar,
               int type,
               int i, int j,
               int w, int h,
               long sum,
               int polarity,
               long threshold){
  haar->type           = type;
  haar->i              = i;
  haar->j              = j;
  haar->w              = w;
  haar->h              = h;
  haar->sum            = sum;
  haar->sum_normalized = -1;
  haar->polarity       = polarity;
  haar->threshold      = threshold;
}

void copy_Haar(Haar* source, Haar* dest){
  dest->type           = source->type;
  dest->i              = source->i;
  dest->j              = source->j;
  dest->w              = source->w;
  dest->h              = source->h;
  dest->sum            = source->sum;
  dest->sum_normalized = source->sum_normalized;
  dest->polarity       = source->polarity;
  dest->threshold      = source->threshold;
}

int is_present(Haar h)
{
  return ((h.sum > h.threshold)?
          1/**h.polarity*/:
          -1/**h.polarity*/);
}


// Print a haar feature for debug purpose
void print_Haar(Haar h){
  warnx(
    "\
| type = %d \
| i = %2d \
| j = %2d \
| w = %2d \
| h = %2d \
| sum = %4ld \
| sum_normalized = %ld\n",
    h.type, h.i, h.j, h.w, h.h, h.sum, h.sum_normalized);
}

char* Haar_to_str(Haar h){
  char* str = malloc(sizeof(char) * 200);
  sprintf(str,
    "\
| type = %d \
| i = %2d \
| j = %2d \
| w = %2d \
| h = %2d \
| threshold = %d\
| polarity = %d\
| margin = %d\
| sum = %4ld",
          h.type, h.i, h.j, h.w, h.h, h.sum, h.threshold, h.polarity, h.margin);
  return str;
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
