/* programa 2*/
#include <stdio.h>

int main (void) {
  unsigned int x = 0xffffffff; // ele irá considerar que o bit mais significativo é digito
  unsigned int y = 2; // 0000 0010 continua sendo 2
  printf("x=%u, y=%u\n", x, y);
  printf("x é menor do que y? %s\n", (x<y)?"sim":"nao");
  return 0;
}