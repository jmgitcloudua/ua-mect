import java.lang.*;
import java.util.*;
import utils.Fraction;

public class InterpreterV extends CalFracBaseVisitor<Fraction> {

  // Instance Fields
  private Map<String, Fraction> map = new HashMap<>();

  @Override
  public Fraction visitProgram(CalFracParser.ProgramContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public Fraction visitStat(CalFracParser.StatContext ctx) {
    if (ctx.print() != null) {
      return visit(ctx.print());
    } else {
      return visit(ctx.assign());
    }
  }

  @Override
  public Fraction visitAssign(CalFracParser.AssignContext ctx) {
    Fraction f = visit(ctx.expr());
    map.put(ctx.ID().getText(), f);

    return f;
  }

  @Override
  public Fraction visitPrint(CalFracParser.PrintContext ctx) {
    Fraction f = visit(ctx.expr());
    System.out.println(f);
    return f; // return null would be acceptable as well
  }

  @Override
  public Fraction visitExprFrac(CalFracParser.ExprFracContext ctx) {
    return new Fraction(ctx.FRAC().getText());
  }

  @Override
  public Fraction visitExprParentesis(CalFracParser.ExprParentesisContext ctx) {
    return visit(ctx.expr());
  }

  @Override
  public Fraction visitExprDivisionMultiply(
    CalFracParser.ExprDivisionMultiplyContext ctx
  ) {
    if (ctx.op.getText().equals("*")) {
      return Fraction.multiply(visit(ctx.expr(0)), visit(ctx.expr(1)));
    }
    return Fraction.divide(visit(ctx.expr(0)), visit(ctx.expr(1)));
  }

  @Override
  public Fraction visitExprAddDifference(
    CalFracParser.ExprAddDifferenceContext ctx
  ) {
    if (ctx.op.getText().equals("+")) {
      return Fraction.add(visit(ctx.expr(0)), visit(ctx.expr(1)));
    }
    return Fraction.subtract(visit(ctx.expr(0)), visit(ctx.expr(1)));
  }

  @Override
  public Fraction visitExprPower(CalFracParser.ExprPowerContext ctx) {
    return Fraction.power(
      visit(ctx.expr()),
      Integer.parseInt(ctx.POWER().getText().substring(1))
    );
  }

  @Override
  public Fraction visitExprReduce(CalFracParser.ExprReduceContext ctx) {
    return Fraction.reduce(visit(ctx.expr()));
  }

  @Override
  public Fraction visitExprVariable(CalFracParser.ExprVariableContext ctx) {
    String key = ctx.ID().getText();
    if (!map.containsKey(key)) {
      System.err.println("ID " + key + " not valid!");
      System.exit(1);
    }
    return map.get(key);
  }
}
