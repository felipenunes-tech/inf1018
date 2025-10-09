/* Felipe Eduardo Nunes da Silva : 2320615 : 33WA */

#include "bigint.h"
#include <stdio.h>
#include <CUnit/Basic.h> // para rodar copie e cole no terminal -> sudo apt-get update && sudo apt-get install libcunit1-dev
#include <CUnit/CUnit.h>

#define NUM_BITS 128
typedef unsigned char BigInt[NUM_BITS/8];

void testa_big_val (void) {
    BigInt resultado;
    BigInt esperado;

    // Teste 1: Converter um número positivo que cabe em um byte
    big_val(resultado, 17);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 17;
    
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 2: Converter um número negativo que cabe em um byte
    big_val(resultado, -2);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = -2;
    
    for (int i = 1; i < sizeof(BigInt); i++) {
        esperado[i] = 255;
    }

    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 3: Converter o número zero
    big_val(resultado, 0);
    memset(esperado, 0, sizeof(BigInt));

    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

void testa_big_comp2 (void) {
    BigInt resultado;
    BigInt esperado;
    BigInt valor;

    // Teste 1: Complemento a 2 de um número positivo
    big_val(valor, 5);
    big_comp2(resultado, valor);
    memset(esperado, 0xFF, sizeof(BigInt));
    esperado[0] = 251; // -5 em complemento a 2

    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 2: Complemento a 2 de um número negativo
    big_val(valor, -3);
    big_comp2(resultado, valor);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 3; // 3 em complemento a 2

    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 3: Complemento a 2 do zero
    big_val(valor, 0);
    big_comp2(resultado, valor);
    memset(esperado, 0, sizeof(BigInt));

    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

void testa_big_sum(void){
    BigInt a, b, resultado, esperado;

    // Teste 1: 7 + 3 = 10
    big_val(a, 7L);
    big_val(b, 3L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 10;
    big_sum(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 2: (-5) + (-2) = -7
    big_val(a, -5L);
    big_val(b, -2L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = (unsigned char)(-7 & 0xFF);
    for (int i = 1; i < sizeof(BigInt); i++) esperado[i] = 0xFF;
    big_sum(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 3: (-5) + 2 = -3
    big_val(a, -5L);
    big_val(b, 2L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = (unsigned char)(-3 & 0xFF);
    for (int i = 1; i < sizeof(BigInt); i++) esperado[i] = 0xFF;
    big_sum(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 4: (-2) + 5 = 3
    big_val(a, -2L);
    big_val(b, 5L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 3;
    big_sum(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 5: (-2) + 5 = 3
    big_val(a, -2L);
    big_val(b, 5L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 3;
    big_sum(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 6: 0 + 5 = 5
    big_val(a, 0L);
    big_val(b, 5L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 5;
    big_sum(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 7: 0 + 0 = 0
    big_val(a, 0L);
    big_val(b, 0L);
    memset(esperado, 0, sizeof(BigInt));
    big_sum(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

void testa_big_sub(void){
    BigInt a, b, resultado, esperado;

    // Teste 1: 10 - 3 = 7
    big_val(a, 10L);
    big_val(b, 3L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 7;
    big_sub(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 2: (-5) - (-2) = -3
    big_val(a, -5L);
    big_val(b, -2L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = (unsigned char)(-3 & 0xFF);
    for (int i = 1; i < sizeof(BigInt); i++) esperado[i] = 0xFF;
    big_sub(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 3: (-5) - 2 = -7
    big_val(a, -5L);
    big_val(b, 2L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = (unsigned char)(-7 & 0xFF);
    for (int i = 1; i < sizeof(BigInt); i++) esperado[i] = 0xFF;
    big_sub(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 4: (5) - 2 = 3
    big_val(a, 5L);
    big_val(b, 2L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 3;
    big_sub(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 5: 7 - 0 = 7
    big_val(a, 7L);
    big_val(b, 0L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 7;
    big_sub(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 6: 0 - 0 = 0
    big_val(a, 0L);
    big_val(b, 0L);
    memset(esperado, 0, sizeof(BigInt));
    big_sub(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

void testa_big_mul(void){
    BigInt a, b, resultado, esperado;

    // Teste 1: 2 * 3 = 6
    big_val(a, 2L);
    big_val(b, 3L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 6;
    big_mul(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 2: 0 * 123 = 0
    big_val(a, 0L);
    big_val(b, 123L);
    memset(esperado, 0, sizeof(BigInt));
    big_mul(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 3: (-2) * 3 = -6
    big_val(a, -2L);
    big_val(b, 3L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = (unsigned char)(-6 & 0xFF);
    for (int i = 1; i < sizeof(BigInt); i++) {
        esperado[i] = 0xFF;
    }
    big_mul(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 4: (-2) * (-3) = 6
    big_val(a, -2L);
    big_val(b, -3L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 6;
    big_mul(resultado, a, b);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

}

void testa_big_shl(void){
    BigInt resultado;
    BigInt esperado;
    BigInt valor;

    // Teste 1: Desloca 1 (0x01) << 3 = 0x08
    big_val(valor, 1L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 8;
    big_shl(resultado, valor, 3);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 2: Desloca o zero
    big_val(valor, 0);
    memset(esperado, 0, sizeof(BigInt));
    big_shl(resultado, valor, 10);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 3: Desloca por mais de 128 bits
    big_val(valor, 4L);
    memset(esperado, 0, sizeof(BigInt));
    big_shl(resultado, valor, 130);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 4: Desloca número negativo (-2 << 1 = 0xFC...)
    big_val(valor, -2L);
    memset(esperado, 0xFF, sizeof(BigInt));
    esperado[0] = 0xFC;
    esperado[sizeof(BigInt)-1] = 0xFF;

    big_shl(resultado, valor, 1);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

void testa_big_shr (void) {
    BigInt resultado;
    BigInt esperado;
    BigInt valor;

    // Teste 1: Desloca 8 (0x08) >> 3 = 0x01
    big_val(valor, 8L);
    memset(esperado, 0, sizeof(BigInt));
    esperado[0] = 1;
    big_shr(resultado, valor, 3);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 2: Desloca o zero
    big_val(valor, 0);
    memset(esperado, 0, sizeof(BigInt));
    big_shr(resultado, valor, 0);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 3: Desloca por mais de 128 bits
    big_val(valor, 4L);
    memset(esperado, 0, sizeof(BigInt));
    big_shr(resultado, valor, 130);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 4: Desloca número negativo (-2 >> 1 = 0x7F...)
    big_val(valor, -2L);
    memset(esperado, 0, sizeof(BigInt));
    for (int i = 0; i < sizeof(BigInt)-1; i++) {
        esperado[i] = 0xFF;
    }
    esperado[sizeof(BigInt)-1] = 0x7F;

    big_shr(resultado, valor, 1);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

void testa_big_sar (void){
    BigInt resultado;
    BigInt esperado;
    BigInt valor;

    // Teste 1: Desloca -1 (todos os bits 1)
    big_val(valor, -1L);
    memset(esperado, 0xFF, sizeof(BigInt));
    big_sar(resultado, valor, 4);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 2: Desloca -2 (0xFE...)
    big_val(valor, -2L);
    memset(esperado, 0xFF, sizeof(BigInt));
    big_sar(resultado, valor, 1);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 3: Desloca o zero
    big_val(valor, 0);
    memset(esperado, 0, sizeof(BigInt));
    big_sar(resultado, valor, 10);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 4: Desloca -1 por mais de 128 bits
    big_val(valor, -1L);
    memset(esperado, 0xFF, sizeof(BigInt));
    big_sar(resultado, valor, 128);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    // Teste 5: Desloca 1 por mais de 128 bits
    big_val(valor, 1L);
    memset(esperado, 0, sizeof(BigInt));
    big_sar(resultado, valor, 128);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}


int main (void) {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    CU_pSuite suite = CU_add_suite("BigIntTestSuite", 0, 0);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if ((CU_add_test(suite, "Teste do big_val()", testa_big_val) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(suite, "Teste do big_comp2()", testa_big_comp2) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(suite, "Teste do big_sum()", testa_big_sum) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(suite, "Teste do big_sub()", testa_big_sub) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(suite, "Teste do big_mul()", testa_big_mul) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(suite, "Teste do big_shl()", testa_big_shl) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(suite, "Teste do big_shr() ", testa_big_shr) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((CU_add_test(suite, "Teste do big_sar() ", testa_big_sar) == NULL)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_number_of_failures();
}