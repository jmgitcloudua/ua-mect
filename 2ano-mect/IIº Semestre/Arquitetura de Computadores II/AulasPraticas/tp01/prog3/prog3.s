# int main(void) 
 # { 
 # char c; 
 # do 
 # { 
 # c = getChar(); 
 # if( c != '\n' ) 
 # putChar( c+1 ); 
 # } while( c != '\n' ); 
 # return 0; 
 # }
      .data
      .equ getChar, 2
      .equ putChar, 3
      .text
      .globl main
# Mapta de registos
# c:t0
main:                         # int main(void){
do:                           # {
      li $v0, getChar
      syscall
      move $t0, $v0            # c = getChar();
if:   beq  $t0, '\n', endf     # if(c != '\n')
      addi $a0, $t0, 1         # $a0 = c+1 
      li   $v0, putChar 
      syscall                  # putChar( c+1 );
enddo: bne $t0, '\n', do       # } while( c != '\n' );
endf: li $v0,0                # return 0;   
      jr    $ra                # fim