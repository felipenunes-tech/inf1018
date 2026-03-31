/*
int nums[] = {10, -21, -30, 45};
int main() {
  int i, *p;
  int sum = 0;
  for (i = 0, p = nums; i != 4; i++, p++)
    sum += *p;
  printf("%d\n", sum);
  return 0;
}
*/

.data /*Define variavel global*/
nums: .int 10, -21, -30, 45 /*int nums[] = {10, -21, -30, 45};*/
Sf:  .string "%d\n"

.text
.global main
main:

/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)
  movq    %r12, -16(%rbp)
/********************************************************/

movl $0, %ebx;
movq $nums, %r12;;
movl $0, %r13d;

Soma:
  cmpl  $4, %ebx # Comparação: i != 4?
  je L2 # Se i == 4, sai do loop

  addl (%r12), %r13d            # Pega o conteúdo de p e soma no sum

  incl %ebx                     # i++
  addq $4, %r12                 # p++ (anda 4 bytes porque int = 4 bytes)
  
  jmp Soma

L2:  
  movq $Sf, %rdi          # 1º argumento: formato
  movl %r13d, %esi        # 2º argumento: valor da soma
  movl $0, %eax           # Limpa eax para o printf
  call printf
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq  -8(%rbp), %rbx
  movq  -16(%rbp), %r12
  leave
  ret      
/**