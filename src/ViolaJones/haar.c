#include <stdio.h>
#include "haar.h"
#include <assert.h>

long sum_rectangle(Ulong_tab* img, int h1, int w1, int h2, int w2){
  unsigned long val_A = 0, val_B = 0, val_C = 0, val_D = 0;
  // A B
  // D C

  if (h1 > 24) {

    printf ("h1 = %d,",h1);
    assert(0);

  }


  if (h2 > img->h) {

    printf ("h2 = %d,",h2);
assert(0);

  }


  if (w1 > 24) {

    printf ("w1 = %d,",w1);
assert(0);

  }


  if (w2 > 24) {

    printf ("w2 = %d\n",w2);
assert(0);

  }


  if (h1 - 1 > 0 && w1 - 1 > 0)
  {
    val_A = get_val(img, h1 - 1, w1 - 1);
    if (val_A != 0) {
      printf ("h1 - 1 = %d, w1 - 1 = %d, A = %lu\n", h1 - 1, w1 - 1, val_A);
    }
    // previous code :
    //SDL_GetRGB(getpixel(img,w1-1, h1-1), img->format, &val_A, &val_A, &val_A);
  }

  if (h1 - 1 > 0)
  {
    val_B = get_val(img, h1 - 1, w2);
     if (val_B != 0) {
      printf ("h1 - 1 = %d, w2 = %d, B = %lu\n", h1 - 1, w2, val_B);
    }
    // previous code :
    //SDL_GetRGB(getpixel(img,w2, h1 -1), img->format, &val_B, &val_B, &val_B);
  }

  val_C = get_val(img, h2, w2);
    if (val_C != 0) {
      printf ("h2 = %d, w2 = %d, C = %lu\n", h2, w2, val_C);
    }
  // previous code :
  //SDL_GetRGB(getpixel(img,w2, h2), img->format, &val_C, &val_C, &val_C);

  if (w1 - 1 > 0)
  {
    val_D = get_val(img, h2, w1 - 1);
    if (val_D != 0) {
      printf ("h2 = %d, w1 - 1 = %d, D = %lu\n", h2, w1 - 1, val_D);
    }
    // previous code :
    //SDL_GetRGB(getpixel(img,w1-1, h2), img->format, &val_D, &val_D, &val_D);
  }
/*
  if (val_A - val_B + val_C - val_D != 0) {
    printf ("A = %lu,B = %lu,C = %lu,D = %lu\n",val_A,val_B,val_C,val_D);
}
*/

  return val_A - val_B + val_C - val_D;
}

Haar_vect compute_haar_features(Ulong_tab *img){
  //Haar *my_vect = malloc((sizeof(int) * 4 + sizeof(unsigned long)) * nbFeature);
  //Haar *res = my_vect;
  Haar_vect haar_vect;
  Haar_vect res = haar_vect;

  printf ("type a :\n");
  //type a avec les paramètres (1,i,j,w,h)
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < 24; j++) {
      for (int h = 1; i + h - 1 < 24; h++) {
        for (int w = 1; j - 1 + 2 * w < 24; w++) {

          int sum1 = sum_rectangle(img, i, j, i + h - 1, j+ w - 1);

          int sum2 = sum_rectangle(img, i, j + w, i + h - 1,     j + 2 * w - 1);


          Haar my_haar = create_Haar(1, i, j, w, h, sum1 - sum2);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
          if (sum1 - sum2 != 0) {
//            print_Haar(my_haar);
            printf ("sum1 = %d, sum2 = %d\n",sum1, sum2);
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
          int sum1 = sum_rectangle(img, i, j, i + h - 1,      j + w - 1);

          int sum2 = sum_rectangle(img, i, j + w, i + h - 1,  j + 2 * w - 1);

          int sum3 = sum_rectangle(img, i, j+2*w, i+h-1,      j+3*w-1);



          Haar my_haar = create_Haar(2, i, j, w, h, sum1 - sum2 + sum3);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
          if (sum1 - sum2 + sum3 != 0) {
//          print_Haar(my_haar);
          printf ("sum1 = %d, sum2 = %d, sum3 = %d\n",sum1, sum2,sum3);
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
          int sum1 = sum_rectangle(img, i,   j, i + h - 1,    j + w - 1);

          int sum2 = sum_rectangle(img, i+h, j, i +2* h - 1,  j + w - 1);



          Haar my_haar = create_Haar(3, i, j, w, h, sum1 - sum2);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
           if (sum1 - sum2 != 0) {
//         print_Haar(my_haar);

            printf ("sum1 = %d, sum2 = %d\n",sum1, sum2);   }
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

          int sum1 = sum_rectangle(img, i,   j, i + h - 1,      j + w - 1);

          int sum2 = sum_rectangle(img, i+h, j, i +2* h - 1,    j + w - 1);

          int sum3 = sum_rectangle(img, i,   j+w, i+h-1,        j+2*w-1);

          int sum4 = sum_rectangle(img, i+h, j+w, i+2*h-1,      j+2*w-1);



          Haar my_haar = create_Haar(5, i, j, w, h, sum1 - sum2 - sum3 + sum4);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
         if (sum1 - sum2 - sum3 + sum4 != 0) {
//           print_Haar(my_haar);
           printf ("sum1 = %d, sum2 = %d,sum3 = %d, sum4 = %d\n",sum1, sum2,sum3,sum4);
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

          int sum1 = sum_rectangle(img, i,     j, i + h - 1,    j + w - 1);

          int sum2 = sum_rectangle(img, i+h,   j, i + 2*h - 1,  j +w - 1);

          int sum3 = sum_rectangle(img, i+2*h, j, i+3*h-1,      j+w-1);



          Haar my_haar = create_Haar(4, i, j, w, h, sum1 - sum2 + sum3);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
           if (sum1 - sum2 + sum3 != 0) {
//         print_Haar(my_haar);
         printf ("sum1 = %d, sum2 = %d,sum3 = %d\n",sum1, sum2,sum3);
           }
        }

      }
    }
  }

  return res;
}
