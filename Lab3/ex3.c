#include <stdio.h>

unsigned char switch_byte(unsigned char x){

    unsigned char temp,temp2;
    temp = x<<4; // 1011 0000
    temp2 =  x>>4; // 0000 1010      
    x= (temp | temp2);
    
    return x;
}


int main(void){

    // 0xAB
    // 1010  1011
    // 0xBA

    printf("%X tem numero %X\n",0xAB,switch_byte(0xAB));
    return 0;

}