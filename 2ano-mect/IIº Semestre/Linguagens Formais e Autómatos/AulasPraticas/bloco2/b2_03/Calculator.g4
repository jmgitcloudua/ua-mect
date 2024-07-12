// -----------------------------------
// Bloco 2, Ex. 2.03
// Formal and Automated Languages
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// -----------------------------------
grammar Calculator;

// Parser Rules
program: stat* EOF;
stat: expr? NEWLINE;
expr:
        expr op=('*' | '/' | '%') expr      #ExprMultDiv
    |   expr op=('+' | '-') expr            #ExprAddSub
    |   Integer                             #ExprInteger
    |   '(' expr ')'                        #ExprParent
    |       op=('+' | '-') expr             #ExprUnaryAddSub
    ;
// Lexer Rules
Integer: [0-9]+;                    //implementing with long integers
NEWLINE: '\r'? '\n';
WS: [ \t]+ -> skip;
COMMENT: '#' .*? '\n' -> skip;