# int main(void) 
 # { 
 # char c; 
 # do 
 # { 
 # c = getChar(); 
 # if( c != '\n' ) 
 # putChar( c ); 
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
if:   beq  $t0, '\n', endif     # if(c != '\n')
      move $a0, $t0            # 
      li   $v0, putChar 
      syscall                  # putChar( c );
enddo: bne $t0, '\n', do       # } while( c != '\n' );
endif: li $v0,0                # return 0;   
      jr    $ra                # fim