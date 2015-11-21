
# include "SDL_OPs.h"


void wait_for_keypressed(void)
{

  SDL_Event             event;

  // Infinite loop, waiting for event
  for (;;) {

    // Take an event
    SDL_PollEvent( &event );

    // Switch on event type
    switch (event.type) {
      // Someone closed the window -> leave the program
      case SDL_QUIT: exit(0);
      // Someone pressed a key -> leave the function
      case SDL_KEYDOWN: return;

    default: break;

    }

    // Loop until we got the expected event
  }

}


SDL_Surface* display_image(SDL_Surface *img)
{

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
