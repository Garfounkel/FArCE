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

  //display_image(img);

  normalize(img);

  //display_image(img);

  invert_grey(img);

  //display_image(img);

  return img;

}


// Blur and sub-functions:

/* First try: probably too complicated (keep it for now until a better algo is implemented)
// sigma = standard deviation = radius = r
// n = number of boxes
double* boxesForGauss(double sigma, size_t n) {
  double wIdeal = sqrt((12*sigma*sigma/n)+1);  // Ideal averaging filter width
  double wl = floor(wIdeal);
  if((int)wl % 2 == 0) wl--;
  double wu = wl+2;

  double mIdeal = (12*sigma*sigma - n*wl*wl - 4*n*wl - 3*n)/(-4*wl - 4);
  double m = round(mIdeal);
  // double sigmaActual = sqrt( (m*wl*wl + (n-m)*wu*wu - n)/12 );

  double *sizes = malloc(sizeof(float) * n);
  for(size_t i = 0; i < n; i++)
    sizes[i] = i < m ? wl : wu;
  return sizes;
}

void boxBlur_4 (SDL_Surface *src, SDL_Surface *target, size_t w, size_t h, double r) {
  for(var i=0; i<src.length; i++) target[i] = src[i];
  boxBlurH_4(target, src, w, h, r);
  boxBlurT_4(src, target, w, h, r);
}

void boxBlurH_4 (SDL_Surface *src, SDL_Surface *target, size_t w, size_t h, double r) {
  var iarr = 1 / (r+r+1);
  for(var i=0; i<h; i++) {
    var ti = i*w, li = ti, ri = ti+r;
    var fv = src[ti], lv = src[ti+w-1], val = (r+1)*fv;
    for(var j=0; j<r; j++)
      val += src[ti+j];
    for(var j=0  ; j<=r ; j++) {
      val += src[ri++] - fv       ;   target[ti++] = Math.round(val*iarr);
    }
    for(var j=r+1; j<w-r; j++) {
      val += src[ri++] - src[li++];   target[ti++] = Math.round(val*iarr);
    }
    for(var j=w-r; j<w  ; j++) {
      val += lv        - src[li++];   target[ti++] = Math.round(val*iarr);
    }
  }
}

void boxBlurT_4 (SDL_Surface *src, SDL_Surface *target, size_t w, size_t h, double r) {
  size_t iarr = 1 / (r+r+1);
  for(size_t i = 0; i < w; i++) {
    size_t ti = i, li = ti, ri = ti+r*w;
    size_t fv = src[ti], lv = src[ti+w*(h-1)], val = (r+1)*fv;
    for(var j=0; j<r; j++)
      val += src[ti+j*w];
    for(var j=0  ; j<=r ; j++) {
      val += src[ri] - fv     ;  target[ti] = Math.round(val*iarr);  ri+=w; ti+=w;
    }
    for(var j=r+1; j<h-r; j++) {
      val += src[ri] - src[li];  target[ti] = Math.round(val*iarr);  li+=w; ri+=w; ti+=w;
    }
    for(var j=h-r; j<h  ; j++) {
      val += lv      - src[li];  target[ti] = Math.round(val*iarr);  li+=w; ti+=w;
    }
  }
}

void Blur(SDL_Surface *src, SDL_Surface *target, double r){
  double bxs = boxesForGauss(r, 3);
  size_t w = src->w, h = src->h;
  boxBlur_4 (src, target, w, h, (bxs[0]-1)/2);
  boxBlur_4 (target, src, w, h, (bxs[1]-1)/2);
  boxBlur_4 (src, target, w, h, (bxs[2]-1)/2);
}
*/

// Doesn't work
void Blur(SDL_Surface *img) {
  Uint8 *pixels = (Uint8 *)img->pixels;
  size_t i = 0, width = img->w, height = img->h;

  for(; i < width * (height - 1); i++)
    pixels[i] = (pixels[i] + pixels[i + 1] + pixels[i + width - 1] + pixels[i + width + 2]) >> 2;
  for(; i < width * height; i++)
    pixels[i] = 0;
}

// Downscale img using Blur
SDL_Surface* Downscale(SDL_Surface *img){
  if (img->h != img->w) {
    printf("Can't downscale the image because it's not square (height != weight).\n");
    return NULL;
  }
  if (img->h <= 24) {
    printf("Didn't downscaled image because it's already less than 24x24 pixel wide.\n");
    return img;
  }

  return NULL;
}
