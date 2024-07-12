    .equ    READ_CORE_TIMER,11   
    .equ    RESET_CORE_TIMER,12  
    .equ    PUT_CHAR,3   
    .equ    PRINT_INT,6   
    .equ    FREQUENCY_Hz, 5
    .equ    TARGET_CORE_VAL, 20000000/FREQUENCY_Hz
    .data   
    .text   
    .globl  main 

# Mapa da registos
# counter: $t0
main:                                               # void main(void){ 
        li      $t0,0                               # counter = 0;                            
while:                                               #     

        blt     $v0, TARGET_CORE_VAL, while         # while(readCoreTimer() < 200000)

        li      $v0, RESET_CORE_TIMER               # resetCoreTimer();
        syscall

        addi    $t0, $t0, 1                         # counter++;
        move    $a0, $t0
        li      $a1, 0x0004000A
        syscall                                     # printInt(++counter, 10 | 4 << 16); 

        ori     $a0, $0, '\r'
        li      $v0, PUT_CHAR
        syscall                                     # putChar('\r');

        j       while

        li      $v0, 0                              # return 0

        jr      $ra                                 # end main }