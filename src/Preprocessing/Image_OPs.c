
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

      Uint8 store = val;

      int vall = (val - m) * 65/ /*ici >>>>*/(var)/*<<<< ici*/ + 127 ;

      if (vall > 255 || (1 && vall < 0)) {


        printf ("%d -> (%d-%d)*127/%d -> %f*127+127 %d\n",store,store,m,var,(double)(val - m)/(2*var), vall);
      }



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

  printf ("max = %d\nmin = %d\n",ma,mi);

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

  display_image(img);

  normalize(img);

  display_image(img);

  invert_grey(img);

  display_image(img);

  return img;

}
