grammar Quiz;

//Parser Rules
file: question* EOF;
question: ID '.' ID '(' String ')' '{' answer+  '}';

answer: String ':' INT ';';
String: '"'.*? '"';

//Lexer Rules
INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]*;   
COMMENT: '#' .*? '\n' ->skip;
WS: [ \n\r\t]+ ->skip;