    .equ    READ_CORE_TIMER,11   
    .equ    RESET_CORE_TIMER,12  
    .equ    PUT_CHAR,3   
    .equ    PRINT_INT,6   
    .data   
    .text   
    .globl  main 

# Mapa da registos
# counter: $t0
main:                                               # void main(void){ 
        li      $t0,0                               # counter = 0;                            
while:                                               # while (1) {     
                                                    #     
        blt     $v0, READ_CORE_TIMER, while         # while(readCoreTimer() < 200000) 10000000

        li      $v0, RESET_CORE_TIMER               # resetCoreTimer();
        syscall

        addi    $t0, $t0, 1                         # counter++;
        move    $a0, $t0
        li      $a1, 10
        syscall                                     # printInt(++counter, 10 | 4 << 16); 

        ori     $a0, $0, '\r'
        li      $v0, PUT_CHAR
        syscall                                     # putChar('\r');

        j       while

        li      $v0, 0                              # return 0

        jr      $ra                                 # end main }