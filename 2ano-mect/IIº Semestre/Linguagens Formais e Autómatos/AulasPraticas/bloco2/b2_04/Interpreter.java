public class Interpreter extends PrefixCalculatorBaseVisitor<Double> {

  @Override
  public Double visitProgram(PrefixCalculatorParser.ProgramContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public Double visitStat(PrefixCalculatorParser.StatContext ctx) {
    Double getExpr = visit(ctx.expr());
    System.out.println("Result = " + getExpr);
    return null;
  }

  @Override
  public Double visitExprPrefix(PrefixCalculatorParser.ExprPrefixContext ctx) {
    Double v1 = (Double) visit(ctx.expr(0));
    Double v2 = (Double) visit(ctx.expr(1));
    Double res = null;
    switch (ctx.op.getText()) {
      case "*":
        res = v1 * v2;
        break;
      case "/":
        if (v2 == 0) {
          System.out.println("ERROR: Can not be divided by zero");
        }
        res = v1 / v2;
        break;
      case "+":
        res = v1 + v2;
        break;
      case "-":
        res = v1 - v2;
        break;
      default:
        System.out.println("ERROR: operand does not exist");
        break;
    }
    return res;
  }

  @Override
  public Double visitExprNumber(PrefixCalculatorParser.ExprNumberContext ctx) {
    Double vExprNum = Double.parseDouble(ctx.Number().getText());
    return vExprNum;
  }
}
