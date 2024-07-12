grammar CSV;

//Parser Rules
file: header row+ ;
header: row ;

row: field (',' field)* '\r'? '\n' ;

field
    :   TEXT
    |   STRING
    
    ;

//Lexer Rules
TEXT : ~[,\n\r"]+ ;
STRING : '"' ('""'|~'"')* '"' ; // quote-quote is an escaped quote