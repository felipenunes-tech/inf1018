/*Felipe Eduardo Nunes da Silva - 2320615 -Turma A
Pedro Augusto Beserra da Silva - 2321374 - Turma B */

#include "bigint.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Função auxiliar para criar BigInts de referência, agora em português.
void cria_esperado(BigInt esperado, long valor) {
    if (valor < 0) {
        memset(esperado, 0xFF, sizeof(BigInt));
    } else {
        memset(esperado, 0, sizeof(BigInt));
    }
    memcpy(esperado, &valor, sizeof(long));
}

// --- Teste 1: big_val ---
void testa_big_val(void) {
    BigInt resultado;
    BigInt esperado;

    big_val(resultado, 500);
    cria_esperado(esperado, 500);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(resultado, -500);
    cria_esperado(esperado, -500);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(resultado, 0);
    cria_esperado(esperado, 0);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

// --- Teste 2: big_comp2 ---
void testa_big_comp2(void) {
    BigInt valor, resultado, esperado;

    big_val(valor, -99);
    big_comp2(resultado, valor);
    cria_esperado(esperado, 99);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(valor, 99);
    big_comp2(resultado, valor);
    cria_esperado(esperado, -99);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(valor, 0);
    big_comp2(resultado, valor);
    cria_esperado(esperado, 0);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

// --- Teste 3: big_sum ---
void testa_big_sum(void) {
    BigInt a, b, resultado, esperado;

    big_val(a, 1000);
    big_val(b, 2345);
    big_sum(resultado, a, b);
    cria_esperado(esperado, 3345);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(a, -100);
    big_val(b, -200);
    big_sum(resultado, a, b);
    cria_esperado(esperado, -300);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(a, 100);
    big_val(b, -30);
    big_sum(resultado, a, b);
    cria_esperado(esperado, 70);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

// --- Teste 4: big_sub ---
void testa_big_sub(void) {
    BigInt a, b, resultado, esperado;

    big_val(a, 200);
    big_val(b, 50);
    big_sub(resultado, a, b);
    cria_esperado(esperado, 150);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(a, 50);
    big_val(b, 200);
    big_sub(resultado, a, b);
    cria_esperado(esperado, -150);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(a, 100);
    big_val(b, -100);
    big_sub(resultado, a, b);
    cria_esperado(esperado, 200);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

// --- Teste 5: big_mul ---
void testa_big_mul(void) {
    BigInt a, b, resultado, esperado;

    big_val(a, 100);
    big_val(b, 100);
    big_mul(resultado, a, b);
    cria_esperado(esperado, 10000);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(a, -25);
    big_val(b, -10);
    big_mul(resultado, a, b);
    cria_esperado(esperado, 250);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(a, -12345);
    big_val(b, 0);
    big_mul(resultado, a, b);
    cria_esperado(esperado, 0);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

// --- Teste 6: big_shl ---
void testa_big_shl(void) {
    BigInt valor, resultado, esperado;

    big_val(valor, 10);
    big_shl(resultado, valor, 3);
    cria_esperado(esperado, 80);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(valor, 200);
    big_shl(resultado, valor, 8);
    cria_esperado(esperado, 51200);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(valor, -1);
    big_shl(resultado, valor, 1);
    cria_esperado(esperado, -2);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

// --- Teste 7: big_shr ---
void testa_big_shr(void) {
    BigInt valor, resultado, esperado;

    big_val(valor, 80);
    big_shr(resultado, valor, 3);
    cria_esperado(esperado, 10);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(valor, 51200);
    big_shr(resultado, valor, 8);
    cria_esperado(esperado, 200);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(valor, -2); // ...11111110
    big_shr(resultado, valor, 1); // Deslocamento lógico -> 0...1111111
    memset(esperado, 0xFF, sizeof(BigInt));
    esperado[sizeof(BigInt) - 1] = 0x7F; // Zera o bit de sinal
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}

// --- Teste 8: big_sar ---
void testa_big_sar(void) {
    BigInt valor, resultado, esperado;

    big_val(valor, 100);
    big_sar(resultado, valor, 2);
    cria_esperado(esperado, 25);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(valor, -100);
    big_sar(resultado, valor, 2);
    cria_esperado(esperado, -25);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);

    big_val(valor, -1);
    big_sar(resultado, valor, 100);
    cria_esperado(esperado, -1);
    CU_ASSERT_EQUAL(memcmp(resultado, esperado, sizeof(BigInt)), 0);
}


int main (void) {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

    CU_pSuite suite = CU_add_suite("BigInt_Suite_Completa", 0, 0);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    // Adiciona todos os 8 testes à suíte.
    if ((CU_add_test(suite, "Testes de big_val", testa_big_val) == NULL) ||
        (CU_add_test(suite, "Testes de big_comp2", testa_big_comp2) == NULL) ||
        (CU_add_test(suite, "Testes de big_sum", testa_big_sum) == NULL) ||
        (CU_add_test(suite, "Testes de big_sub", testa_big_sub) == NULL) ||
        (CU_add_test(suite, "Testes de big_mul", testa_big_mul) == NULL) ||
        (CU_add_test(suite, "Testes de big_shl", testa_big_shl) == NULL) ||
        (CU_add_test(suite, "Testes de big_shr", testa_big_shr) == NULL) ||
        (CU_add_test(suite, "Testes de big_sar", testa_big_sar) == NULL))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_number_of_failures();
}