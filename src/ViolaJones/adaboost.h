#ifndef ADABOOST_IPOL_H_
# define ADABOOST_IPOL_H_

#include "Ulong_tab.h"
#include "Haar_type.h"
#include "haar.h"
#include <math.h>
#include <err.h>

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
Model adaboost(Triplet* imgs, size_t len_imgs);
size_t dirLenght(char* path);
char** get_Files_List(char* path, size_t *nb);
void print_images_list(char **list, size_t lenght);


#endif /* !ADABOOST_IPOL_H_ */
