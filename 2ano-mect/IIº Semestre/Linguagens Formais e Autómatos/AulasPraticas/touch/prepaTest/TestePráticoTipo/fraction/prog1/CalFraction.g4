grammar CalFraction;


//Parser Rules
main: (stat ';')* EOF;

stat: print | assign;

print: 'print' expr ;
assign: expr '->' ID;

expr:   <assoc=right> expr POWER            #powerExpr
    |    expr op=('*' | ':') expr           #multDivExpr
    |   expr op=('+' | '-') expr            #addSubExpr
    |   REDUCE expr                         #reduceExpr
    |   '(' expr ')'                        #parentExpr
    |   ID                                  #idExpr
    |   FRACTION                            #fractionExpr
    ;

//Lexer Rules
REDUCE: 'reduce';
FRACTION: INTEGER ('/' INTEGER)?;
POWER: '^' INTEGER;


INTEGER:   ('-' | '+')? [0-9]+;
ID: [a-z]+;

COMMENTS:   '//' .*? '\n' -> skip;
WS:         [ \t\r\n]+ 	-> skip;
ERROR: .;

