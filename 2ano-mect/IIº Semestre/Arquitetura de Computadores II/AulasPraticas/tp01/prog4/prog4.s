 # int main(void) 
 # { 
 # char c; 
 # do 
 # { 
 # while( (c = inkey()) == 0 ); 
 # if( c != '\n' ) 
 # putChar( c ); 
 # } while( c != '\n' ); 
 # return 0; 
 # }
      .data
      .equ inkey, 1
      .equ putChar, 3
      .text
      .globl main
# Mapa de registos
# c: $t0
main:                          # int main(void){
do:                             # {
            li    $v0, inkey    # 
            syscall
            move  $t0, $v0       # (c = inkey());
               
  while:    beq   $t0, 0, do   # while( (c = inkey()) == 0 );
  endw:
  if:       beq   $t0, '\n',endif   # if( c != '\n' ){
            move  $a0, $t0
            li    $v0, putChar
            syscall                 # putChar( c );
            j     while
enddo:      bne   $t0, '\n',do      # } while( c != '\n' );
  endif:    li    $v0, 0            # return 0;
            jr    $ra               # fim             

