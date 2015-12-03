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

#endif /* !ADABOOST_IPOL_H_ */
