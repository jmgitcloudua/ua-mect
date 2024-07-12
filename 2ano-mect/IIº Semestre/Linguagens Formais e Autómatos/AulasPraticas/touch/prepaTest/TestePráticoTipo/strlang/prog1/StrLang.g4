grammar StrLang;

main: (statement)* EOF;

statement:   print | declaration;

print:  'print' (STRING|VAR|op);

declaration: 
        VAR ':' STRING              #declarationString
    |   VAR ':' input               #declarationInput
    ;

input:  'input' '('STRING')';

op: '(' op '/' op '/' op ')'        #opReplace
    |    op '+' op                  #opAdd
    |   STRING                      #opString
    |   VAR                         #opVar
    ;

VAR: (INT|TXT)+;
STRING: '"' .*? '"';
INT: [0-9]+;
TXT: [a-zA-Z]+;
LINECOMMENT: '//' .*? '\n' -> skip;
WS: [ \t\r\n]+ -> skip;
ERROR: .;