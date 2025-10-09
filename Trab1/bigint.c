/* Felipe Eduardo Nunes da Silva : 2320615 : 33WA */

#include "bigint.h"
#include <stdio.h>
#include <string.h>

#define NUM_BITS 128
#define NUM_BYTES (NUM_BITS / 8)
typedef unsigned char BigInt[NUM_BITS/8];

/* Atribuicao */

/* res = val (extensao com sinal) */
void big_val (BigInt res, long val) {
    // Realiza a extensao de sinal preenchendo todo o BigInt com o bit mais significativo de 'val'.
    unsigned char preenchimento = (val < 0) ? 0xFF : 0x00;
    memset(res, preenchimento, NUM_BYTES);

    // Copia os bytes de 'val' para a parte menos significativa do BigInt.
    unsigned char* bytes_do_valor = (unsigned char*)&val;
    for (unsigned i = 0; i < sizeof(long); i++) {
        res[i] = bytes_do_valor[i];
    }
}

/* Operacoes aritmeticas */

/* res = -a */
void big_comp2(BigInt res, BigInt a) {
    // Implementa o complemento de dois com a logica (~a + 1) em duas passadas.
    for (unsigned i = 0; i < NUM_BYTES; i++) {
        res[i] = ~a[i];
    }

    unsigned int vai_um = 1;
    for (unsigned i = 0; i < NUM_BYTES && vai_um > 0; i++) {
        unsigned int soma_parcial = res[i] + vai_um;
        res[i] = (unsigned char)soma_parcial;
        vai_um = soma_parcial >> 8;
    }
}

/* res = a + b */
void big_sum (BigInt res, BigInt a, BigInt b) {
    unsigned int transporte = 0;
    unsigned int i = 0;

    while (i < NUM_BYTES) {
        unsigned int soma_bytes = (unsigned int)a[i] + b[i] + transporte;
        res[i] = soma_bytes & 0xFF;
        transporte = soma_bytes >> 8;
        i++;
    }
}

/* res = a - b */
void big_sub (BigInt res, BigInt a, BigInt b) {
    // Subtracao implementada como a soma do complemento de dois: a + (-b).
    BigInt b_negativo;
    big_comp2(b_negativo, b);
    big_sum(res, a, b_negativo);
}

/* res = a * b */
void big_mul (BigInt res, BigInt a, BigInt b) {
    // Algoritmo de multiplicacao longa (base 256).
    memset(res, 0, NUM_BYTES);
    
    for (unsigned idx_b = 0; idx_b < NUM_BYTES; idx_b++) {
        unsigned int excedente = 0;
        for (unsigned idx_a = 0; idx_a < NUM_BYTES; idx_a++) {
            unsigned int pos_res = idx_a + idx_b;
            
            if (pos_res < NUM_BYTES) {
                unsigned int produto_parcial = (unsigned int)b[idx_b] * a[idx_a] + res[pos_res] + excedente;
                res[pos_res] = (unsigned char)produto_parcial;
                excedente = produto_parcial >> 8;
            }
        }
    }
}

/* Operacoes de deslocamento */

/* res = a << n */
void big_shl (BigInt res, BigInt a, int n) {
    if (n >= NUM_BITS) {
        memset(res, 0, NUM_BYTES);
        return;
    }

    const unsigned desloc_bytes = n / 8;
    const unsigned desloc_bits = n % 8;

    // Loop invertido para evitar sobrescrever bytes de 'a' que ainda serao lidos.
    for (int i = NUM_BYTES - 1; i >= 0; --i) {
        unsigned char parte_principal = 0;
        if (i >= desloc_bytes) {
            parte_principal = a[i - desloc_bytes] << desloc_bits;
        }

        unsigned char parte_transportada = 0;
        if (desloc_bits > 0 && i > desloc_bytes) {
            parte_transportada = a[i - desloc_bytes - 1] >> (8 - desloc_bits);
        }
        
        res[i] = parte_principal | parte_transportada;
    }
}

/* res = a >> n (logico) */
void big_shr (BigInt res, BigInt a, int n) {
    if (n >= NUM_BITS) {
        memset(res, 0, NUM_BYTES);
        return;
    }
    
    const unsigned desloc_bytes = n / 8;
    const unsigned desloc_bits = n % 8;

    for (unsigned i = 0; i < NUM_BYTES; i++) {
        unsigned char v1 = 0, v2 = 0;

        if (i + desloc_bytes < NUM_BYTES) {
            v1 = a[i + desloc_bytes] >> desloc_bits;
        }

        if (desloc_bits > 0 && i + desloc_bytes + 1 < NUM_BYTES) {
            v2 = a[i + desloc_bytes + 1] << (8 - desloc_bits);
        }

        res[i] = v1 | v2;
    }
}

/* res = a >> n (aritmetico) */
void big_sar(BigInt res, BigInt a, int n) {
    const unsigned char bit_de_sinal = a[NUM_BYTES - 1] & 0x80;
    
    if (n >= NUM_BITS) {
        memset(res, bit_de_sinal ? 0xFF : 0, NUM_BYTES);
        return;
    }

    // 1. Realiza um deslocamento logico (preenchendo com zeros).
    const unsigned desloc_bytes = n / 8;
    const unsigned desloc_bits = n % 8;
    for (int i = 0; i < NUM_BYTES; i++) {
        unsigned char parte_principal = (i + desloc_bytes < NUM_BYTES) ? (a[i + desloc_bytes] >> desloc_bits) : 0;
        unsigned char parte_transportada = (desloc_bits > 0 && i + desloc_bytes + 1 < NUM_BYTES) ? (a[i + desloc_bytes + 1] << (8 - desloc_bits)) : 0;
        res[i] = parte_principal | parte_transportada;
    }
    
    // 2. Se o numero era negativo, propaga o bit de sinal.
    if (bit_de_sinal) {
        unsigned char mascara = (unsigned char)0xFF << (8 - desloc_bits);
        if (desloc_bits > 0 && NUM_BYTES > desloc_bytes) {
            res[NUM_BYTES - desloc_bytes - 1] |= mascara;
        }
        for (unsigned i = NUM_BYTES - desloc_bytes; i < NUM_BYTES; i++) {
            res[i] = 0xFF;
        }
    }
}