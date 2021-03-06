#include "haar.h"


// Compute the sum of pixels using integral image
// in a rectangle defined by h1, w1, h2 and w2 inside img
long sum_rect(Ulong_tab* img, int h1, int w1, int h2, int w2){
  unsigned long val_A = 0, val_B = 0, val_C = 0, val_D = 0;
  // A B
  // D C

  /*
  if (h1 > 24 || h1 < 0) {

  printf ("h1 = %d,",h1);
  assert(0);

  }


  if (h2 > img->h || h2 < 0) {

  printf ("h2 = %d,",h2);
  assert(0);

  }


  if (w1 > 24 || w1 < 0) {

  printf ("w1 = %d,",w1);
  assert(0);

  }


  if (w2 > 24 || w2 < 0) {

  printf ("w2 = %d\n",w2);
  assert(0);

  }
  */
//  printf ("h1 = %d,h2 = %d,w1 = %d,w2 = %d\n",h1,h2,w1,w2);

  if (h1 - 1 > 0 && w1 - 1 > 0)
  {

    val_A = get_val(img, h1 - 1, w1 - 1);
    if (val_A != 0) {
      //printf ("h1 - 1 = %d, w1 - 1 = %d, A = %lu\n", h1 - 1, w1 - 1, val_A);
    }
  }

  if (h1 - 1 > 0)
  {
    val_B = get_val(img, h1 - 1, w2);
    if (val_B != 0) {
      //printf ("h1 - 1 = %d, w2 = %d, B = %lu\n", h1 - 1, w2, val_B);
    }
  }

  val_C = get_val(img, h2, w2);
  if (val_C != 0) {
    //printf ("h2 = %d, w2 = %d, C = %lu\n", h2, w2, val_C);
  }

  if (w1 - 1 > 0)
  {
    val_D = get_val(img, h2, w1 - 1);
    if (val_D != 0) {
      //printf ("h2 = %d, w1 - 1 = %d, D = %lu\n", h2, w1 - 1, val_D);
    }
  }
/*
  if (val_A - val_B + val_C - val_D != 0) {
  printf ("A = %lu,B = %lu,C = %lu,D = %lu\n",val_A,val_B,val_C,val_D);
  }
*/

  return val_A - val_B + val_C - val_D;
}


// Compute all haar features inside a 24*24 image
Haar* compute_haar_features(Ulong_tab *img, size_t* size){
  Haar* haar_vect = malloc(sizeof(Haar) * 200000);
  Haar* res = haar_vect;

  printf ("type a :\n");
  //type a avec les paramètres (1,i,j,w,h)
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      for (int h = 1; i + h - 1 < 24; h++) {
        for (int w = 1; j - 1 + 2 * w < 24; w++) {

          int sum1 = sum_rect(img,  i,  j,      i + h - 1,  j + w - 1    );
          int sum2 = sum_rect(img,  i,  j + w,  i + h - 1,  j + 2 * w - 1);

          fill_Haar(haar_vect, 1, i, j, w, h, sum1 - sum2, 0, 0);
          haar_vect++;
          //printf ("index = %d\n",haar_vect - res);
          //haar_vect = create_Haar_vect(my_haar);
          //haar_vect = *haar_vect.next;
          if (sum1 - sum2 != 0) {
            //print_Haar(my_haar);
            //printf ("sum1 = %d, sum2 = %d\n",sum1, sum2);
          }

        }
      }
    }
  }



  printf ("type b :\n");
  //type b avec les paramètres (2,i,j,w,h)
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      for (int h = 1; i + h - 1 < 24; h++) {
        for (int w = 1; j - 1 + 3 * w < 24; w++) {

          int sum1 = sum_rect(img, i, j,        i + h - 1,  j + w - 1  );
          int sum2 = sum_rect(img, i, j + w,    i + h - 1,  j + 2*w - 1);
          int sum3 = sum_rect(img, i, j + 2*w,  i + h - 1,  j + 3*w - 1);

          fill_Haar(haar_vect, 2, i, j, w, h, sum1 - sum2 + sum3, 0, 0);
          haar_vect++;
          //printf ("index = %d\n",haar_vect - res);
          //haar_vect = create_Haar_vect(my_haar);
          //haar_vect = *haar_vect.next;
          if (sum1 - sum2 + sum3 != 0) {
            //print_Haar(my_haar);
            //printf ("sum1 = %d, sum2 = %d, sum3 = %d\n",sum1, sum2,sum3);
          }
        }

      }
    }
  }

  printf ("type c :\n");
  //type c avec les paramètres (3,i,j,w,h)
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      for (int h = 1; i + 2*h - 1 < 24; h++) {
        for (int w = 1; j +w-1 < 24; w++) {

          int sum1 = sum_rect(img,  i,      j,  i + h - 1,    j + w - 1);
          int sum2 = sum_rect(img,  i + h,  j,  i + 2*h - 1,  j + w - 1);

          fill_Haar(haar_vect, 3, i, j, w, h, sum1 - sum2, 0, 0);
          haar_vect++;
          //printf ("index = %d\n",haar_vect - res);
          //haar_vect = create_Haar_vect(my_haar);
          //haar_vect = *haar_vect.next;
          if (sum1 - sum2 != 0) {
            //print_Haar(my_haar);
            //printf ("sum1 = %d, sum2 = %d\n",sum1, sum2);   }
          }

        }
      }
    }
  }

  printf ("type d :\n");
  //type d avec les paramètres (4,i,j,w,h)
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      for (int h = 1; i +3* h - 1 < 24; h++) {
        for (int w = 1; j - 1 + w < 24; w++) {

          int sum1 = sum_rect(img,  i,        j,  i + h - 1,    j + w - 1);
          int sum2 = sum_rect(img,  i + h,    j,  i + 2*h - 1,  j + w - 1);
          int sum3 = sum_rect(img,  i + 2*h,  j,  i + 3*h - 1,  j + w - 1);

          fill_Haar(haar_vect, 4, i, j, w, h, sum1 - sum2 + sum3, 0, 0);
          haar_vect++;
          //printf ("index = %d\n",haar_vect - res);
          //haar_vect = create_Haar_vect(my_haar);
          //haar_vect = *haar_vect.next;
          if (sum1 - sum2 + sum3 != 0) {
            //print_Haar(my_haar);
            //printf ("sum1 = %d, sum2 = %d,sum3 = %d\n",sum1, sum2,sum3);
          }
        }

      }
    }
  }

  printf ("type e :\n");
  //type e avec les paramètres (5,i,j,w,h)
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      for (int h = 1; i + 2*h - 1 < 24; h++) {
        for (int w = 1; j - 1 + 2 * w < 24; w++) {

          int sum1 = sum_rect(img, i,     j,     i + h - 1,   j + w - 1);
          int sum2 = sum_rect(img, i + h, j,     i + 2*h - 1, j + w - 1);
          int sum3 = sum_rect(img, i,     j + w, i + h - 1,   j + 2*w - 1);
          int sum4 = sum_rect(img, i + h, j + w, i + 2*h - 1, j + 2*w - 1);

          fill_Haar(haar_vect, 5, i, j, w, h, sum1-sum2-sum3+sum4, 0, 0);
          haar_vect++;
          // FUCKING RES GO FUCK YOURSELF AND DIE !!!
          //printf ("index = %d\n",haar_vect - res);



          //haar_vect = create_Haar_vect(my_haar);
          //haar_vect = *haar_vect.next;
          if (sum1 - sum2 - sum3 + sum4 != 0) {
            //print_Haar(my_haar);
            //printf ("sum1 = %d, sum2 = %d,sum3 = %d, sum4 = %d\n",
            //        sum1, sum2,sum3,sum4);
          }
        }

      }
    }
  }
