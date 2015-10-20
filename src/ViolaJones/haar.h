# ifndef HAAR_H_
# define HAAR_H_

# include <stdlib.h>
# include <SDL.h>

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

unsigned long sum_rectangle(Ulong_tab* img, int h1, int w1, int h2, int w2);
int* haar_features(Ulong_tab *img);

# endif
