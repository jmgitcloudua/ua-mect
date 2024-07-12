import java.util.*;

/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Linguagens Formais e Autómatos(LFA) | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
public class Ex101_v3{

    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
         var s = "";
         double num1, num2, result = 0.0D;
         String splited_s[];
        do{
            //sc.nextLine();
            System.out.println("Operation (number op number):");
            s = sc.nextLine();
            splited_s = s.split(" ");
           try {
              if (splited_s.length == 3) {
                 num1  = Double.parseDouble(splited_s[0]);
                 num2  = Double.parseDouble(splited_s[2]);
                 switch (splited_s[1]) {
                  case "+":
                      result = num1+num2;
                      break;
                  case "-":
                      result = num1-num2;
                      break;
                  case "*":
                      result = num1*num2;
                      break;
                  case "/":
                  if (num2 == 0.0D) {
                      System.err.printf("ERROR: divide by zero\n");
                      System.exit(1);
                   }
                      result = num1/num2;
                      break;
                  default:
                        System.err.printf("ERROR: invalid operator \"%s\"\n", splited_s[1]);
                        System.exit(1);
                        break;
                     
                      
                     
              }
              System.out.printf("%2.2f %s %2.2f = %2.4f\n", num1, splited_s[1], num2, result);
              }
              
              
           } catch (Exception e) {
            System.err.println("Wring usage-unsuported format");
            sc.close();
           }
          

                
                
           
        }while(true);
    }
    
}