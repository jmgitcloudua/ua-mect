grammar Shapes;
// parser rules:
main: statement* EOF;
statement: expr; // you can use distance var
distance: 'distance' p1=point p2=point;
point: '(' x=expr ',' y=expr ')';
expr: 
        expr op=('*' | '/') expr #ExprMultDiv
    |   expr op=('+' | '-') expr #ExpAddSub
    |   '(' expr ')'             #ExprParanthesis            
    |   distance                 #ExprDistance
    |   Number                   #ExprNumber
    ;

Number: [0-9]+;
// lexer rules:
WS: [\r\t\n]+ -> skip;