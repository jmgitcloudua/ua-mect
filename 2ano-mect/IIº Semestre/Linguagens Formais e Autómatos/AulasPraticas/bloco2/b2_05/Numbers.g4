// -----------------------------------
// Bloco 2, Ex. 2.05
// Formal and Automated Languages
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// -----------------------------------
grammar Numbers;

//Parser Rules
file: line* EOF;                   // the file is composed with zero or more lines
line: Number '-' Word NEWLINE;       //  each line has a form Num - Word and terminate with change line

//Lexer Rules
Number: [0-9]+;
Word: [a-zA-Z]+;
NEWLINE: '\r'? '\n';
Ws: [ \t]+ ->skip;
