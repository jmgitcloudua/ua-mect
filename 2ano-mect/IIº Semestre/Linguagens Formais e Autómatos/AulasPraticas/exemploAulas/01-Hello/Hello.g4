grammar Hello;                // define a grammar called Hello
// parser (first letter in lower case):
r : 'hello' ID ;            // match keyword hello followed by an identifier
// lexer (first letter in upper case):
ID : [a-z]+ ;               // match lower-ase identifiers
WS : [\t\r\n]+ -> skip ;    // skip spaces, tabs, newlines (Windows)