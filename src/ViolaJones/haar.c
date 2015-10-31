#include <stdio.h>
#include "haar.h"
#include <assert.h>

unsigned long sum_rectangle(Ulong_tab* img, int h1, int w1, int h2, int w2){
  unsigned long val_A = 0, val_B = 0, val_C = 0, val_D = 0;
  // A B
  // D C

  if (h1 > img->h) {

    printf ("h1 = %d,",h1);
    assert(0);

  }


  if (h2 > img->h) {

    printf ("h2 = %d,",h2);
assert(0);

  }


  if (w1 > img->w) {

    printf ("w1 = %d,",w1);
assert(0);

  }


  if (w2 > img->w) {

    printf ("w2 = %d\n",w2);
assert(0);

  }


  if (h1 - 1 > 0 && w1 - 1 > 0)
  {
    val_A = get_val(img, h1 - 1, w1 - 1);
    // previous code :
    //SDL_GetRGB(getpixel(img,w1-1, h1-1), img->format, &val_A, &val_A, &val_A);
  }

  if (h1 - 1 > 0)
  {
    val_B = get_val(img, h1 - 1, w2);
    // previous code :
    //SDL_GetRGB(getpixel(img,w2, h1 -1), img->format, &val_B, &val_B, &val_B);
  }

  val_C = get_val(img, h2, w2);
  // previous code :
  //SDL_GetRGB(getpixel(img,w2, h2), img->format, &val_C, &val_C, &val_C);

  if (w1 - 1 > 0)
  {
    val_D = get_val(img, h2, w1 - 1);
    // previous code :
    //SDL_GetRGB(getpixel(img,w1-1, h2), img->format, &val_D, &val_D, &val_D);
  }

  return val_A - val_B + val_C - val_D;
}

Haar_vect compute_haar_features(Ulong_tab *img){
  //Haar *my_vect = malloc((sizeof(int) * 4 + sizeof(unsigned long)) * nbFeature);
  //Haar *res = my_vect;
  Haar_vect haar_vect;
  Haar_vect res = haar_vect;

  //type a avec les paramètres (1,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + 2 * w <= 24; w++) {

          int sum1 = sum_rectangle(img, i, i + h - 1, j,     j + w - 1);
          int sum2 = sum_rectangle(img, i, i + h - 1, j + w, j + 2 * w - 1);

          Haar my_haar = create_Haar(1, i, j, w, h, sum1 - sum2);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
          print_Haar(my_haar);
        }
      }
    }
  }


  //type b avec les paramètres (2,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + 3 * w <= 24; w++) {

          int sum1 = sum_rectangle(img, i, i + h - 1, j,     j + w - 1);
          int sum2 = sum_rectangle(img, i, i + h - 1, j + w, j + 2 * w - 1);
          int sum3 = sum_rectangle(img, i, i+h-1,     j+2*w, j+3*w-1);

          Haar my_haar = create_Haar(2, i, j, w, h, sum1 - sum2 + sum3);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
          print_Haar(my_haar);
        }
      }
    }
  }

  //type c avec les paramètres (3,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + 2*h - 1 <= 24; h++) {
        for (int w = 1; j +w-1 <= 24; w++) {

          int sum1 = sum_rectangle(img, i,   i + h - 1,   j, j + w - 1);
          int sum2 = sum_rectangle(img, i+h, i +2* h - 1, j, j + w - 1);

          Haar my_haar = create_Haar(3, i, j, w, h, sum1 - sum2);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
          print_Haar(my_haar);
        }
      }
    }
  }


  //type e avec les paramètres (5,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + 2*h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + 2 * w <= 24; w++) {

          int sum1 = sum_rectangle(img, i,   i + h - 1,   j,   j + w - 1);
          int sum2 = sum_rectangle(img, i+h, i +2* h - 1, j,   j + w - 1);
          int sum3 = sum_rectangle(img, i,   i+h-1,       j+w, j+2*w-1);
          int sum4 = sum_rectangle(img, i+h, i+2*h-1,     j+w, j+2*w-1);

          Haar my_haar = create_Haar(5, i, j, w, h, sum1 - sum2 - sum3 + sum4);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
          print_Haar(my_haar);
        }
      }
    }
  }


  //type d avec les paramètres (4,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i +3* h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + w <= 24; w++) {

          int sum1 = sum_rectangle(img, i,     i + h - 1,   j, j + w - 1);
          int sum2 = sum_rectangle(img, i+h,   i + 2*h - 1, j, j +w - 1);
          int sum3 = sum_rectangle(img, i+2*h, i+3*h-1,     j, j+w-1);

          Haar my_haar = create_Haar(4, i, j, w, h, sum1 - sum2 + sum3);
          haar_vect = create_Haar_vect(my_haar);
          haar_vect = *haar_vect.next;
          print_Haar(my_haar);
        }
      }
    }
  }

  return res;
}
