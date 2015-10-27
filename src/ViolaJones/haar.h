# ifndef HAAR_H_
# define HAAR_H_

# include <stdlib.h>
# include <SDL.h>
# include "Ulong_tab.h"
# include "Haar_type.h"

unsigned long sum_rectangle(Ulong_tab* img, int h1, int w1, int h2, int w2);
Haar* compute_haar_features(Ulong_tab *img, long nbFeature);

# endif
