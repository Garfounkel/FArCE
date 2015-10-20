
#include "haar.h"

unsigned long sum_rectangle(Ulong_tab* img, int h1, int w1, int h2, int w2){
  unsigned long val_A, val_B, val_C, val_D;
  // A B
  // D C

  val_A = get_val(img, h1 - 1, w1 - 1);
  // previous code : SDL_GetRGB(getpixel(img,w1 - 1, h1 -1), img->format, &val_A, &val_A, &val_A);

  val_B = get_val(img, h1 - 1, w2);
  // previous code : SDL_GetRGB(getpixel(img,w2, h1 -1), img->format, &val_B, &val_B, &val_B);

  val_C = get_val(img, h2, w2);
  // previous code : SDL_GetRGB(getpixel(img,w2, h2), img->format, &val_C, &val_C, &val_C);

  val_D = get_val(img, h2, w1 - 1);
  // previous code : SDL_GetRGB(getpixel(img,w1-1, h2), img->format, &val_D, &val_D, &val_D);

  return val_A - val_B + val_C - val_D;
}

Haar* compute_haar_features(Ulong_tab *img, long nbFeatures){
  Haar *my_vect = malloc((sizeof(int) * 4 + sizeof(unsigned long)) * nbFeatures);
  Haar *res = my_vect;

  //type a avec les paramètres (1,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + 2 * w <= 24; w++) {

          int sum1 = sum_rectangle(img, i, i + h - 1, j, j + w - 1);
          int sum2 = sum_rectangle(img, i, i + h - 1, j + w, j + 2 * w - 1);

          Haar my_haar = create_Haar(1, i, j, w, h, sum1 - sum2);
          *my_vect = my_haar;
          my_vect++;
        }
      }
    }
  }


  //type b avec les paramètres (2,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + 2 * w <= 24; w++) {

          int sum1 = sum_rectangle(img, i, i + h - 1, j, j + w - 1);
          int sum2 = sum_rectangle(img, i, i + h - 1, j + w, j + 2 * w - 1);
          int sum3 = sum_rectangle(img, i, i+h-1,j+2*w, j+3*w-1);

          Haar my_haar = create_Haar(2, i, j, w, h, sum1 - sum2 + sum3);
          *my_vect = my_haar;
          my_vect++;
        }
      }
    }
  }

  //type c avec les paramètres (3,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + 2*h - 1 <= 24; h++) {
        for (int w = 1; j +w-1 <= 24; w++) {

          int sum1 = sum_rectangle(img, i, i + h - 1, j, j + w - 1);
          int sum2 = sum_rectangle(img, i+h, i +2* h - 1, j, j +w - 1);

          Haar my_haar = create_Haar(3, i, j, w, h, sum1 - sum2);
          *my_vect = my_haar;
          my_vect++;
        }
      }
    }
  }

  //type d avec les paramètres (4,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i +3* h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + w <= 24; w++) {
          int sum1 = sum_rectangle(img, i, i + h - 1, j, j + w - 1);
          int sum2 = sum_rectangle(img, i+h, i + 2*h - 1, j, j +w - 1);
          int sum3 = sum_rectangle(img, i+2*h,i+3*h-1,j,j+w-1);

          Haar my_haar = create_Haar(4, i, j, w, h, sum1 - sum2 + sum3);
          *my_vect = my_haar;
          my_vect++;
        }
      }
    }
  }

  //type e avec les paramètres (5,i,j,w,h)
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + 2*h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + 2 * w <= 24; w++) {
          int sum1 = sum_rectangle(img, i, i + h - 1, j, j + w - 1);
          int sum2 = sum_rectangle(img, i+h, i +2* h - 1, j, j + w - 1);
          int sum3 = sum_rectangle(img,i,i+h-1,j+w,j+2*w-1);
          int sum4 = sum_rectangle(img,i+h,i+2*h-1,j+w,j+2*w-1);

          Haar my_haar = create_Haar(5, i, j, w, h, sum1 - sum2 - sum3 + sum4);
          my_haar.type = 5;
          my_haar.i = i;
          my_haar.j = j;
          my_haar.w = w;
          my_haar.h = h;
          my_haar.sum = sum1 - sum2 - sum3 + sum4;

          *my_vect = my_haar;
          my_vect++;
        }
      }
    }
  }

  return res;
}
