public class InterpreterV extends ShapesBaseVisitor<Object> {

  @Override
  public Object visitStatement(ShapesParser.StatementContext ctx) {
    Double result = null;
    result = (Double) visit(ctx.expr());
    if (result != null) {
      System.out.println("Result:" + result);
    }
    return result;
  }

  @Override
  public Object visitDistance(ShapesParser.DistanceContext ctx) {
    Double[] p1 = (Double[]) visitPoint(ctx.p1);
    Double[] p2 = (Double[]) visitPoint(ctx.p2);

    return Math.sqrt(
      (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1])
    );
  }

  @Override
  public Object visitPoint(ShapesParser.PointContext ctx) {
    Double[] result = new Double[2];
    result[0] = (Double) visit(ctx.x);
    result[1] = (Double) visit(ctx.y);
    return result;
  }

  @Override
  public Object visitExprDistance(ShapesParser.ExprDistanceContext ctx) {
    return visitDistance(ctx.distance());
  }

  @Override
  public Object visitExprNumber(ShapesParser.ExprNumberContext ctx) {
    return Double.parseDouble(ctx.Number().getText());
  }

  @Override
  public Object visitExprMultDiv(ShapesParser.ExprMultDivContext ctx) {
   Double result = null;
    Double e1 = (Double) visit(ctx.expr(0));
    Double e2 = (Double) visit(ctx.expr(1));
    if (e1 != null && e2 != null) {
      switch (ctx.op.getText()) {
        case "*":
          result = e1 * e2;
          break;
        case "/":
            if (e2 == 0) {
               System.out.println("ERROR! Could not be divide by zero");
            }
          result = e1 / e2;
          break;
        default:
        System.out.println("Error! Try other again");
          break;
      }
    }
    return result;
  }
  

  @Override
  public Object visitExprParanthesis(ShapesParser.ExprParanthesisContext ctx) {
    return visit(ctx.expr());
  }

  @Override
  public Object visitExpAddSub(ShapesParser.ExpAddSubContext ctx) {
    Double result = null;
    Double e1 = (Double) visit(ctx.expr(0));
    Double e2 = (Double) visit(ctx.expr(1));
    if (e1 != null && e2 != null) {
      switch (ctx.op.getText()) {
        case "+":
          result = e1 + e2;
          break;
        case "-":
          result = e1 - e2;
          break;
        default:
        System.out.println("Error! Try other again");
          break;
      }
    }
    return result;
  }
}
