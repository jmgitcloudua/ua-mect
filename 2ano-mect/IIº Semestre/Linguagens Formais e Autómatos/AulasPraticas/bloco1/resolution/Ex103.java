import java.util.*;


/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Linguagens Formais e Autómatos(LFA) | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
public class Ex103 {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
		while(true) {
			Stack<Double> opdsStack = new Stack<>(); // variable declarion of operands for stack
			Queue<String> optsStack = new LinkedList<String>(); // variable declarion of operations for stack
			
			System.out.print("Reverse Polish Notation Calculator... enter an operation (eg: 1 2 3 * +)\n [Operation]==> ");

			
			try {
				String[] in = sc.nextLine().split(" ");
	
				//  input process
				for(int i = 0; i < in.length; i++) {
					
					if (in[i].matches("-?\\d+(\\.\\d+)?")) {
						System.out.println( (i != 0)? "Stack: " + opdsStack : "");;
						opdsStack.push(Double.parseDouble(in[i]));
					}
					else {
						for (int j = i; j < in.length; j++) {
							optsStack.add(in[j]);
						}
						break;
					}
					
				}
				
				// output calculate 
				while(!optsStack.isEmpty()) {
					System.out.println("Stack: " + opdsStack);
					String operator = optsStack.remove();
					switch(operator) {
					case "+":
						opdsStack.push(opdsStack.pop() + opdsStack.pop());
						System.out.println("Stack: " + opdsStack);
						break;
					case "-":
						opdsStack.push(opdsStack.pop() - opdsStack.pop());
						System.out.println("Stack: " + opdsStack);
						break;
					case "/":
						opdsStack.push(opdsStack.pop() / opdsStack.pop());
						System.out.println("Stack: " + opdsStack);
						break;
					case "*":
						opdsStack.push(opdsStack.pop() * opdsStack.pop());
						System.out.println("Stack: " + opdsStack);
						break;
					default:
						System.out.println("Wrong usage - unsupported operation.");
                        break;
					}
				}
				System.out.println("\n"); // just for elegant formatation
				
			} catch(Exception e) {
				System.err.println("Wrong usage - unsupported format.");
				sc.close();
			}
		}
	}
    
}
