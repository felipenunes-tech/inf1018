/*
#include <stdlib.h>
int main() {
    system("ls -ls");
    return 0;
}
*/
.data
s1: .string "ls -ls"

.text
.globl main
main:
/* prologo */
pushq %rbp
movq  %rsp, %rbp

  /* coloque seu codigo aqui */
  leaq s1(%rip), %rdi // rdi = &s1  
  movl $0, %eax // rax = 0
  call system   // chama a funcao da biblioteca

  /* finalizacao */
leave
ret