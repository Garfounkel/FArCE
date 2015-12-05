# ifndef HAAR_STRUCT_DEF
# define HAAR_STRUCT_DEF

# include <err.h>
# include <stdlib.h>

typedef struct Haar Haar;
struct Haar
{
    int type;
    int i;
    int j;
    int w;
    int h;
    long sum;
    long sum_normalized;
    int threshold;
    int polarity;
    float error;
    int margin;
};

Haar create_Haar(int type,
                 int i, int j,
                 int w, int h,
                 long sum,
                 int polarity,
                 long threshold);
void copy_Haar(Haar* source, Haar* dest);
char* Haar_to_str(Haar h);
void print_Haar(Haar h);
void fill_Haar(Haar* haar,
               int type,
               int i, int j,
               int w, int h,
               long sum,
               int polarity,
               long threshold);
int is_present(Haar h);


typedef struct Haar_vect Haar_vect;
struct Haar_vect
{
  Haar haar;
  Haar_vect *next;
};

Haar_vect create_Haar_vect(Haar haar);
void print_Haar_vect(Haar_vect h);

# endif
