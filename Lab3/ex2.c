#include <stdio.h>

int odd_ones(unsigned int x) {

    /* escreva seu código aqui */
    int cont = 0;
    while(x>0){
      cont += (x&1);
      x >>=1;
    }
    return cont & 1;
}

int main() {
  printf("%x tem numero %s de bits\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
  printf("%x tem numero %s de bits\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
  return 0;
}