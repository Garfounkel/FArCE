# ifndef HAAR_STRUCT_DEF
# define HAAR_STRUCT_DEF

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
};

Haar create_Haar(int type, int i, int j, int w, int h, long sum);
void print_Haar(Haar h);
void fill_Haar(Haar* haar, int type, int i, int j, int w, int h, long sum);
int is_present(Haar h, long threshold);


typedef struct Haar_vect Haar_vect;
struct Haar_vect
{
  Haar haar;
  Haar_vect *next;
};

Haar_vect create_Haar_vect(Haar haar);
void print_Haar_vect(Haar_vect h);

# endif
