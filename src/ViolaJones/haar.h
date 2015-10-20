# ifndef HAAR_H_
# define HAAR_H_

# include <stdlib.h>
//# include <SDL.h>

# ifndef ULONG_TAB_TYPE_DEF
# define ULONG_TAB_TYPE_DEF

typedef struct my_Ulong_tab
{
  int h;
  int w;
  unsigned long *arr;
} Ulong_tab;

Ulong_tab* create_Ulong_tab(int h_val, int w_val)
{
  Ulong_tab* tab = malloc(sizeof(int) * 2 + sizeof( unsigned long*));
  tab->h = h_val;
  tab->w = w_val;
  tab->arr = malloc(sizeof(unsigned long) * h_val * w_val);
  return tab;
}

long get_val(Ulong_tab* tab, int i, int j)
{
  return tab->arr[i * tab->w + j];
}

void set_val(Ulong_tab* tab, unsigned long x, int i, int j)
{
  //printf ("begin setval\n");
  //printf ("h = %d\n",i);
  //printf ("w = %d\n",j);
  tab->arr[i * tab->w + j] = x;
}

# endif

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

Haar create_Haar(int type, int i, int j, int w, int h, unsigned long sum)
{
  Haar haar; //= malloc(sizeof(int) * 5 + sizeof(unsigned long));
  haar.type = type;
  haar.i = i;
  haar.j = j;
  haar.w = w;
  haar.h = h;
  haar.sum = sum;
  haar.sum_normalized = 42; // 42 Signifie que la valeur n'a pas encore été calculée.
  return haar;
}

# endif

unsigned long sum_rectangle(Ulong_tab* img, int h1, int w1, int h2, int w2);
Haar* compute_haar_features(Ulong_tab *img, long nbFeatures);

# endif
