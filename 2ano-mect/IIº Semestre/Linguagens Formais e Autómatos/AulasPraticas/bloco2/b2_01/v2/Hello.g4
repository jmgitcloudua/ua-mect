// -----------------------------------
// Bloco 2, Ex. 2.01
// Formal and Automated Languages
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// Vertion 2.0
// -----------------------------------
grammar Hello;                                                                   // Define a grammar called Hello                                                     // Define a grammar called Hello

// Parser Language Rules
main: (greetings | bye)* EOF;                                       
greetings : 'hello' ID;                                                         // match keyword hello followed by an ID
bye : 'bye' ID;    
// Lexer Language Rules
ID : [a-zA-Z]+ ;                                                                // match lower−case identifiers
WS : [ \t\r\n]+ -> skip ;                                                       // skip spaces, \t, \n, \r (Windows)                                                         // skip spaces, tabs, newlines, \r(Windows)

