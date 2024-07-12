// -----------------------------------
// Bloco 2, Ex. 2.08
// Formal and Automated Languages
// Jodionisio Muachifi, 97147, MIECT
// Abril 2021 | 2ºAno-2ºSemestre
// -----------------------------------
// • 2 + 3 -> 2 3 +
// • 2 + 3 = 4 -> 2 3 4 = +
// • 3 * (2 + 1) + (2 − 1) -> 3 2 1 + * 2 1 − 
grammar Calculator;

// Parser Rules
main: (stat | assignment)* EOF;
stat:   expr NEWLINE;               
assignment:  ID '=' expr NEWLINE ;   
expr:
        op=('+' | '-') expr         #ExprUnaryAddSub
    |   expr op=('*' | '/') expr    #ExprMultDiv
    |   expr op=('+' | '-') expr    #ExprAddSub
    |   Int                         #ExprInt
    |   '(' expr ')'                #ExprParent
    |   ID                          #ExprId
    ;
// Lexer Rules
ID: [a-zA-Z]+([a-zA-Z_0-9]+)?;      // match identifiers
Int: [0-9]+('.'[0-9+])?;        // match integers
NEWLINE:'\r'? '\n' ;                // return newlines to parser (is end-statement signal)
WS: [ \t]+ -> skip ;                // out whitespace