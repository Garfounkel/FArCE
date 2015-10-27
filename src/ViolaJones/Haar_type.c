
# include "Haar_type.h"

Haar create_Haar(int type, int i, int j, int w, int h, unsigned long sum)
{
  Haar haar; //= malloc(sizeof(int) * 5 + sizeof(unsigned long));
  haar.type = type;
  haar.i = i;
  haar.j = j;
  haar.w = w;
  haar.h = h;
  haar.sum = sum;
  haar.sum_normalized = 42;
  // 42 Signifie que la valeur n'a pas encore été calculée.
  return haar;
}
