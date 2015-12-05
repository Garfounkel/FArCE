
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
SDL_Surface* CreateTargetImgFormat(SDL_Surface* source, int w, int h);
SDL_Surface* Blur(SDL_Surface *source);
SDL_Surface* Downscale(SDL_Surface *img);

// Draw Window
void drawLine(SDL_Surface *Screen, int x0, int y0, int x1, int y1, Uint32 pixel);
void drawWindow(SDL_Surface *src, int x, int y, size_t sidelenght);

# endif
