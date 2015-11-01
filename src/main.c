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

//# include <warnx.h>

//load library
void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

//load image
SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

//affiche Ulong_tab
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

// convert a Ulongtab to SDL_Surface//
void Ulong_tab_to_SDL(Ulong_tab* tab, SDL_Surface* img)
{
  unsigned long ma;

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

      printf("%lu",val);

      putpixel(img,w,h,SDL_MapRGB(img->format, val, val, val));
    }
  }
}

int main(int i, char** path)
{

  if(i > 2 || i == 1)
  {
    printf("please specify an image to display\n");
    return -1;
  }

  size_t *lenght = malloc(sizeof(int));
  char **list = get_Files_List("../database", lenght);
  print_images_list(list, *lenght);

  init_sdl();

  SDL_Surface* surface = load_image(path[1]);

  display_image(surface);

  preprocessing(surface);

  Ulong_tab* tab = create_Ulong_tab(surface->h, surface->w);

  integral_image(surface, tab);

//  print(tab);

  Ulong_tab_to_SDL(tab, surface);

  display_image(surface);

  compute_haar_features(tab);

  SDL_FreeSurface(surface);

  printf("\n");

  return 0;
}
