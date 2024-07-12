import java.util.*;

public class InterpreterV extends CalculatorBaseVisitor<String> {

  Map<String, Integer> map = new HashMap<>();

  @Override
  public String visitMain(CalculatorParser.MainContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public String visitStat(CalculatorParser.StatContext ctx) {
    String getstat = visit(ctx.expr());
    System.out.println(" -> " + getstat);

    return null;
  }

  /** expr op=('+'|'-') expr */
  @Override
  public String visitExprAddSub(CalculatorParser.ExprAddSubContext ctx) {
    return (
      visit(ctx.expr(0)) + " " + visit(ctx.expr(1)) + " " + ctx.op.getText()
    );
  }

  /** expr op=('*'|'/') expr */
  @Override
  public String visitExprMultDiv(CalculatorParser.ExprMultDivContext ctx) {
    return (
      visit(ctx.expr(0)) + " " + visit(ctx.expr(1)) + " " + ctx.op.getText()
    );
  }

  @Override
  public String visitExprParent(CalculatorParser.ExprParentContext ctx) {
    return visit(ctx.expr());
  }

  @Override
  public String visitExprInt(CalculatorParser.ExprIntContext ctx) {
    return ctx.Int().getText();
  }

  @Override
  public String visitAssignment(CalculatorParser.AssignmentContext ctx) {
    String id = ctx.ID().getText();
    String value = visit(ctx.expr());

    return id + "=" + value;
  }

  @Override
  public String visitExprId(CalculatorParser.ExprIdContext ctx) {
    String id = ctx.ID().getText();
    return id;
  }

  @Override
  public String visitExprUnaryAddSub(CalculatorParser.ExprUnaryAddSubContext ctx) {
    String s = visit(ctx.expr());

    return s + "!" + ctx.op.getText();
  }
}
