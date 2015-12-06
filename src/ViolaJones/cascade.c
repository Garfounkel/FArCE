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

SDL_Surface* load_image(char *path)
{

  SDL_Surface          *img;

  // Load an image using SDL_image with format detection
  img = IMG_Load(path);

  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());

  return img;

}


void FaceDetection(char* pathimg, char* pathmodel)
{
  SDL_Surface* surface = load_image(pathimg);
  size_t nbHaarsinM = 0;
  Model M = read_model(pathmodel, &nbHaarsinM);

  display_image(surface);

  printf ("%d visage(s) detectés\n", Detect_in_image(surface, M, nbHaarsinM));

  display_image(surface);

  SDL_FreeSurface(surface);
}


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


void Update_m_integ(Ulong_tab* initial, size_t m, Ulong_tab* new)
{
  //warnx("free");


  if (new)
    free(new->arr);
  free(new);

  //warnx("create_Ulong_tab");
  new = create_Ulong_tab(initial->h/m, initial->w/m);


  for (int i = 0; i < new->h; ++i)
  {

    for (int j = 0; j < new->w; ++j)
    {
      //warnx("set get val");

      set_val(new, get_val(initial, i * m, j * m)/(m * m), i, j);

    }

  }

}



int Detect_in_image(SDL_Surface* img, Model M, size_t nbHaarsInM)
{

  img = preprocessing(img);


  Ulong_tab* integ = create_Ulong_tab(img->h, img->w);

  integ = integral_image(img, integ);

  int detected = 0;


  size_t size = (integ->w > integ->h)? integ->h : integ->w;

  size_t m = 1;


  Ulong_tab* m_integ = NULL;


  while (m * 24 <= size) {


    Update_m_integ(integ, m, m_integ);


    for (int i = 0; i < m_integ->w - 24; ++i)
    {

      for (int j = 0; j < m_integ->h - 24; ++j)
      {

        if (1 + faceDetect(M, nbHaarsInM, m_integ, i, j)) {
          drawWindow(img, i, j, 24 * m);
          warnx("face detected");
          detected++;

        }

      }

    }


    m++;


  }

  return detected;

}
