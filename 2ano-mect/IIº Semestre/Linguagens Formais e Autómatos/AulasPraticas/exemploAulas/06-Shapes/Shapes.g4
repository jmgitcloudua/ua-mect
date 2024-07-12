grammar Shapes;
//parser rules
distance: 'distance' point point;
point: '(' x=NUMBER ',' y=NUMBER ')';
//lexer rules
NUMBER: [0-9]+;
WHITSPACE: [\t\r\n]+ -> skip;
