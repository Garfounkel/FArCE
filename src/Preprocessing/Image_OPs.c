
# include "Image_OPs.h"

SDL_Surface* to_grey(SDL_Surface *img)
{
  for(int h = 0; h < img->h; h++)
  {
    for(int w = 0; w < img->w; w++)
    {
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(getpixel(img,w,h), img->format, &r, &g, &b);

      Uint8 m = 0.3 * r + 0.59 * g + 0.11 * b;

      putpixel(img,w,h,SDL_MapRGB(img->format, m, m, m));

    }
  }
  return img;
}

SDL_Surface* invert_grey(SDL_Surface *img)
{
  for (int h = 0; h < img->h; h++)
  {
    for (int w = 0; w < img->w; w++)
    {
      Uint8 m;
      SDL_GetRGB(getpixel(img,w,h),img->format,&m,&m,&m);

      m = -m + 255;

      putpixel(img,w,h,SDL_MapRGB(img->format, m, m, m));
    }
  }
  return img;
}

Uint8 mean(SDL_Surface *img)
{
  unsigned long sum = 0;
  for (int h = 0; h < img->h; h++)
  {
    for (int w = 0; w < img->w; w++)
    {
      Uint8 m;
      SDL_GetRGB(getpixel(img,w,h),img->format,&m,&m,&m);

      sum += m;
    }
  }
  return sum / (img->h * img->w);
}
