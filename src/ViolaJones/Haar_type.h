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
  unsigned long sum;
  unsigned long sum_normalized;
};

Haar create_Haar(int type, int i, int j, int w, int h, unsigned long sum);

# endif
