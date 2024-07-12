// -----------------------------------
// Bloco 2, Ex. 2.01
// Formal and Automated Languages
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// -----------------------------------
grammar Hello;                                                                      // Define a grammar called Hello                                                     // Define a grammar called Hello

// Parser Language Rules
main : (greetings | bye)* EOF;                                       
greetings : 'hello' ids {System.out.println("Olá " + $ids.list);};                // match keyword hello followed by an ID
bye : 'bye' ids {System.out.println("Adeus " + $ids.list);};        
ids returns[String list=""] : ( ID {$list = $list + ($list.isEmpty() ? "" : ",") + $ID.text;})+;
// Lexer Language Rules
ID : [a-zA-Z]+ ;                                                                // match lower−case identifiers
WS : [ \t\r\n]+ -> skip ;                                                       // skip spaces, \t, \n, \r (Windows)                                                         // skip spaces, tabs, newlines, \r(Windows)

