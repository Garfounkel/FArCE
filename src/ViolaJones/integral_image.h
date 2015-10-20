# ifndef INTEGRAL_IMAGE_H_
# define INTEGRAL_IMAGE_H_

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "pixel_operations.h"
# include "Ulong_tab.h"

Ulong_tab* integral_image (SDL_Surface *img, Ulong_tab* new);

# endif
