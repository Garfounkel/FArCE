
# include "Ulong_tab.h"

// Creates an Ulong_tab and initialize its attributes
Ulong_tab* create_Ulong_tab(int h_val, int w_val)
{
  Ulong_tab* tab = malloc(sizeof(int) * 2 + sizeof( unsigned long*));
  tab->h = h_val;
  tab->w = w_val;
  tab->arr = malloc(sizeof(unsigned long) * h_val * w_val);
  return tab;
}

// Get the value of the pixel at a given position
long get_val(Ulong_tab* tab, int i, int j)
{
  return tab->arr[i * tab->w + j];
}

// Set the value of the pixel at a given position
void set_val(Ulong_tab* tab, unsigned long x, int i, int j)
{
  tab->arr[i * tab->w + j] = x;
}
