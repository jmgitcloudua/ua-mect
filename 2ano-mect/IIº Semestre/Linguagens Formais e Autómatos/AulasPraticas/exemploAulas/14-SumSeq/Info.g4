grammar Info;
@header {
import static java.lang.System.*; 
}
main : seq1=seq[ true ] seq2=seq[ false ] {
    out.println( "average ( seq1 ) : "+ $seq1.average);
    out.println( "average ( seq2 ) : "+ $seq2.average);
    };
seq[ boolean crash ] returns[ double average =0 ]
locals[ int sum =0 , int count =0 ] :
    '(' ( INT { $sum+=$INT.int ; $count ++;} )* ')' {
    if ( $count >0 )
        $average = ( double ) $sum / $count ;
    else if ( $crash) {
        err.println ( "ERROR: divide by zero! " ) ;
        exit( 1 ) ;
        } 
    }
    ;
INT : [0-9]+;
WS: [ \t\n\r]+  -> skip ;