grammar CalFraction;

//Parser Rules
main: (stat ';')* EOF;

stat: assign | print;

assign:  expr '->' ID;

print: 'print' expr;

expr:  <assoc=right> expr POWER		#powerExpr
   |   e1=expr op=('*' | ':') e2=expr   #multDivExpr
   |   e1=expr op=('+' | '-') e2=expr   #addSubExpr
   |   '(' expr ')'                     #parentExpr
   |  REDUCE expr			#reduceExpr
   |  FRACTION 				#fractionExpr
   |  ID				#idExpr
   ;
//Lexer Rules
POWER: '^' INTEGER;
REDUCE: 'reduce'; 
FRACTION: INTEGER ('/' INTEGER)?;
INTEGER: ('-' | '+')?[0-9]+;
ID: [a-z]+;

COMMENT: '//'.*?'\n'->skip;
WS: [ \n\r\t]+->skip;
ERROR: .;
