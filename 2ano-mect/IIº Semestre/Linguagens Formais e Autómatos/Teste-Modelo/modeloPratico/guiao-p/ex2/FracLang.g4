grammar FracLang;

//Parser Rules
main: (stat ';')* EOF;

stat: display | assign;

display: 'display' expr;

assign: ID '<=' expr;

expr:  op=('+' | '-') expr          #unaryExpr
    |   expr op=('*' | ':') expr    #multDivExpr
    |   expr op=('+' | '-') expr    #addSubExpr
    |   'reduce' expr               #reduceExpr
    |   '(' expr ')'                #parentExpr
    |   FRACTION                    #fractionExpr
    |   ID                          #idExpr
    |   'read' STRING               #readExpr
    ;   

//Lexer Rules
FRACTION: INTEGER ('/' INTEGER)?;
STRING: '"'.*? '"';
ID: [a-z]+;
INTEGER: [0-9]+;
COMMENT: '--'.*?'\n' ->skip;
WS: [ \n\r\t]+ ->skip;
ERROR: .;