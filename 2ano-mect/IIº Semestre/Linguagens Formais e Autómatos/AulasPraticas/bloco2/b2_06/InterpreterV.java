import java.util.HashMap;
import java.util.Map;

public class InterpreterV extends CalculatorBaseVisitor<Integer> {

  Map<String, Integer> map = new HashMap<String, Integer>();

  /** expr NEWLINE , print the result */
  @Override
  public Integer visitExprPrint(CalculatorParser.ExprPrintContext ctx) {
    Integer value = visit(ctx.expr()); // evaluate the expr child
    System.out.println(value); // print the result
    return null; // return dummy value
  }

  /** ID '=' expr NEWLINE */
  @Override
  public Integer visitExprAssign(CalculatorParser.ExprAssignContext ctx) {
    String id = ctx.ID().getText(); // id is left-hand side of '='
    Integer value = visit(ctx.expr()); // compute value of expression on right
    map.put(id, value); // store it in our HashMap
    return value;
  }

    /** expr op=('+'|'-') expr */
  @Override
  public Integer visitExprAddSub(CalculatorParser.ExprAddSubContext ctx) {
    Integer v1 = visit(ctx.expr(0)); // get value of left subexpression
    Integer v2 = visit(ctx.expr(1)); // get value of right subexpression
    if (ctx.op.getType() == CalculatorParser.ADD) {
      return v1 + v2;
    } else {
      return v1 - v2; // must be SUB
    }
  }

  /** '(' expr ')' */
  @Override
  public Integer visitExprParent(CalculatorParser.ExprParentContext ctx) {
    return visit(ctx.expr()); // return child expr's value
  }

  /** expr op=('*'|'/') expr */
  @Override
  public Integer visitExprMultDiv(CalculatorParser.ExprMultDivContext ctx) {
    Integer v1 = visit(ctx.expr(0)); // get value of left subexpression
    Integer v2 = visit(ctx.expr(1)); // get value of right subexpression
    if (ctx.op.getType() == CalculatorParser.MUL) {
      return v1 * v2;
    } else {
      return v1 / v2; // must be DIV
    }
  }

  /* Integer*/
  @Override
  public Integer visitExprInteger(CalculatorParser.ExprIntegerContext ctx) {
    return Integer.valueOf(ctx.Integer().getText());
  }

  /* ID */
  @Override
  public Integer visitExprId(CalculatorParser.ExprIdContext ctx) {
    String id = ctx.ID().getText();
    if (map.containsKey(id)) return map.get(id);
    return null;
  }
}
