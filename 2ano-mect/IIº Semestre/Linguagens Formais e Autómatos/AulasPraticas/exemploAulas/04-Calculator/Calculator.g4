grammar Calculator;

operation
    : left=NUMBER operator='+' right=NUMBER
    | left=NUMBER operator='-' right=NUMBER
    | left=NUMBER operator='*' right=NUMBER
    | left=NUMBER operator='/' right=NUMBER
    ;

NUMBER
   : ('0' .. '9') + ('.' ('0' .. '9') +)?
   ;
WS : [ \t\r\n]+ -> skip ;
//WS : (' ' | '\t')+ -> channel(HIDDEN);