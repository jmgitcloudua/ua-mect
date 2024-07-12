grammar FracLang;

//Parser Rules
main: (stat ';')* EOF;

stat: display | assign;

display: 'display' expr;

assign: ID '<=' expr;

expr:       op=('+' | '-') expr             #unaryExpr
    |   expr op=('*' | ':') expr            #multDivExpr
    |   expr op=('+' | '-') expr            #addSubExpr
    |   'reduce' expr                       #reduceExpr
    |   '(' expr ')'                        #parentExpr
    |   'read' STRING                       #readExpr
    |   FRACTION                            #fractionExpr
    |   ID                                  #idExpr                    
    ;

//Lexer Rules
STRING: '"'.*?'"';
ID: [a-z]+;
FRACTION: NUM ('/' NUM)?;
NUM: [0-9]+;
COMMENT: '--'.*?'\n'->skip;
WS: [ \n\t\r]+->skip;
ERROR: .;
