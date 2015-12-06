//libsdl-image1.2 ,libsdl-image1.2-dev ,libsdl-ttf2.0-0 ,libsdl-ttf2.0-dev ,
//libsdl-mixer1.2 ,libsdl-mixer1.2-dev.
//Les options respectives à ajouter à la compilation
//avec GCC (après -lSDLmain -lSDL) sont :
//-lSDL_image # # include <stdio.h>

# include <dirent.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "ViolaJones/pixel_operations.h"
# include "ViolaJones/haar.h"
# include "ViolaJones/Ulong_tab.h"
# include "ViolaJones/integral_image.h"
# include "ViolaJones/adaboost.h"
# include "Preprocessing/Image_OPs.h"
# include "SDL_operations/SDL_OPs.h"
# include <assert.h>
# include <sys/stat.h>
# include <unistd.h>
# include "ViolaJones/cascade.h"

// Load SDL library
void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

// Load an image
SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

// Print an Ulong_tab
void print(Ulong_tab* img)
{
  for (int h = 0; h < img->h; h++)
  {
    for (int w = 0; w < img->w; w++)
    {
      Uint8 m;

      m = get_val(img, h,w);

      printf ("%d|",m);

    }
    printf ("\n");
  }
}

// Convert an Ulongtab to SDL_Surface
void Ulong_tab_to_SDL(Ulong_tab* tab, SDL_Surface* img)
{
  unsigned long ma = 0;

  for (int h = 0; h < img->h; ++h)
  {
    for (int w = 0; w < img->w; ++w)
    {
      unsigned long val = get_val(tab,h,w);

      if(val > ma)
        ma = val;
    }
  }

  for (int h = 0; h < img->h; ++h)
  {
    for (int w = 0; w < img->w; ++w)
    {
      unsigned long val = get_val(tab,h,w);

      val = ma ? 255*val/ma : 255;

      //printf("%lu",val);

      putpixel(img,w,h,SDL_MapRGB(img->format, val, val, val));
    }
  }
}

int main(int i, char** path)
{
// test atoiKey
/*  char *foos = "key = 954cle = 27";
  warnx("atoi: %d\n", atoiKey(foos, "key ="));
  warnx("atoi: %d\n", atoiKey(foos, "cle"));
*/

// test readModel
/*  Model M = read_model("model.farce");
  print_Haar(M.haars[4]);
  warnx("coef = %f\n", M.coefs[4]);
*/

//testing quicksort
/*  Triplet* t = malloc(sizeof(Triplet) * 10);
  for (size_t i = 0; i < 10; i++) {
    t[i].sum = i * pow(-1, i);
  }
  for (size_t i = 0; i < 10; i++) {
    warnx("%d", t[i].sum);
  }
  quickSort(t, t + 10);
  for (size_t i = 0; i < 10; i++) {
    warnx("%d", t[i].sum);
  }
*/

// Parsing
  if(i > 2 || i == 1)
  {
    warnx("please specify an image to display\n");
    return -1;
  }

  init_sdl();

  struct stat buf;
  assert(stat(path[1], &buf) == 0);
  // Arg is a dir
  if(S_ISDIR(buf.st_mode)) {


    Triplet* imgs = NULL;

    size_t size_imgs;

    warnx("gen triplet\n");
    generate_Triplet_vect(path[1], &imgs, &size_imgs);
    warnx("end gen triplet\n");

    /*
      for (size_t i = 0; i < size_imgs; ++i)
    {
      printf ("display %zu\n", i);
      print(imgs[i].img);
    }
    */

    warnx("adaboost");
    warnx("size_imgs = %zu\n", size_imgs);
    if (size_imgs)
      adaboost(imgs, size_imgs, 1000); // 10 = arbitrary number of training rounds


    warnx("finprint\n");
  }
  // Arg is a file
  else {
  SDL_Surface* surface = load_image(path[1]);

  display_image(surface);

// drawWindow test
//  drawWindow(surface, 30, 30, 50);
//  display_image(surface);

// Uncomment if you want to try blur
  //SDL_Surface* blurred = Blur(surface);
  //display_image(blurred);

// Uncomment if you want to try Downscale
  //SDL_Surface* downsampled = Downscale(surface);
  //display_image(downsampled);

// Convert to grey, mean, invert color and normalize our image
    preprocessing(surface);

// Create an Ulong_tab from an image
    Ulong_tab* tab = create_Ulong_tab(surface->h, surface->w);


// Compute the integral image
    integral_image(surface, tab);

// test faceDetect
  Model m;
  m.coefs = malloc(sizeof(float));
  m.coefs[0] = 1;
  m.haars = malloc(sizeof(Haar));
  m.haars[0] = create_Haar(1, 0, 0, 12, 12, -42, -42, -42);
  print_Haar(m.haars[0]);
  int foo = faceDetect(m, 1, tab, 0, 0);
  warnx("face = %d", foo);

// For debugging:
//  print(tab);

    Ulong_tab_to_SDL(tab, surface);
    display_image(surface);

    size_t ez;
    compute_haar_features(tab, &ez);

    printf ("%zu\n",ez);

// Compute all haar features of the image
//  size_t size;

//  compute_haar_features(tab, &size);

    SDL_FreeSurface(surface);

    return 0;
  }
}
