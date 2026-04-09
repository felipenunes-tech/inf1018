/*
int main() {
  int i;
  int *p = nums;
  for (i = 0; i < 5; i++) {
    printf("%d\n", filtro(*p,LIM));
    p++;
  }
  return 0;
}
*/

.data
 nums: .int 3, -5, 7, 8, -2
 s1:   .string "%d\n"

 .text
 .globl main
 main:
 /* prologo */
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp
    movq  %rbx, -8(%rbp)
    movq  %r12, -16(%rbp)

  /* coloque seu codigo aqui */
    movq $0, %rbx                # i = 0 (índice inicial)
    movq $nums, %r12d            # p = nums

Loop:
    cmpl $5, %rbx # i=5?
    je Finalizacao
    movl(%r12), %edi





  /* finalizacao */
Finalizacao:
    movq -8(%rbp), %rbx
    movq -16(%rbp), %r12
    leave
    ret