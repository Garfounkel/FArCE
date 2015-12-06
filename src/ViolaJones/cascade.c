#include "cascade.h"

/*
Window* FaceDetection(UlongTab img, Cascade cascade, float scalecoef) {
  Window P;
  P.i1 = ?;
  P.i2 = ?;
  P.j1 = ?;
  P.j2 = ?;

  for (size_t l = 0; l < cascade.lenght; l++) {

  }

}
*/

int faceDetect(Model M, size_t nbHaarsInM, Ulong_tab *img, size_t x, size_t y) {
  int sum = 0;
  for (size_t i = 0; i < nbHaarsInM; i++) {
    if (M.coefs[i] != 0) {
      Haar h = M.haars[i];
      h.i += x;
      h.j += y;
      print_Haar(M.haars[i]);
      compute_haar_sum(img, &h);
      sum += h.sum;
      warnx("sum = %d", sum);
    }
  }
  return sum > 0 ? 1 : -1;
}

int Detect_in_image(SDL_Surface* img, Model M, size_t nbHaarsInM)
{
  img = preprocessing(img);

  Ulong_tab* integ = create_Ulong_tab(img->h, img->w);
  integ = integral_image(img, integ);
  int detected = 0;

  size_t size = min(integ->w, integ->h);
  int m = 1;

  while (m * 24 <= size) {

    Ulong_tab* m_integ;
    Update_m_integ(integ, m, m_integ);

    for (int i = 0; i < m_integ->w - 24; ++i)
    {
      for (int j = 0; j < m_integ->h - 24; ++j)
      {
        if (1 + faceDetect(M, nbHaarsInM, m_integ, i, j)) {
          // trace rectangle
          detected++;
        }
      }
    }

    multiplier++;

  }
  return detected;
}

void Update_m_integ(Ulong_tab* initial, int m, Ulong_tab* new)
{
  free(new->arr);
  free(new);

  new = create_Ulong_tab(img->h/m, img->w/m);

  for (int i = 0; i < new->h; ++i)
  {
    for (int j = 0; j < new->w; ++j)
    {
      set_val(new, get_val(initial, i * m, j * m)/(m * m), i, j);
    }
  }
}
