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
size_t dirLenght(char* path);
char** get_Files_List(char* path, size_t *nb);
void print_images_list(char **list, size_t lenght);

# endif