/*
  for (Haar* i = res; i < haar_vect; ++i)
  {
    print_Haar(*i);

  }

*/

  *size = haar_vect - res;
  //warnx("sortie compute haar");
  return res;
}


// Compute a single haar feature sum
void compute_haar_sum(Ulong_tab *img, Haar* haar){
  int i = haar->i;
  int j = haar->j;
  int h = haar->h;
  int w = haar->w;

  if (i < 0 || j < 0 || h < 0 || w < 0) {
    print_Haar(*haar);
  }
  // Type a:
  if (haar->type == 1) {
    int sum1 = sum_rect(img,  i,  j,      i + h - 1,  j + w - 1    );
    int sum2 = sum_rect(img,  i,  j + w,  i + h - 1,  j + 2 * w - 1);
    haar->sum = sum1 - sum2;
  }
  // Type b:
  else if (haar->type == 2) {
    int sum1 = sum_rect(img, i, j,        i + h - 1,  j + w - 1  );
    int sum2 = sum_rect(img, i, j + w,    i + h - 1,  j + 2*w - 1);
    int sum3 = sum_rect(img, i, j + 2*w,  i + h - 1,  j + 3*w - 1);
    haar->sum = sum1 - sum2 + sum3;
  }
  // Type c:
  else if (haar->type == 3) {
    int sum1 = sum_rect(img,  i,      j,  i + h - 1,    j + w - 1);
    int sum2 = sum_rect(img,  i + h,  j,  i + 2*h - 1,  j + w - 1);
    haar->sum = sum1 - sum2;
  }
  // Type d:
  else if (haar->type == 4){
    int sum1 = sum_rect(img,  i,        j,  i + h - 1,    j + w - 1);
    int sum2 = sum_rect(img,  i + h,    j,  i + 2*h - 1,  j + w - 1);
    int sum3 = sum_rect(img,  i + 2*h,  j,  i + 3*h - 1,  j + w - 1);
    haar->sum = sum1 - sum2 + sum3;
  }
  // Type e:
  else if (haar->type == 5){
    int sum1 = sum_rect(img, i,     j,     i + h - 1,   j + w - 1);
    int sum2 = sum_rect(img, i + h, j,     i + 2*h - 1, j + w - 1);
    int sum3 = sum_rect(img, i,     j + w, i + h - 1,   j + 2*w - 1);
    int sum4 = sum_rect(img, i + h, j + w, i + 2*h - 1, j + 2*w - 1);
    haar->sum = sum1 - sum2 - sum3 + sum4;
  }
  else {
    // unknown feature
  }
}
