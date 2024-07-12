grammar PropertyFile;
file : prop+ EOF;
prop : ID '=' STRING '\n' ;
ID   : [a-z]+ ;
STRING : '"' .*? '"' ;
COMMENT: '#' .*? '\n' ->skip;
WS: [ \n\r\t]+ ->skip;