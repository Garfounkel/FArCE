//libsdl-image1.2 ,libsdl-image1.2-dev ,libsdl-ttf2.0-0 ,libsdl-ttf2.0-dev ,libsdl-mixer1.2 ,libsdl-mixer1.2-dev.
//Les options respectives à ajouter à la compilation avec GCC (après -lSDLmain -lSDL) sont :
//-lSDL_image # # include <stdio.h>

# include "integral_image.h"

Ulong_tab* integral_image (SDL_Surface *img, Ulong_tab* new)
{
  for(int h = 0; h <= img->h; h++)
  {
    for(int w = 0; w <= img->w; w++)
    {
      unsigned long r, sr = 0;

      {
        Uint8 tmp;
        SDL_GetRGB(getpixel(img,w,h), img->format, &tmp, &tmp, &tmp);

        sr = r = tmp;

        if (w >= 149 && h >= 149)
          printf ("%ld->%ld", r, r);
      }

      if (w <= img->w && h - 1 >= 0)
      {
        r = get_val(new, h - 1, w);

        if (w >= 149 && h >= 149)
          printf ("+%ld",r);

        sr += r;
      }


      if (w - 1 >= 0 && h <= img->h)
      {
        r = get_val(new, h, w - 1);

        if (w >= 149 && h >= 149)
          printf ("+%ld",r);

        sr += r;
      }


      if (w - 1 >= 0 && h - 1 >= 0)
      {
        r = get_val(new, h - 1, w - 1);

        if (w >= 149 && h >= 149)
          printf ("-%ld",r);

        sr -= r;
      }


      set_val(new, sr, h, w);


      if (w >= 149 && h >= 149)
        printf("->%ld|", get_val(new,h,w));

    }

    if (h >= 149)
      printf("\n");

  }

  return new;
}
