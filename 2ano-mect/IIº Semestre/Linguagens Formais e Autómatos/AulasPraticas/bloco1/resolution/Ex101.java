import java.util.*;

/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Linguagens Formais e Autómatos(LFA) | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
public class Ex101{

    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
       
        while (true) {
            System.out.println("Operation (number op number):");
            double result = 0.0D;
            double num1 = scInput();
            if (!sc.hasNext()) {
               System.err.printf("ERROR: read operator failure\n");
               System.exit(1);
            }
            String str = sc.next();
            double num2 = scInput();
            byte op = -1;
            switch(str.hashCode()) {
            case 42:
               if (str.equals("*")) {
                  op = 2;
               }
               break;
            case 43:
               if (str.equals("+")) {
                  op = 0;
               }
            case 44:
            case 46:
            default:
               break;
            case 45:
               if (str.equals("-")) {
                  op = 1;
               }
               break;
            case 47:
               if (str.equals("/")) {
                  op = 3;
               }
            }
                
                switch (op) {
                    case 0:
                        result = num1+num2;
                        break;
                    case 1:
                        result = num1-num2;
                        break;
                    case 2:
                        result = num1*num2;
                        break;
                    case 3:
                    if (num2 == 0.0D) {
                        System.err.printf("ERROR: divide by zero\n");
                        System.exit(1);
                     }
                        result = num1/num2;
                        break;
                    default:
                        System.err.printf("ERROR: invalid operator \"%s\"\n", str);
                        System.exit(1);
                        break;
                }
                System.out.printf("%2.2f %s %2.2f = %2.4f\n", num1, str, num2, result);
           
        }
    }
    private static double scInput() {
        if (!sc.hasNextDouble()) {
           System.err.printf("ERROR: read number failure\n");
           System.exit(1);
        }
  
        return sc.nextDouble();
     }
}