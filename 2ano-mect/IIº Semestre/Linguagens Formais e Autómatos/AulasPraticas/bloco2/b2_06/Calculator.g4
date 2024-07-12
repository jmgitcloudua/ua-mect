// -----------------------------------
// Bloco 2, Ex. 2.06
// Formal and Automated Languages
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// -----------------------------------
grammar Calculator;

// Parser Rules
program: stat+;
stat:   expr NEWLINE                # ExprPrint
    |   ID '=' expr NEWLINE         # ExprAssign
    |   NEWLINE                     # blank
    ;    

expr:
        expr op=('*' | '/') expr    #ExprMultDiv
    |   expr op=('+' | '-') expr    #ExprAddSub
    |   Integer                     #ExprInteger
    |   '(' expr ')'                #ExprParent
    |   ID                          #ExprId
    ;
// Lexer Rules
MUL :   '*' ; // assigns token name to '*' used above in grammar
DIV :   '/' ;
ADD :   '+' ;
SUB :   '-' ;
ID  :   [a-zA-Z]+ ;      // match identifiers
Integer :   [0-9]+ ;         // match integers
NEWLINE:'\r'? '\n' ;     // return newlines to parser (is end-statement signal)
WS  :   [ \t]+ -> skip ; // toss out whitespace