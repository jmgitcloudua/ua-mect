import java.util.*;

/**
 * Nome Jodionisio da Lucinda João Muachifi Nº Mec: 97147 Cadeira de :
 * Linguagens Formais e Autómatos(LFA) | 2º Ano-2º semestre Curso: MIECT Marcço
 * 2021
 */
public class Ex107 {

  static Scanner in = new Scanner(System.in);

  public static void main(String[] args) {
   
	while(in.hasNextLine()){
		String val = in.nextLine();
		Scanner sc = new Scanner(val);
	
    ExpressionTree expTree = new ExpressionTree(sc.next());
    System.out.println(expTree.toString());
    System.out.println(expTree.toInfix(false));
    System.out.println(expTree.toInfix(true) + " = " + expTree.eval());

    System.out.println("\n");

    /*expTree = new ExpressionTree(sc.next());
    System.out.println(expTree.toString());
    System.out.println(expTree.toInfix(false));
    System.out.println(expTree.toInfix(true) + " = " + expTree.eval());*/

    System.out.println("\n");
	}
    /*try {
      expTree = new ExpressionTree("+ * 3 + 2 1 - 2 ");
    } catch (Exception e) {
		System.err.println("Handle incorrect expressions using exceptions:");
      	e.printStackTrace();
    }*/
  }
}

class ExpressionTree {

  private String node;
  private ExpressionTree left, right;

  /**
   * Creates an ExpressionTree from an expression in prefix-format
   *
   * @param expression
   */
  public ExpressionTree(String expression) {
    if (expression.trim().isEmpty()) return;
    populate(expression);
  }

  private ExpressionTree() {}

  private String populate(String exp) { // can be simplified
    // assert !exp.isEmpty();
    String[] expParts = exp.split(" ", 2);
    if (expParts[0].matches("[-+*/]")) { // operation
      // check at least two operands remain, otherwise throw an exception
      if (expParts[1].split(" ").length < 2) throw new IllegalArgumentException(
        "Incorrect expression - insufficient operands!"
      );

      node = expParts[0];
      left = new ExpressionTree();
      String newExp = left.populate(expParts[1].trim());
      right = new ExpressionTree();
      return right.populate(newExp).trim();
    } else { // operand
      // check operand is a number, otherwise throw an exception
      if (
        !expParts[0].matches("-?\\d+(\\.\\d+)?")
      ) throw new IllegalArgumentException(
        "Incorrect expression - unsupported symbol!"
      );

      node = expParts[0];
      left = right = null;
      if (expParts.length > 1) {
        return expParts[1].trim();
      } else {
        return "";
      }
    }
  }

  /**
   * Computes the expression
   *
   * @return the expression's result (a double)
   */
  public double eval() {
    if (node.matches("[-+*/]")) {
      switch (node) {
        case "+":
          return left.eval() + right.eval();
        case "-":
          return left.eval() - right.eval();
        case "/":
          return left.eval() / right.eval();
        default: // *
          return left.eval() * right.eval();
      }
    } else {
      return Double.parseDouble(node);
    }
  }

  /**
   * String representation of the ExpressionTree, using infix-format notation
   *
   * @param parens a flag for whether to use parenthesis (true) or not (false)
   * @return
   */
  public String toInfix(boolean parens) {
    if (left == null) return node;
    String str = parens ? "(" : "";
    str += left.toInfix(parens) + " " + node;
    if (right != null) str += " " + right.toInfix(parens);
    return parens ? str + ")" : str;
  }

  /**
   * String representation of the ExpressionTree, using prefix-format notation
   *
   * @param parens a flag for whether to use parenthesis (true) or not (false)
   * @return
   */
  /*public String creatPrefix(boolean parans) {
		if (in.hasNextDouble()) {
			
		} else {

		}
		return 0;
	}*/

  /**
   * String representation of the ExpressionTree, using prefix-format notation
   */
  public String toString() {
    String str = node;
    if (left != null) str += " " + left.toString();
    if (right != null) str += " " + right.toString();
    return str;
  }
}
