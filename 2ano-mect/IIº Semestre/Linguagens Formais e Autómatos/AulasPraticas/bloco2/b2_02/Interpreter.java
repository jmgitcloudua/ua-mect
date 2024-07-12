public class Interpreter extends SuffixCalculatorBaseVisitor<Double> {

  @Override
  public Double visitProgram(SuffixCalculatorParser.ProgramContext ctx) {
    
   return visitChildren(ctx);
  }

  @Override
  public Double visitStat(SuffixCalculatorParser.StatContext ctx) {
   Double stat = (Double)visit(ctx.expr()); 
   System.out.println("Result =  " + stat);
   return null;
  }

  @Override
  public Double visitExprNumber(SuffixCalculatorParser.ExprNumberContext ctx) {
    Double exprNum = Double.parseDouble(ctx.Number().getText());
    return exprNum;
  }

  @Override
  public Double visitExprSuffix(SuffixCalculatorParser.ExprSuffixContext ctx) {
    Double v1 = visit(ctx.expr(0));
    Double v2 = visit(ctx.expr(1));
    Double res = null;
    switch (ctx.op.getText()) {
      case "*":
        res = v1 * v2;
        break;
      case "/":
        if (v2 == 0) {
          System.out.println("ERROR: can not divide by zero");
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
      System.out.println("ERROR: There are not this operation " + ctx.op );
        break;
    }
    return res;
  }
}
