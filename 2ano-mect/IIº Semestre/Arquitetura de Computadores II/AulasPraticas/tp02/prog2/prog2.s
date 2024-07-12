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
main:   addi    $sp, $sp, -4                        # void main(void){ 
        sw      $ra, 0($sp)                         # guardar endereço de retorno
        li      $t0,0                               # counter = 0;                            
loop:  li      $a0, 1000                           # while (1) {     
        jal     delay                               # delay(1000);    

        addi    $t0, $t0, 1                         # counter++;
        move    $a0, $t0
        li      $a1, 10
        syscall                                     # printInt(++counter, 10 | 4 << 16); 

        ori     $a0, $0, '\r'
        li      $v0, PUT_CHAR
        syscall                                     # putChar('\r');

        j       loop

       
        lw      $ra, 0($sp)                         # 
        addi    $sp, $sp, 4                         # 

        li      $v0, 0                              # return 0

        jr      $ra                                 # end main }

delay:                                              # void delay(int ms){
while:  ble     $a0, $0, endw                       # while(ms > 0){

        li      $v0, RESET_CORE_TIMER
        syscall                                     #  resetCoreTimer();

wait:   li      $v0, READ_CORE_TIMER
        syscall
        blt     $v0, TARGET_CORE_VAL, wait          # readCoreTimer() < K; onde k = 20000

        addi    $a0, $a0, -1                        # ms--;

        j       while                               # }

endw:   jr    $ra                                   #  



