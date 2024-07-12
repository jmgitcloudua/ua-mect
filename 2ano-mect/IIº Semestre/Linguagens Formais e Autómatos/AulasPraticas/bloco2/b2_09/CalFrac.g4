// -----------------------------------
// Bloco 2, Ex. 2.09
// Formal and Automated Languages
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// -----------------------------------

grammar CalFrac;

//---Parser Rules------//
program: (stat SEMICOLON)* EOF;

stat   : print		
	   | assign	
       ;

assign : expr ARROW ID	
	   ;
	   
print  : PRINT expr 
	   ;
	   
expr   : expr op=(DIVIDE | MULTIPLY) expr	#ExprDivisionMultiply
	   | expr op=(ADD    | SUBTRACT) expr	#ExprAddDifference
	   | expr POWER							#ExprPower
	   | REDUCE expr						#ExprReduce
	   | LPARENTESIS expr RPARENTESIS	    #ExprParentesis
	   | FRAC								#ExprFrac   
	   | ID							        #ExprVariable
	   ;




//----Lexer Rules----//

// Reserved Words
PRINT		: 'print';
REDUCE		: 'reduce';
POWER		: '^' INT;		// solves priority issues
FRAC		: INT ('/' INT)?;

// Numbers and IDs
INT 		: ('-'|'+')? [0-9]+;
ID			: [a-z]+;

// Operations
DIVIDE		: ':';			
MULTIPLY	: '*';
ADD			: '+';
SUBTRACT	: '-';

// Other Stuff
ARROW		: '->';	
SEMICOLON	: ';';
LPARENTESIS	: '(';
RPARENTESIS	: ')';

// Comments & Space
COMMENTS	: '//' .*? '\n' -> skip;
WS			: [ \t\r\n]+ 	-> skip;
ERROR		: .;