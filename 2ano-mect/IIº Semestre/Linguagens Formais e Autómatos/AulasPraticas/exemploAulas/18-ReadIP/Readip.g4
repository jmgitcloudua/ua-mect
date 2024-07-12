grammar Readip;

//Parser Rules
main: file* EOF;
file: row+;                ​// parser rule matching rows of log file​​ 
row: ip STRING INT NL;    ​// match log file record​​ 
ip: INT ​'.'​ INT ​'.' INT ​'.'​ INT; ​// match IPs in parser​​ ​

//Lexer Rules
INT: [0-9]+;        ​// match IP octet or HTTP result code​​ 
STRING: ​'"'​.*?​'"';   ​// matches the HTTP protocol command​​
NL: ​'\n'​;          ​// match log file record terminator​​ 
WS: ​''​ -> skip;   ​// ignore spaces