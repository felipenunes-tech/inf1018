#include <stdio.h>

void dump (void *p, int n);

int main() {
  char c1 = 1;
  char c2 = '1'
  ;
  int i = 1;
  char v[] = "1";

  printf("valor de c1: %d -> na memória: ",c1);
  dump(&c1, sizeof(c1));

  printf("\nvalor de c2: %d -> na memória: ",c2);
  dump(&c2, sizeof(c2));

  printf("\nvalor de i: %d -> na memória: ",i);
  dump(&i, sizeof(i));

  printf("\nvalor de v: %s -> na memória: ",v);
  dump(v, sizeof(v));

  printf("\n");
  return 0;
}
