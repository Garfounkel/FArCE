# include "Image_OPs.h"

SDL_Surface* to_grey(SDL_Surface* img)
{
  for(int h = 0; h < img->h; h++)
  {
    for(int w = 0; w < img->w; w++)
    {
      Uint8 r;
      Uint8 g;
      Uint8 b;
      SDL_GetRGB(getpixel(img, w, h), img->format, &r, &g, &b);

      Uint8 m = 0.3*r + 0.59*g + 0.11*b;

      putpixel(img,w,h,SDL_MapRGB(img->format, m, m, m));

    }
  }
  return img;
}

SDL_Surface* invert_grey(SDL_Surface* img)
{
  for (int h = 0; h < img->h; h++)
  {
    for (int w = 0; w < img->w; w++)
    {
      Uint8 m;
      SDL_GetRGB(getpixel(img, w, h), img->format, &m, &m, &m);

      m = 255 - m;

      putpixel(img, w, h, SDL_MapRGB(img->format, m, m, m));
    }
  }
  return img;
}

Uint8 mean(SDL_Surface* img)
{
  unsigned long sum = 0;
  for (int h = 0; h < img->h; h++)
  {
    for (int w = 0; w < img->w; w++)
    {
      Uint8 m;
      SDL_GetRGB(getpixel(img, w, h), img->format, &m, &m, &m);

      sum += m;
    }
  }
  return sum/(img->h*img->w);
}

Uint8 standard_var(Uint8 mean, SDL_Surface* img)
{
  unsigned long sum = 0;

  for (int h = 0; h < img->h; h++)
  {
    for (int w = 0; w < img->w; w++)
    {
      Uint8 m;
      SDL_GetRGB(getpixel(img, w, h), img->format, &m, &m, &m);
      int tmp = m - mean;
      //printf ("tmp = %d - %d = %d\n",m,mean,tmp);
      sum += tmp*tmp;
    }
  }

  printf ("sum = %lu\n",sum);
  printf ("N = %d\n",(img->h*img->w));
  printf ("post sqrt = %lu\n", sum/(img->h*img->w));

  return((Uint8) sqrt(sum/(img->h*img->w)));
}

void standardize(SDL_Surface* img)
{
  Uint8 m = mean(img);
  //printf ("mean = %d\n", m);
  Uint8 var = standard_var(m, img);
  //printf ("var = %d\n", var);

  for (int h = 0; h < img->h; h++)
  {
    for (int w = 0; w < img->w; w++)
    {
      Uint8 val;
      SDL_GetRGB(getpixel(img, w, h), img->format, &val, &val, &val);

      //Uint8 store = val;

      int vall = (val - m) * 65/ /*ici >>>>*/(var)/*<<<< ici*/ + 127 ;



      putpixel(img, w, h, SDL_MapRGB(img->format, vall, vall, vall));
    }
  }

}

Uint8 max(SDL_Surface* img)
{
  Uint8 max;

  for (int h = 0; h < img->h; ++h)
  {
    for (int w = 0; w < img->w; ++w)
    {
      Uint8 val;

      SDL_GetRGB(getpixel(img, w, h), img->format, &val, &val, &val);

      if(val > max)
      {
        max = val;
      }

    }
  }
  return max;
}

Uint8 min(SDL_Surface* img)
{
  Uint8 min;

  for (int h = 0; h < img->h; ++h)
  {
    for (int w = 0; w < img->w; ++w)
    {
      Uint8 val;

      SDL_GetRGB(getpixel(img, w, h), img->format, &val, &val, &val);

      if(val < min)
      {
        min = val;
      }

    }
  }
  return min;
}

void normalize(SDL_Surface* img)
{
  Uint8 mi = min(img);
  Uint8 ma = max(img);

  //printf ("max = %d\nmin = %d\n",ma,mi);

  for (int h = 0; h < img->h; ++h)
  {
    for (int w = 0; w < img->w; ++w)
    {
      Uint8 val;

      SDL_GetRGB(getpixel(img, w, h), img->format, &val, &val, &val);

      val = (ma - mi)? (val - mi)*255/(ma - mi) : 255;

      putpixel(img, w, h, SDL_MapRGB(img->format, val, val, val));
    }
  }
}


SDL_Surface* preprocessing(SDL_Surface* img)
{

  to_grey(img);

  //display_image(img);

  normalize(img);

  //display_image(img);

  invert_grey(img);

  //display_image(img);

  return img;

}

// Return target surface so that it is the same format as source surface.
SDL_Surface* CreateTargetImgFormat(SDL_Surface* source, int w, int h) {
  int    depth = source->format->BitsPerPixel;
  Uint32 Rmask = source->format->Rmask;
  Uint32 Gmask = source->format->Gmask;
  Uint32 Bmask = source->format->Bmask;
  Uint32 Amask = source->format->Amask;
  return SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, depth, Rmask, Gmask, Bmask, Amask);
}

// Blur
SDL_Surface* Blur(SDL_Surface* source) {
  SDL_Surface* target = CreateTargetImgFormat(source, source->w, source->h);

  // Compute the average of every group of 9 pixels surronding a single pixel p.
  for(int y = 0; y < source->h; y++){
    for(int x = 0; x < source->w; x++)
    {
      unsigned r = 0, g = 0, b = 0;
      Uint8 rt, gt, bt;

      for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <= y+1; j++) {
          SDL_GetRGB(getpixel(source, i, j), source->format, &rt, &gt, &bt);
          r += rt;
          g += gt;
          b += bt;
        }
      }
      r /= 9;
      g /= 9;
      b /= 9;
      unsigned avg = SDL_MapRGB(target->format, r, g, b);

      putpixel(target,x, y, avg);
    }
  }
  return target;
}

// Downscale img
SDL_Surface* Downscale(SDL_Surface *source)
{
  SDL_Surface *target = CreateTargetImgFormat(source, 24, 24);

  double sx = (24  / (double)(source->w)); // Scale factor for width
  double sy = (24 / (double)(source->h)); // Scale factor for height

  for(int y = 0; y < source->h; y++)
    for(int x = 0; x < source->w; x++)
      for(int o_y = 0; o_y < sy; ++o_y)
        for(int o_x = 0; o_x < sx; ++o_x)
          putpixel(target, (int)(sx * x) + o_x, (int)(sy * y) + o_y, getpixel(source, x, y));

  return target;
}
