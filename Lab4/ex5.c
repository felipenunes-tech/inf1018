#include <stdio.h>

void dump(unsigned int x) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (x >> i) & 1);
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}

int main() {
    signed char sc = -1;
    unsigned int ui = sc;

    printf("ui = %u\n", ui);
    dump(ui);

    printf("sc = %d\n", sc);
    dump(sc);

    return 0;
}