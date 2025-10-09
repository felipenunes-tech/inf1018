/* Felipe Eduardo Nunes da Silva : 2320615 : 33WA */

#include <stdio.h>
#include <string.h>
// #include "testebigint.c"

#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS/8];

void big_val (BigInt res, long val){
    memset(res, 0, sizeof(BigInt)); // inicializa o BigInt com zeros
    unsigned indice = 0; 
    unsigned qt_bytes = NUM_BITS / 8;

    while(val && indice < qt_bytes){
       unsigned ultimoByte = val & 0xff;
       res[indice] = ultimoByte;
       val = val>>8;
       indice++;

    }

}

void big_comp2(BigInt res, BigInt a){
    unsigned indice = 0;
    unsigned qt_bytes = NUM_BITS / 8;

    while(indice < qt_bytes){
         res[indice] = ~a[indice];
         indice++;
    }
    // adicionar 1 e caso ocorra overflow, propagar o um pelo vetor
    unsigned um = 1;
    indice = 0;

    while (indice < qt_bytes && um) {
        // salvo em uma variavel maior que char para evitar overflow
        unsigned soma = res[indice] + um;
        //pego o byte menos significativo, e atribuo ao res
        res[indice] = soma & 0xff;
        // o proximo um é o byte mais significativo que restou da soma
        um = soma >> 8;
        indice++;

    }
}

void big_sum(BigInt res, BigInt a, BigInt b){
    unsigned qt_bytes = NUM_BITS / 8;
    unsigned um = 0;
    unsigned indice = 0;

    while(indice < qt_bytes){
        unsigned soma = a[indice] + b[indice] + um;
        res[indice] = soma & 0xff;
        um = soma >> 8;
        indice++;
    }
}

void big_sub(BigInt res, BigInt a, BigInt b){
    memset(res, 0, sizeof(BigInt));
    BigInt compa2_b;
    big_comp2(compa2_b, b);
    big_sum(res, a, compa2_b);
}

void big_mul(BigInt res, BigInt a, BigInt b){
    BigInt temp;
    memset(res, 0, sizeof(BigInt));
    unsigned num_bytes = NUM_BITS / 8;

    // Para cada bit do multiplicador b
    for (unsigned pos_bit = 0; pos_bit < NUM_BITS; pos_bit++) {
        unsigned indice_byte_b = pos_bit / 8;
        unsigned indice_bit_b = pos_bit % 8;
        unsigned mascara_bit_b = 1 << indice_bit_b;

        // Se o bit correspondente de b está ligado
        if (b[indice_byte_b] & mascara_bit_b) {
            memset(temp, 0, sizeof(BigInt));
            unsigned desloca_byte = pos_bit / 8;
            unsigned desloca_bit = pos_bit % 8;

            // Para cada byte do multiplicando a
            for (unsigned indice_byte_a = 0; indice_byte_a < num_bytes; indice_byte_a++) {
                unsigned valor_a = a[indice_byte_a];
                if (valor_a == 0) continue;

                // Desloca o byte de a para a esquerda
                unsigned deslocado = valor_a << desloca_bit;
                unsigned sobra = 0;
                // Se houver deslocamento de bits, pega o "resto" do próximo byte
                if (desloca_bit && indice_byte_a < num_bytes - 1)
                    sobra = a[indice_byte_a + 1] >> (8 - desloca_bit);

                unsigned indice_temp = indice_byte_a + desloca_byte;
                if (indice_temp < num_bytes)
                    temp[indice_temp] |= deslocado & 0xFF;
                if (desloca_bit && indice_temp + 1 < num_bytes)
                    temp[indice_temp + 1] |= sobra & 0xFF;
            }
            // Soma o valor temporário ao resultado acumulado
            big_sum(res, res, temp);
        }
    }
}

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n){
    memset(res, 0, sizeof(BigInt));
    unsigned num_bytes = NUM_BITS / 8;

    if (n >= NUM_BITS) return; // se n é maior ou igual ao número de bits, o resultado é zero

    unsigned desloca_bytes = n / 8;
    unsigned desloca_bits = n % 8;

    for (unsigned i = 0; i < num_bytes; i++) {
        if (i + desloca_bytes < num_bytes) {
            res[i + desloca_bytes] |= (a[i] << desloca_bits) & 0xFF;
        }
        if (desloca_bits != 0 && i + desloca_bytes + 1 < num_bytes) {
            res[i + desloca_bytes + 1] |= (a[i] >> (8 - desloca_bits)) & 0xFF;
        }
    }

}

/* res = a >> n (lógico)*/
void big_shr(BigInt res, BigInt a, int n){
    memset(res, 0, sizeof(BigInt));
    unsigned num_bytes = NUM_BITS / 8;

    if (n >= NUM_BITS) return; // se n é maior ou igual ao número de bits, o resultado é zero

    unsigned desloca_bytes = n / 8;
    unsigned desloca_bits = n % 8;

    for (unsigned i = 0; i < num_bytes; i++) {
        if (i >= desloca_bytes) {
            res[i - desloca_bytes] |= (a[i] >> desloca_bits) & 0xFF;
        }
        if (desloca_bits != 0 && i >= desloca_bytes + 1) {
            res[i - desloca_bytes - 1] |= (a[i] << (8 - desloca_bits)) & 0xFF;
        }
    }
}

/* res = a >> n (aritmético)*/
void big_sar(BigInt res, BigInt a, int n){
    memset(res, 0, sizeof(BigInt));
    unsigned num_bytes = NUM_BITS / 8;

    if (n >= NUM_BITS) {
        // Se n é maior ou igual ao número de bits, o resultado depende do bit de sinal
        if (a[num_bytes - 1] & 0x80) { // se o bit de sinal é 1 (número negativo)
            memset(res, 0xFF, sizeof(BigInt)); // preenche com 1s
        }
        return;
    }

    unsigned desloca_bytes = n / 8;
    unsigned desloca_bits = n % 8;

    for (unsigned i = 0; i < num_bytes; i++) {
        if (i >= desloca_bytes) {
            res[i - desloca_bytes] |= (a[i] >> desloca_bits) & 0xFF;
        }
        if (desloca_bits != 0 && i >= desloca_bytes + 1) {
            res[i - desloca_bytes - 1] |= (a[i] << (8 - desloca_bits)) & 0xFF;
        }
    }

    // Se o número é negativo, preenche os bits mais significativos com 1s
    if (a[num_bytes - 1] & 0x80) {
        for (unsigned i = num_bytes - 1; i >= num_bytes - desloca_bytes; i--) {
            res[i] = 0xFF;
        }
        if (desloca_bits != 0 && num_bytes > desloca_bytes) {
            res[num_bytes - desloca_bytes - 1] |= ((1 << desloca_bits) - 1) << (8 - desloca_bits);
        }
    }
}