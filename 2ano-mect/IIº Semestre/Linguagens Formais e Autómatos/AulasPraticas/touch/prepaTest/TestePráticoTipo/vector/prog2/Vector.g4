grammar Vector;

//Parser Rules
main: (stat? ';')*;

stat:   'show' value                        #showStat                                  
    |   value '->' ID                       #assignStat
    ;

value:  '(' value ')'                       #parentValue
    |   op=('+' | '-') value                #signalValue
    |   v1=value op=('+' | '-') v2=value    #addSubValue
    |   REAL                                #realValue
    |   vector                              #vectorValue  
    |   ID                                  #idValue
    ;

vector: '[' REAL (',' REAL)* ']';   


//Lexer Rules
REAL :  [1-9]+ ('.' [0-9]+)?  ;
ID:            [a-z]([a-z0-9]+)? ;
COMMENT:       '#' .*? '\n' -> skip ;
WS:            [ \n\t]+ -> skip ;
ERROR: .;