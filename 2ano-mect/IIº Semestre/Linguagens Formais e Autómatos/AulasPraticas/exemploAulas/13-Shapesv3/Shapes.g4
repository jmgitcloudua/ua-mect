grammar Shapes;

// parser rules:
main: statement* EOF;
statement: expr; // you can use distance var
distance returns[Double res = null]: 'distance' point point;
point returns[Point res = null]: '(' x=expr ',' y=expr ')';
expr returns[Double res = null]: 
        expr op=('*' | '/') expr #ExprMultDiv
    |   expr op=('+' | '-') expr #ExpAddSub
    |   '(' expr ')'             #ExprParanthesis            
    |   distance                 #ExprDistance
    |   Number                   #ExprNumber
    ;

// lexer rules:
Number: [0-9]+;
WS: [\r\t\n]+ -> skip;