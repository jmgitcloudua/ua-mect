#include <stdio.h>
#include <string.h>

int main ( void )
{
      char name[50];
//puts ( "Hello Jodionisio Muachifi!" );
//puts ( "Hello Jodionisio Muachifi!" );
//printf( "Hello Jodionisio Muachifi!" );

//puts ( "Puts your name ?" );
printf( "Puts your name: " );

// Remove potential \n
name[strcspn(name, "\n")] = 0;

scanf("%30s", name);
//fgets(name, 50, stdin);

printf("Hello, %s!\n", name);
return 0;

}