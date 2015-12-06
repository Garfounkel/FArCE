# ifndef YOLO_H_
# define YOLO_H_
# include <dirent.h>
# include <stdlib.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <err.h>
# include "ViolaJones/pixel_operations.h"
# include "ViolaJones/haar.h"
# include "ViolaJones/Ulong_tab.h"
# include "ViolaJones/integral_image.h"
# include "ViolaJones/adaboost.h"
# include "Preprocessing/Image_OPs.h"
# include "SDL_operations/SDL_OPs.h"
# include <assert.h>
# include <sys/stat.h>
# include <unistd.h>
# include "ViolaJones/cascade.h"

void init_sdl(void);
SDL_Surface* load_image(char *path);
void print(Ulong_tab* img);
void Ulong_tab_to_SDL(Ulong_tab* tab, SDL_Surface* img);
void yolo(char** path);

#endif
