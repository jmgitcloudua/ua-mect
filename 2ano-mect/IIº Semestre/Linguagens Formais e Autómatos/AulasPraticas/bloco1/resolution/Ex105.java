import java.util.*;
/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Linguagens Formais e Autómatos(LFA) | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
public class Ex105 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (true) {
            System.out.print("Number Translator... enter a sentece below\n =>");
            String[] in = sc.nextLine().split(" |-");
            List<String> listNumbers = Arrays.asList( new String[] {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety", "hundred", "thousand", "hundred thousand", "million",  "hundred million", "thousand million"});
			Integer[] intNumbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50, 60, 70, 80, 90, 100, 1000, 100000, 1000000, 100000000, 1000000000};

            try {
                
                int sum = 0;
				int buffer = 0;
				for(String s : in) {
					if (listNumbers.contains(s)) {
						int num = intNumbers[listNumbers.indexOf(s)];
						if (buffer == 0) {
							buffer += num;
						} else if (num > buffer) {
							buffer *= num;
						} else {
							sum += buffer;
							buffer = num;
						}
					}else{
                        System.out.println("Number text " + s + " does not exist in the list");
                        System.exit(1);
                    }
				}
				sum += buffer;
				System.out.println(sum);
            } catch (Exception e) {
                System.err.println(" something went wrong!\uD83D\uDE00");	
				sc.close();
            }
        }
    }
}
