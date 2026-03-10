#include <stdio.h>

//A
unsigned char switch_byte(unsigned char x){
    unsigned char temp,temp2;
    temp = x<<4; // 1011 0000
    temp2 =  x>>4; // 0000 1010      
    x= (temp | temp2);
    return x;
}

//B
unsigned char rotate_left(unsigned char x, int n){
    unsigned char temp,temp2;
    temp = x<<n;
    temp2 = x>>(8-n);
    x = (temp | temp2);
    return x;
}

int main(void){
//A)
    // 0xAB
    // 1010  1011
    // 0xBA
    printf("%X vira %X\n",0xAB,switch_byte(0xAB));
//B)
    printf("%X deslocando %d bits vira %X\n",0x61,1,rotate_left(0x61,1));
    printf("%X deslocando %d bits vira %X\n",0x61,2,rotate_left(0x61,2));
    printf("%X deslocando %d bits vira %X\n",0x61,7,rotate_left(0x61,7));


    return 0;

}