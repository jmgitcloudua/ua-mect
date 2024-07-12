import java.util.*;

/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Linguagens Formais e Autómatos(LFA) | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
public class Ex101_v2 {

    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        
        System.out.println("Enter two number: ");
        double num1 = sc.nextDouble();
        double num2 = sc.nextDouble();  

        double result = 0.0D;

        System.out.print("Enter an operator [+, -, *, /]: ");
        char op = sc.next().charAt(0);

      

         try {

            switch (op) {
                case '+':
                    result = num1+num2;
                    break;
                case '-':
                    result = num1-num2;
                    break;
                case '*':
                    result = num1*num2;
                    break;
                case '/':
                    if (num2 == 0.0D) {
                        System.err.printf("ERROR: divide by zero\n");
                        System.exit(1);
                    }
                    result = num1/num2;
                    break;
            
                default:
                    System.err.printf("ERROR: invalid operator \"%c\"\n", op);
                    System.exit(1);
                    break;
            }
            System.out.printf("%2.2f %s %2.2f = %2.4f\n", num1, op, num2, result);
             
         } catch (Exception e) {
             System.err.println("Wring usage-unsuported format");
             sc.close();
         }




    }
    
}
