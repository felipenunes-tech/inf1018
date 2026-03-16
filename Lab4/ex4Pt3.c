/* programa 3*/
#include <stdio.h>

int main (void) {
  int x = 0xffffffff; // Considera o bit mais a esquerda
  unsigned int y = 2; // continua 2
  printf("x=%u, y=%u\n", x, y);
  printf("x é menor do que y? %s\n", (x<y)?"sim":"nao");
  return 0;
}