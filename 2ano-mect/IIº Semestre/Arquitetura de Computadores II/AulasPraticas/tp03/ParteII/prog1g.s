 # -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
# -----------------------------------
    .equ    READ_CORE_TIMER,11   
    .equ    RESET_CORE_TIMER,12  
    .equ    FREQUENCY_Hz, 1.5          # updated to 1.5Hz         
    .equ    TARGET_CORE_VAL, 20000000/FREQUENCY_Hz
    .equ    ms, 1000                 # trying with 1000ms
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

#-----Impleting 4bits Binary up Counting with 1Hz of frequency
# Registers Map
# $s0, $s1, $s2 -> used to access TRIS/LAT/PORT registers
# $s3 -> counter
# $t0 -> value from RB2
# $t1 -> LSBit after shift left/right / value to write to LATE registers
main:                               # int main(void){
    addi $sp, $sp, -20	            # reserve space into stack
    sw $ra, 0($sp)                  #  Save $ra, $s registers
    sw $s0, 4($sp)                  #
    sw $s1, 8($sp)                  #
    sw $s2, 12($sp)                 #
    sw $s3, 16($sp)                 #

    lui $s0, SFR_BASE_HI            #
    
    #---Configuring RB ports as inputs (read-modify-write)
    lw  $s1, TRISB($t0)             # $s1 = TRISB+$t0
    andi $s1, $t1, FFF0             # $s1 = $t1 & 0xFFF0
    ori $s1, $t1, 0x000F            # Modify ,$s1 = $s1 | 0x0001 (bit0-3=1, input) 0000.0000.0000.1111
    sw  $s1, TRISB($t0)             # Write(Write TRISB register)

    #---Configuring RE ports as outputs (read-modify-write)
    lw  $s2, TRISE($t0)             #Read, $s2 = TRISE+$t0
    andi $s2, $s2, 0xFFF0           # Modify, $s2 = $s2 & 0xFFFE  (bit0-3=0, output) 1111.1111.1111.0000  
    sw  $s2, TRISE($t0)             # Write(Write TRISE register)

    li  $s3, 0x0001                 # counter = 0;

#--- 4 Bits Johnson Counter Left/Right Shift
while:                              # while(1){
    li  $a0, ms                     # 1000ms
    jal delay                       # call sub-rotine

    #---Read from RB1 port
    lw  $t0, PORTB($s0)              # Read, $t0 = PORTB+$s0
    andi $t0, $t0, 0x0001

    not $t1, $t1, $s3
    andi $t1, $t1, 0x0008           # keepts not(bit 3)

if:       beq $t0, 0, else           #   RB1 = 1 -> LEFT

resetIfL: bne $s3, 0x0008, elseL     #     counter = 1000. next time, counter must be = 0001
          li  $s3, 0x0001
          j endIfL

elseL:    sll  $s3, $s3, 1

endIfL:   li $a0,'<'                 #     Debug
          li $v0, 3
          syscall

          j endIf
                                 
else:	                             #   RB1 = 0 -> RIGHT
resetIfR: bne $s3, 0x0001, elseR     # counter = 1000. next time, counter must be = 0001
          li  $s3, 0x0008
          j endIfR

elseR:    srl  $s3, $s3, 1

endIfR:   li $a0,'>'                 #Debug
          li $v0, 3
          syscall

endIf:    li $a0,' '                 #Debug
          li $v0, 3
          syscall

    lw  $t0, LATE($s0)              # Read, $t1 = LATE+$s0
    andi  $t1, $t0, 0xFFF0          # $t1 = $t1 & 0xFFF0
    or    $t1, $t0, $s3             # $t1 = $t1 | counter
    sw    $t1, LATE($s0)            # Write(Write LATE register)
    
    j   while                       # }
     
    lw $ra, 0($sp)                  #  carry back $ra, $s registers
    lw $s0, 4($sp)                  #
    lw $s1, 8($sp)                  #
    lw $s2, 12($sp)                 #
    lw $s3, 16($sp)                 #
    addi $sp, $sp, 20	            # restore space into stack

    li  $v0,1
    jr  $ra                         # end main}

delay:                                              # void delay(int ms){
while2:  ble     $a0, $0, endw                       # while(ms > 0){

        li      $v0, RESET_CORE_TIMER
        syscall                                     #  resetCoreTimer();

wait:   li      $v0, READ_CORE_TIMER
        syscall
        blt     $v0, TARGET_CORE_VAL, wait          # readCoreTimer() < K; onde k = 20000

        addi    $a0, $a0, -1                        # ms--;

        j       while2                               # }

endw:   jr    $ra 