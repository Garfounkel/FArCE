//libsdl-image1.2 ,libsdl-image1.2-dev ,libsdl-ttf2.0-0 ,libsdl-ttf2.0-dev ,libsdl-mixer1.2 ,libsdl-mixer1.2-dev.
//Les options respectives à ajouter à la compilation avec GCC (après -lSDLmain -lSDL) sont :
//-lSDL_image # # include <stdio.h>

# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "pixel_operations.h"

struct Uint64_tab
{
  int h;
  int w;
  unsigned long *arr;
};

struct Uint64_tab* create_Uint64_tab(int h_val, int w_val)
{
  struct Uint64_tab* tab = malloc(sizeof(int) * 2 + sizeof( unsigned long*));
  tab->h = h_val;
  tab->w = w_val;
  tab->arr = malloc(sizeof(unsigned long) * h_val * w_val);
  return tab;
}




long get_val(struct Uint64_tab* tab, int i, int j)
{
  return tab->arr[i * tab->w + j];
}
void set_val(struct Uint64_tab* tab, unsigned long x, int i, int j)
{
  //printf ("begin setval\n");
  //printf ("h = %d\n",i);
  //printf ("w = %d\n",j);
  tab->arr[i * tab->w + j] = x;
}



//# include <warnx.h>

void wait_for_keypressed(void) {
  SDL_Event             event;
  // Infinite loop, waiting for event
  for (;;) {
    // Take an event
    SDL_PollEvent( &event );
    // Switch on event type
    switch (event.type) {
      // Someone pressed a key -> leave the function
    case SDL_KEYDOWN: return;
    default: break;
    }
    // Loop until we got the expected event
  }
}

void init_sdl(void) {
  // Init only the video part
  if( SDL_Init(SDL_INIT_VIDEO)==-1 ) {
    // If it fails, die with an error message
    errx(1,"Could not initialize SDL: %s.\n", SDL_GetError());
  }
  // We don't really need a function for that ...
}

SDL_Surface* load_image(char *path) {
  SDL_Surface          *img;
  // Load an image using SDL_image with format detection
  img = IMG_Load(path);
  if (!img)
    // If it fails, die with an error message
    errx(3, "can't load %s: %s", path, IMG_GetError());
  return img;
}

SDL_Surface* display_image(SDL_Surface *img) {
  SDL_Surface          *screen;
  // Set the window to the same size as the image
  screen = SDL_SetVideoMode(img->w, img->h, 0, SDL_SWSURFACE|SDL_ANYFORMAT);
  if ( screen == NULL ) {
    // error management
    errx(1, "Couldn't set %dx%d video mode: %s\n",
         img->w, img->h, SDL_GetError());
  }
 
  /* Blit onto the screen surface */
  if(SDL_BlitSurface(img, NULL, screen, NULL) < 0)
    warnx("BlitSurface error: %s\n", SDL_GetError());
 
  // Update the screen
  SDL_UpdateRect(screen, 0, 0, img->w, img->h);
 
  // wait for a key
  wait_for_keypressed();
 
  // return the screen for further uses
  return screen;
}


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

SDL_Surface* invert_grey(SDL_Surface *img)// , SDL_Surface *new)
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

struct Uint64_tab* integral_image (SDL_Surface *img, struct Uint64_tab* new)
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


Uint8 sum_rectangle(SDL_Surface* img, int h1, int w1,int h2, int w2){
  Uint8 val_A, val_B, val_C, val_D;
// A B
// D C

// D et C etaient swap

  SDL_GetRGB(getpixel(img,w1 - 1, h1 -1), img->format, &val_A, &val_A, &val_A);
  SDL_GetRGB(getpixel(img,w2, h1 -1), img->format, &val_B, &val_B, &val_B);
  SDL_GetRGB(getpixel(img,w1-1, h2), img->format, &val_D, &val_D, &val_D);
  SDL_GetRGB(getpixel(img,w2, h2), img->format, &val_C, &val_C, &val_C);

  return val_A - val_B + val_C - val_D;
}

int* haar_features(SDL_Surface *img){
  int *my_vect = malloc(sizeof(int));
  int *victor = my_vect;

//type a
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + 2 * w <= 24; w++) {
          int sum1 = sum_rectangle(img, i, i + h - 1, j, j + w - 1);
          int sum2 = sum_rectangle(img, i, i + h - 1, j + w, j + 2 * w - 1);
          *my_vect = sum1 - sum2;
          my_vect++;
        }
      }
    }
  }


//type b
  for (int i = 1; i <= 24; i++) {
    for (int j = 1; j <= 24; j++) {
      for (int h = 1; i + h - 1 <= 24; h++) {
        for (int w = 1; j - 1 + 2 * w <= 24; w++) {
          int sum1 = sum_rectangle(img, i, i + h - 1, j, j + w - 1);
          int sum2 = sum_rectangle(img, i, i + h - 1, j + w, j + 2 * w - 1);
          *my_vect = sum1 - sum2;
          my_vect++;
        }
      }
    }
  }

  return victor;
}

int main(int i, char** path)
{

  if(i > 2 || i == 1)
  {
    printf("please specify an image to display\n");
    return -1;
  }
  // init SDL
  init_sdl();
  // open window

//  SDL_SetVideoMode(640, 480, 0, 0);
  //load image
  SDL_Surface* surface = load_image(path[1]);
  //display image
  display_image(surface);
  //wait for input
  //  wait_for_keypressed();

  to_grey(surface);

  display_image(surface);

  invert_grey(surface);//,surface);

  display_image(surface);

  //printf ("surface->w = %d\n",surface->w);
  struct Uint64_tab* tab = create_Uint64_tab(surface->h, surface->w);

  integral_image(surface, tab);//,surface);

  display_image(surface);
  //  wait_for_keypressed();

  SDL_FreeSurface(surface);

  return 0;
}
