# ifndef ULONG_TAB_TYPE_DEF
# define ULONG_TAB_TYPE_DEF

# include <stdlib.h>

typedef struct my_Ulong_tab
{
  int h;
  int w;
  unsigned long *arr;
} Ulong_tab;

Ulong_tab* create_Ulong_tab(int h_val, int w_val);

long get_val(Ulong_tab* tab, int i, int j);

void set_val(Ulong_tab* tab, unsigned long x, int i, int j);

# endif
