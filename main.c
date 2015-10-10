# include <stdio.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "pixel_operations.h"

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

  //  wait_for_keypressed();

  SDL_FreeSurface(surface);

  return 0;
}
