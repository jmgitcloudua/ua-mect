import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Linguagens Formais e Autómatos(LFA) | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
public class Ex102 {

   static double prevResult = 0;
	static Map<String, Double> map = new HashMap<>();
	
	public static void main(String[] args) {
		
		Scanner sc = new Scanner(System.in);
		
		System.out.println("\nFollow this exemple below");
      System.out.println("\t n = 10");
      System.out.println("\t 4 * n");
      System.out.println("\t n = n + 1");
      System.out.println("\t n + 5");
		System.out.println("\t\t* ( now with assignments [=] & operations using the last result [.] )");
		
		while(true) {
			System.out.print(" -> ");
			String[] in = sc.nextLine().split("[ ]+");
			
			// handle variable name
			if (in.length == 1 && map.containsKey(in[0])) {
				prevResult = map.get(in[0]);
				System.out.println(">> " + prevResult);
				continue;
			}
			
			// handle expressions
			try {
				String operator = in[1];
				switch(operator) {
				case "+":
				case "-":
				case "/":
				case "*":
					prevResult = simpleCalculator(in);
					System.out.println(">> " + prevResult);
					break;
				case "=":
					// guarantee variable is a number
					try { 
						Double.parseDouble(in[0]);
						System.out.println("Illegal left value!");
					} catch(Exception e) {
						prevResult = parseAssignment(in);
						map.put(in[0], prevResult);
						System.out.println(">> " + in[0] + " = " + prevResult);
					}
					break;
				default:
					System.err.println("Wrong usage - unsupported format.");
				}
			} catch(Exception e) {
				System.err.println("Wrong usage - unsupported format.");				
				sc.close();
			}
		}
	}
	
	/**
	 * Processes an operand, supporting numbers (doubles), map and the previous result (=0 if no operation has been done yet)
	 * @param operand String to process
	 * @return
	 */
	public static double getOperand(String operand) {
		if (operand.equals(".")) {
			return prevResult;
		} else if (map.containsKey(operand)) {
			return map.get(operand);
		} else {
			return Double.parseDouble(operand);
		}
	}
	
	/**
	 * Calculates a simple operation ( + | - | / | * )
	 * @param line a String array with three elements, space separated: [num] [op] [num]
	 * @return the result of the operation
	 */
	public static double simpleCalculator(String[] line) {
		String operator = line[1];
		double operandOne = getOperand(line[0]);
		double operandTwo = getOperand(line[line.length-1]);
		if (line.length > 3) {
			operandOne = simpleCalculator(Arrays.copyOfRange(line, 0, line.length - 2));
			operator = line[line.length-2];
		}
		switch(operator) {
		case "+":
			return operandOne + operandTwo;
		case "-":
			return operandOne - operandTwo;
		case "/":
			return operandOne / operandTwo;
		case "*":
			return operandOne * operandTwo;
		default:
			System.err.println("Wrong usage - unsupported format.");
			return Double.NaN;
		}
	}
	
	/**
	 * Parses the right-hand side of an assignment, which could be a value or an expression
	 * @param s
	 */
	public static double parseAssignment(String[] in) {
		if (in.length < 3)  { // freak case of operations like "n ="
			return 0; 
		} else if (in.length == 3) { 
			return getOperand(in[2]); 
		} else {
			String[] expression = Arrays.copyOfRange(in, 2, in.length);
			return simpleCalculator(expression);
		}
	}
    
}
