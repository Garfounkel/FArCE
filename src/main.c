//libsdl-image1.2 ,libsdl-image1.2-dev ,libsdl-ttf2.0-0 ,libsdl-ttf2.0-dev ,libsdl-mixer1.2 ,libsdl-mixer1.2-dev.
//Les options respectives à ajouter à la compilation avec GCC (après -lSDLmain -lSDL) sont :
//-lSDL_image # # include <stdio.h>

# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "ViolaJones/pixel_operations.h"
# include "ViolaJones/haar.h"
# include "ViolaJones/Ulong_tab.h"
# include "ViolaJones/integral_image.h"
# include "Preprocessing/Image_OPs.h"

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


int main(int i, char** path)
{

  if(i > 2 || i == 1)
  {
    printf("please specify an image to display\n");
    return -1;
  }

  init_sdl();

  SDL_Surface* surface = load_image(path[1]);

  display_image(surface);

  to_grey(surface);

  display_image(surface);

  invert_grey(surface);

  display_image(surface);

  Ulong_tab* tab = create_Ulong_tab(surface->h, surface->w);

  integral_image(surface, tab);

  display_image(surface);

  SDL_FreeSurface(surface);

  return 0;
}
