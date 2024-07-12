grammar StrLang;

// Parser Rules
main: (statement)* EOF;

statement:  print | assignment;

print:      PRINT text;

assignment: ID COLON text;

text:       input                                   #textInput
    |       text PLUS text                          #textConcat
    |       text BACKSLASH text BACKSLASH text      #textReplace
    |       OPEN_PAR text CLOSE_PAR                 #textParenthesis
    |       ID                                      #textID
    |       STRING                                  #textString
    ;

input: INPUT OPEN_PAR STRING CLOSE_PAR;

//Lexer Rules
INPUT: 'input';
PRINT: 'print';

OPEN_PAR: '(';
CLOSE_PAR: ')';
COLON: ':';
PLUS: '+';
BACKSLASH: '/';

STRING: '"' (ESC | .)*? '"';
ESC: '\\"' | '\\\\';

ID: [a-zA-Z][0-9A-Za-z]*;

COMMENTS: '//'.*?'\n'->skip;
WS: [ \t\n\r]+->skip;
ERROR:.;
