# ifndef ADABOOST_H_
# define ADABOOST_H_

# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include <dirent.h>
# include "pixel_operations.h"
# include "Haar_type.h"
# include "haar.h"
# include "../SDL_operations/SDL_OPs.h"

typedef struct Triplet Triplet;
struct Triplet{
    SDL_Surface img;
    int weight;
    int is_a_face; // 1 = is a face, -1 = isn't a face, 42 = not initialized
};

Triplet create_Triplet(SDL_Surface img, int weight);

void adaboost(char* directory);
size_t dirLenght(char* path);
char** get_Files_List(char* path, size_t *nb);
void print_images_list(char **list, size_t lenght);

# endif
