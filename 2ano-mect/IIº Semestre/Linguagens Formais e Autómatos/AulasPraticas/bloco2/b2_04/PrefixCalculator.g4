// -----------------------------------
// Bloco 2, Ex. 2.04
// Formal and Automated Languages
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// -----------------------------------
grammar PrefixCalculator;

//Parser Rules
program: stat* EOF;        					// Zero or more repetitions of stat
stat: expr? NEWLINE;     						// Optativeexpr
expr:
		 op=('*' | '/' | '+' | '-') expr expr	 #ExprPrefix
	| 	Number					 	             #ExprNumber
	;
//Lexer Rules
Number: [0-9]+('.' [ 0-9]+)?;
NEWLINE: '\r' ?  '\n';
WS: [\t]+ -> skip;  
