
# ifndef IMAGE_OPS_H_
# define IMAGE_OPS_H_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include "../ViolaJones/pixel_operations.h"
# include <math.h>
# include "../SDL_operations/SDL_OPs.h"

// Preprocessing:
SDL_Surface* to_grey(SDL_Surface* img);
SDL_Surface* invert_grey(SDL_Surface* img);
Uint8 mean(SDL_Surface* img);
Uint8 standard_var(Uint8 mean, SDL_Surface* img);
void normalize(SDL_Surface* img);
SDL_Surface* preprocessing(SDL_Surface* img);

// Blur and Downscale:
//double* boxesForGauss(double sigma, size_t n);
void Blur(SDL_Surface *img);
SDL_Surface* Downscale(SDL_Surface *img);


//void normalize_Ulong_tab(Ulong_tab* img);


# endif
