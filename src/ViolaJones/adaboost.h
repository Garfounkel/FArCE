#ifndef ADABOOST_IPOL_H_
# define ADABOOST_IPOL_H_

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

typedef struct Triplet Triplet;

struct Triplet
{

  Ulong_tab* img;

  float weight;

  int is_a_face;
  // 1 = is a face, -1 = isn't a face
  int sum;

};


typedef struct Model Model;

struct Model
{

  float* coefs;

  Haar* haars;

};


typedef struct Caracteristique Caracteristique;
struct Caracteristique{
    int threshold;
    int toggle;
    float error;
    int margin;
};

Triplet create_Triplet(Ulong_tab* img, int weight, int is_a_face);
void generate_Triplet_vect(char* directory, Triplet** imgs, size_t* size);
Model adaboost(Triplet* imgs, size_t size_imgs, int T);
size_t dirLenght(char* path);
char** get_Files_List(char* path, size_t *nb);
void print_images_list(char **list, size_t lenght);
void quickSort(Triplet *begin, Triplet *end);
int atoiKey(char *str, char *key);
Model read_model(char* fname, size_t *nbHaar);

#endif /* !ADABOOST_IPOL_H_ */
