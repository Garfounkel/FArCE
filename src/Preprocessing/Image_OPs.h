
# ifndef IMAGE_OPS_H_
# define IMAGE_OPS_H_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "../ViolaJones/pixel_operations.h"

SDL_Surface* to_grey(SDL_Surface *img);
SDL_Surface* invert_grey(SDL_Surface *img);
Uint8 mean(SDL_Surface *img);

# endif
