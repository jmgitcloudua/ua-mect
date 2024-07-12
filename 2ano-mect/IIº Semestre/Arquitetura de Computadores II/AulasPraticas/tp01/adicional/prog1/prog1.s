    .data
    .equ    putChar,3
    .equ    printInt,6
    .equ    inkey,1
    .text
    .globl main
#Mapa de registos
# s: $t0
# c: $t1
# cnt: $t2
main:                               # int main(void){
        li	$t0, 0                  # s=0;
        li  $t2, 0                  # cnt=0;
do:                                 # do{   
        ori $a0,0,'\r'
        li  $v0, putChar
        syscall                     # putChar('\r');     // Carriage return character   
        #---------falta completar
        li  $a0,5                   # $a0 = 5;
        jal wait                    # call wait function
        move    $a0,$v0	
        li  $v0, inkey              
        syscall
        move    $t1, $v0            #  c = inkey();
if:     bne $t1, '+', endif    
        ori    $t0,$0,0             # s=0;
        bne $t1, '-', endif 
        ori $t0, $0, 1              # s=1;
if2:    bne $t0, 0, else
        addi $t3, $t2,1             # $t3 =  (cnt + 1) ;
        and  $t2, $t3, 0xFF         # cnt = (cnt + 1) & 0xFF;
else:  addi $t3, $t2, -1             # $t3 =  (cnt - 1) ;
       and  $t2, $t3, 0xFF         # cnt = (cnt - 1) & 0xFF; 
enddo:  bne $t1, 'q',do             #  } while( c != 'q' );
endif:  li  $v0, 0                  # return 0
        jr  $ra                     # end main }

# Wait Function
wait:                               #   void wait(int ts){
        li  $t0, 0                  # i = 0;
        mul $t2, $a0, 515000        # 515000 * ts
while:  bge $t0,$t2,endw            # while(i < 515000 * ts){
        addi $t0, $t0, 1            # i++;
        j   while
endw: 
        jr  $ra                     # end wait }


