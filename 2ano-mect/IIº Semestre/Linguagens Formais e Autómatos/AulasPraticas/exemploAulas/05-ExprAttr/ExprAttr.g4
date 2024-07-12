grammar ExprAttr ;
stat : assign ;
assign : ID '=' e= expr ';'
{ System.out.println ($ID.text +" = "+ $e.v ) ; } // action
;
expr returns [ int v ] : INT // result attribute named v in expr
{ $v = Integer.parseInt ( $INT.text ) ; } // action
;
ID : [a-z]+ ;
INT : [0-9]+ ;
WS : [\t\r\n]+ -> skip ;