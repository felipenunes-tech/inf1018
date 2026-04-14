.data
nums:  .int  10, -21, -30, 45    # Array original de inteiros (4 bytes)
Sf:  .string "%d\n"              # String de formato para printf

.text
.globl  main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)
  movq    %r12, -16(%rbp)
/********************************************************/

  movl  $0, %ebx       /* ebx = 0 (nosso 'i') */
  movq  $nums, %r12    /* r12 = &nums (nosso 'p') */

L1:
  cmpl  $4, %ebx       /* if (ebx == 4) ? */
  je  L2               /* se sim, sai do loop (goto L2) */

  movl  (%r12), %eax   /* eax = *p (carrega o número atual) */

  # --- INÍCIO DO TESTE DE NÚMERO PAR ---
  # testl faz um AND bit a bit entre 1 e o valor em %eax,
  # mas NÃO altera o %eax! Ele apenas atualiza as flags do processador.
  testl $1, %eax       
  
  # jnz significa "Jump if Not Zero" (Pule se NÃO for zero).
  # Se o resultado do AND foi 1, o número é ÍMPAR, então pulamos o printf.
  jnz proximo          
  # --- FIM DO TESTE ---

/*************************************************************/
/* este trecho imprime o valor de %eax (estraga %eax)        */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro para string)*/
  movl    %eax, %esi   /* segundo parametro  (inteiro a imprimir) */
  call  printf         /* chama a funcao da biblioteca */
/*************************************************************/

proximo:
  addl  $1, %ebx       /* ebx += 1; (i++) */
  addq  $4, %r12       /* r12 += 4; (p++ para avançar 4 bytes no int) */
  jmp  L1              /* volta para L1; */

L2:  
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret      
/***************************************************************/