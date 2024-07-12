// -----------------------------------
// Bloco 2, Ex. 2.11
// Formal and Automated Languages
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// -----------------------------------
grammar SetCalc;

// Parser Rules
program   : line * EOF;

line      : expr;

expr      : '(' expr ')'                #ExprParentesis
          | expr '\\' expr              #ExprDiference
          | expr '&'  expr              #ExprIntersection
          | expr '+'  expr              #ExprUnion
          | set                         #ExprSet
          | assignment                  #ExprAssignment
          | ID                          #ExprID     
          ;

assignment: ID '=' expr 
          ;

set       : '{' (NUM  (',' NUM )*  )? '}'
          | '{' (WORD (',' WORD)* )? '}'
          ;

// Lexer Rules
NUM       : ('-'|'+')? [0-9]+;
WORD      : [a-z]+;
ID        : [A-Z]+;
COMMENTS  : '--' .*? '\n' -> skip;
//NEWLINE   : '\r'? '\n';
WS        : [ \t\r\n]+ -> skip;
ERROR : . ; // to convert all lexer errors into parser errors