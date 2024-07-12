import java.util.*;

public class Test {

  static Scanner sc = new Scanner(System.in);

  public static void main(String args[]) {
    System.out.println("Enter an algebraic expression like: 5 + 6 * 7");
    ExpressionTree y = new ExpressionTree(sc.nextLine());
    print(y);
    //System.out.print(y.eval());
  }

  public static void print(ExpressionTree y) {
    System.out.println("Prefix: " + y.prefix());
    System.out.println("Postfix: " + y.postfix());
    System.out.println("Fully parenthesised: " + y.fullyParenthesised() );
    System.out.println("-----------------");
  }

}
