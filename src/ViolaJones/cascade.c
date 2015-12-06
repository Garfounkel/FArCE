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
