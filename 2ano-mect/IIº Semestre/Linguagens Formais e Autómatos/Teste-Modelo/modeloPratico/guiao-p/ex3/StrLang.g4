grammar StrLang;

//Parser Rules
main: (stat )* EOF;

stat: print | assign;

print: 'print' expr;

assign: ID ':' expr;

expr:   
        expr '+' expr                   #concatExpr
    |   expr '-' expr                   #removeExpr
    |   'trim' expr                     #trimExpr
    |   '(' expr ')'                    #parentExpr
    |   expr '/'  expr '/' expr         #replaceExpr
    |   input                           #inputExpr
    |   STRING                          #stringExpr
    |   ID                              #idExpr
    ;  
input: 'input' '(' STRING ')';

//Lexer Rules
STRING: '"' (ESC | .)*? '"';
ESC: '\\"' | '\\\\';
ID: [a-zA-Z][0-9A-Za-z]*;
COMMENT: '//'.*? '\n'->skip;
WS: [ \n\r\t]+ ->skip;
ERROR: .;

