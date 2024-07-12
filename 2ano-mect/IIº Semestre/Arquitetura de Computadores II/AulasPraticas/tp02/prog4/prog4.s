
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
        li      $t0,0                               # cnt1 = 0;
        li      $t1,0                               # cnt5 = 0;
        li      $t2,0                               # cnt10 = 0; 
loop:  li      $a0, 1000                           # while (1) {     
        jal     delay                               # delay(1000);    

        ori     $a0, $0, '\r'
        li      $v0, PUT_CHAR
        syscall                                     # putChar('\r');

        move    $a0, $t0
        li      $a1, 0x00050002
        syscall                                     # printInt(cnt1, 10 | 4 << 16); 
        ori     $a0, $0, ' '                        # putChar(' ');

        move    $a0, $t1
        li      $a1, 0x00050002
        syscall                                     # printInt(cnt5, 10 | 4 << 16); 
        ori     $a0, $0, ' '                        # putChar(' ');

        move    $a0, $t2
        li      $a1, 0x00050002
        syscall                                     # printInt(cnt10, 10 | 4 << 16); 
        ori     $a0, $0, ' '                        # putChar(' ');

        addi    $t2, $t2, 1                         # cnt10++;

        rem     $t3,$t2,2                           # cnt10 % 2 
        rem     $t4, $t2,10                         # cnt10 % 10

if:     bne     $t3,$0,endif                        # if (cnt10 % 2 == 0){
        addi    $t1,$t1,1                           # cnt5++;
if2:    bne     $t4, $0, endif                      # if (cnt10 % 10 == 0){
        addi    $t0,$t0,1                           # ctn1++;

        j       loop
endif:     
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
