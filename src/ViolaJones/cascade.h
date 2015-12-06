
#ifndef CASCADE_H_
# define CASCADE_H_

# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include <dirent.h>
# include <math.h>
# include "pixel_operations.h"
# include "Haar_type.h"
# include "haar.h"
# include "../SDL_operations/SDL_OPs.h"
# include "../Preprocessing/Image_OPs.h"
# include "integral_image.h"
# include "Ulong_tab.h"
# include "adaboost.h"

typedef struct Windows Windows;
struct Windows{
    size_t i1;
    size_t i2;
    size_t j1;
    size_t j2;
};

void FaceDetection(char* pathimg, char* pathmodel);

int faceDetect(Model M, size_t nbHaarsInM, Ulong_tab *img, size_t x, size_t y);

int Detect_in_image(SDL_Surface* img, Model M, size_t nbHaarsInM);


#endif /* !CASCADE_H_ */
