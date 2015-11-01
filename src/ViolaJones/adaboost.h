# ifndef ADABOOST_H_
# define ADABOOST_H_

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "pixel_operations.h"
# include "Haar_type.h"
# include "haar.h"

void adaboost(char* directory);
char** list_images(char* directory);

# endif
