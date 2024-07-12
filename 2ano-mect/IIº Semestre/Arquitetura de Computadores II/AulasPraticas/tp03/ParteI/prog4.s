 # -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
# -----------------------------------
    .equ    READ_CORE_TIMER,11   
    .equ    RESET_CORE_TIMER,12  
    .equ    FREQUENCY_Hz, 5         # change to 1Hz
    .equ    TARGET_CORE_VAL, 20000000/FREQUENCY_Hz
    .equ    SFR_BASE_HI, 0xBF88      # 16 MSbits of SFR area (SFR - Special Function Registers)
    .equ    TRISE,  0x6100           # TRISE address is 0xBF886100
    .equ    PORTE,  0x6110           # PORTE address is 0xBF886110 
    .equ    LATE, 0x6120             # LATE  address is 0xBF886120
    
    #-------------------------------------------------------------
    .equ TRISB, 0x6040 	             # TRISB address is 0xBF886040
    .equ PORTB, 0x6050	             # PORTB address is 0xBF886050
    .equ LATB, 0x6060 	             # LATB  address is 0xBF886060 
    .data
    .text
    .globl  main
# Map of Registers
# $s0 -> v

# Remark: THE FOLLOWING REGISTERS MUST BE SAVED
# $s1 -> SFR_BASE_HI
# $s2 -> TRISE
# $s3 -> LATE
main:                               # int main(void){
    addi $sp, $sp, -20	            # reserve space into stack
    sw $ra, 0($sp)                  #  Save $ra, $s registers
    sw $s0, 4($sp)                  #
    sw $s1, 8($sp)                  #
    sw $s2, 12($sp)                 #
    sw $s3, 16($sp)                 #

    li $s0, 0                       #    int v = 0;

    #---TRISE0 = 0, Configure RE0 port as output 
    lui $s1, SFR_BASE_HI            # 
    lw  $s2, TRISE($s1)             # read, $s2 = TRISE+$s1
    andi $s2, $s2, 0xFFFE           # Modify, $s2=$s2 & 0xFFFE
    sw  $s2,TRISE($s1)              # Write (Write TRISE register)
while:                              # while(1){
    #---Write v in bit 0 of E port
    lw  $s3, LATE($s1)              # read, $s3=LATE+$s1
    andi $s3,$s3, 0xFFFE            # Modify, $s3=$s3 & 0xFFFE
    or  $s3, $s3, $s0               # Modify, $s3 = $s3 | $s0
    sw  $s3, LATE($s1)                # Write (Write LATE register)

    li  $a0, 500                    # $a = 500ms(delay of 500 miliseconds) 
    jal delay                       # change to 20ms and 10ms to see other behavior
    
    xori $s0, $s0, 1                # v^=1; // complement the bit 0 of v (v = v xor 1)

    j   while                       # }

     
    lw $ra, 0($sp)                  #  carry back $ra, $s registers
    lw $s0, 4($sp)                  #
    lw $s1, 8($sp)                  #
    lw $s2, 12($sp)                 #
    lw $s3, 16($sp)                 #
    addi $sp, $sp, 20	            # restore space into stack

    li  $v, 1
    jr  $ra                         # end main function}



delay:                                              # void delay(int ms){
while2:  ble     $a0, $0, endw                       # while(ms > 0){

        li      $v0, RESET_CORE_TIMER
        syscall                                     #  resetCoreTimer();

wait:   li      $v0, READ_CORE_TIMER
        syscall
        blt     $v0, TARGET_CORE_VAL, wait          # readCoreTimer() < K; onde k = 20000

        addi    $a0, $a0, -1                        # ms--;

        j       while2                               # }

endw:   jr    $ra                                   #