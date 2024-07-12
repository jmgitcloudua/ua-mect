public class Interpreter extends CalculatorBaseVisitor<Integer> {

  @Override
  public Integer visitProgram(CalculatorParser.ProgramContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public Integer visitStat(CalculatorParser.StatContext ctx) {
    Integer statExpr = visit(ctx.expr());
    System.out.println("Result = " + statExpr);
    return null;
  }

  @Override
  public Integer visitExprAddSub(CalculatorParser.ExprAddSubContext ctx) {
    Integer v1 = visit(ctx.expr(0));
    Integer v2 = visit(ctx.expr(1));
    Integer res = null;
    switch (ctx.op.getText()) {
      case "+":
        res = v1 + v2;
        break;
      case "-":
        res = v1 - v2;
        break;
      default:
        System.out.println("ERROR: This simbol not defined" + ctx.op.getText());
        break;
    }
    return res;
  }

  @Override
  public Integer visitExprParent(CalculatorParser.ExprParentContext ctx) {
    return visit(ctx.expr());
  }

  @Override
  public Integer visitExprMultDiv(CalculatorParser.ExprMultDivContext ctx) {
    Integer v1 = visit(ctx.expr(0));
    Integer v2 = visit(ctx.expr(1));
    Integer res = null;
    switch (ctx.op.getText()) {
      case "*":
        res = v1 * v2;
        break;
      case "%":
        res = v1%v2;
        break;
      case "/":
        if (v2 == 0) {
          System.out.println("ERROR: can not be divide by zero");
        }
        res = v1 / v2;
        break;
      default:
        System.out.println("ERROR: This simbol not defined" + ctx.op.getText());
        break;
    }
    return res;
  }

  @Override
  public Integer visitExprInteger(CalculatorParser.ExprIntegerContext ctx) {
    Integer exprInt = Integer.parseInt(ctx.Integer().getText());
    return exprInt;
  }

  @Override
  public Integer visitExprUnaryAddSub(
    CalculatorParser.ExprUnaryAddSubContext ctx
  ) {
    Integer value = visit(ctx.expr());
    if ("-".equals(ctx.op.getText())) return value * -1;
    return value;
  }
}
