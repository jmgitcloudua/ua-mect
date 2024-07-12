grammar Expr ;
stat : assign ;
assign : ID '=' expr ';' ;
expr : INT ;
ID : [a-z]+ ;
INT : [0-9]+ ;
WS : [ \t\r\n]+ -> skip ;