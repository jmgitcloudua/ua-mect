// -----------------------------------
// Bloco 2, Ex. 2.02
// Formal Languages and Automata 
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// -----------------------------------
grammar SuffixCalculator;

//Parser Rules
program: stat* EOF;        					// Zero or more repetitions of stat
stat: expr? NEWLINE;     						// Optativeexpr
expr:
		expr expr op=('*' | '/' | '+' | '-')	 #ExprSuffix
	| 	Number					 	             #ExprNumber
	;
//Lexer Rules
Number: [0-9]+('.' [0-9]+)?;
NEWLINE: '\r' ?  '\n';
WS: [\t ]+ -> skip;  
