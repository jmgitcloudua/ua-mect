# -----------------------------------
# 2º Ano-2ºSemestre | Abril 2021
# Arquitectura de Computadores II
# Jodionisio Muachifi, 97147, MIECT
# -----------------------------------
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
main:                               # int main(void){
    lui $t0, SFR_BASE_HI            #
    
    #---Configuring RB0 ports as inputs (read-modify-write)
    lw  $t1, TRISB($t0)             # $t1 = TRISB+$t0
    #andi $t1, $t1, FFF0             # $t1 <- $t1 & 0xFFF0
    ori $t1, $t1, 0x000F            # Modify ,$t1 = $t1 | 0x0001 (bit0-3=1, input) 0000.0000.0000.1111
    sw  $t1, TRISB($t0)             # Write(Write TRISB register)

    #---Configuring RE0 ports as outputs (read-modify-write)
    lw  $t2, TRISE($t0)             # $t2 = TRISE+$t0
    andi $t2, $t2, 0xFFF0           # Modify, $t2 = $t2 & 0xFFFE  (bit0-3=0, output) 1111.1111.1111.0000  
    sw  $t2, TRISE($t0)             # Write(Write TRISE register)

    #----Writing a infinity loop
while:                              # while(1){
    #---Reading from RB0 Ports
    lw  $t3, PORTB($t0)             # $t3 = PORTB+$t0
    andi $t3, $t3, 0x000F           # $t3 = $t3 & 0x000F (modify) 

    #---Writing RB0 to RE Ports
    lw  $t4, LATE($t0)              # $t4 = LATE+$t0(read)
    andi $t4, $t4, 0xFFF0           # Modify, $t4 = $t4 & 0xFFF0  (bit0-3=0, output) 1111.1111.1111.0000  
    or  $t4, $t4, $t3               # Modify, $t4 = $t4 | $t3
    sw  $t4, LATE($t0)              # Write(Write LATE register) 

    j   while                       # }

    li  $v0, 1
    jr  $ra                         # end main function
