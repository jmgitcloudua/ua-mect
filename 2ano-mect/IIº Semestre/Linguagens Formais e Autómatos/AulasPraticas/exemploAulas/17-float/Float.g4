grammar Float;

//Parser Rules
main: stat* EOF;
stat: FLOAT;
FLOAT: DIGIT+'.'DIGIT*
    |   '.' DIGIT+
    ;
//Lexer Rules
fragment
DIGIT: [0-9];
WS: [\t\r\n]+ ->skip;