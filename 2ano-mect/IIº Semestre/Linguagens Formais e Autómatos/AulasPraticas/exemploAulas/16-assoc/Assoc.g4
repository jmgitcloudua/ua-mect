grammar Assoc;

//Parser Rules
main : stat* EOF;
stat: expr;
expr: expr '^'<assoc=right> expr
    |   expr '*' expr
    |   expr '+' expr
    | INT
    ;

//Lexer Rules
INT: [0-9]+; 
WS: [\n\r\t]+ ->skip;