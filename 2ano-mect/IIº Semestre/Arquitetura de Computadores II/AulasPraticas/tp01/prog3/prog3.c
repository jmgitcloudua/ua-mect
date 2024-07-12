#include <detpic32.c>

int main(void) 
 { 
 char c; 
 do 
 { 
 c = getChar(); 
 if( c != '\n' ) 
 putChar( c + 1 ); 
 } while( c != '\n' ); 
 return 0;