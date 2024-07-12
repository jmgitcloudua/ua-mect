import static java.lang.System.*;

import java.util.*;
import org.antlr.v4.runtime.tree.ParseTreeProperty;

public class InterpreterL extends ShapesBaseListener {

  @Override
  public void exitStatement(ShapesParser.StatementContext ctx) {
    Double res = ctx.expr().res;
    if (res != null) {
      System.out.println("[Listener]: " + res);
    }
  }

  @Override
  public void exitDistance(ShapesParser.DistanceContext ctx) {
    Point p1 = ctx.point(0).res;
    Point p2 = ctx.point(1).res;
    if (p1 != null && p2 != null) {
      ctx.res = p1.distanceTo(p2);
    }
  }

  @Override
  public void exitPoint(ShapesParser.PointContext ctx) {
    Double x = ctx.x.res;
    Double y = ctx.y.res;
    if (x != null && y != null) {
      ctx.res = new Point(x, y);
    }
  }

  @Override
  public void exitExprMultDiv(ShapesParser.ExprMultDivContext ctx) {
    Double e1 = ctx.expr(0).res;
    Double e2 = ctx.expr(1).res;
    if (e1 != null && e2 != null) {
      switch (ctx.op.getText()) {
        case "*":
          ctx.res = e1 * e2;
          break;
        case "/":
          if (e2 == 0) {
            System.out.println("ERROR! Could not be divide by zero");
          }
          ctx.res = e1 / e2;
          break;
        default:
          System.out.println("Error! Try other again");
          break;
      }
    }
  }

  @Override
  public void exitExpAddSub(ShapesParser.ExpAddSubContext ctx) {
    Double e1 = ctx.expr(0).res;
    Double e2 = ctx.expr(1).res;
    if (e1 != null && e2 != null) {
      switch (ctx.op.getText()) {
        case "+":
          ctx.res = e1 + e2;
          break;
        case "-":
          ctx.res = e1 - e2;
          break;
        default:
          System.out.println("Error! Try other again");
          break;
      }
    }
  }

  @Override
  public void exitExprParanthesis(ShapesParser.ExprParanthesisContext ctx) {
    ctx.res = ctx.expr().res;
  }

  @Override
  public void exitExprDistance(ShapesParser.ExprDistanceContext ctx) {
    ctx.res = ctx.distance().res;
  }

  @Override
  public void exitExprNumber(ShapesParser.ExprNumberContext ctx) {
    ctx.res = Double.parseDouble(ctx.Number().getText());
  }
}
