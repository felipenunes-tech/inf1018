/* programa 1*/
#include <stdio.h>

int main (void) {
  int x = 0xffffffff;// 1111 1111 ou -1 já que tem sinal
  int y = 2; // 0000 0010 ou 0002
  printf("x=%d, y=%d\n", x, y);
  printf("x é menor do que y? %s\n", (x<y)?"sim":"nao");
  return 0;
}