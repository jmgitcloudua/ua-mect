
import java.util.HashMap;

import utils.Fraction;


public class FracInterpreter extends CalFractionBaseVisitor<Fraction> {

  HashMap<String, Fraction> symbolTable = new HashMap<>();

  @Override
  public Fraction visitMain(CalFractionParser.MainContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public Fraction visitStat(CalFractionParser.StatContext ctx) {
    if (ctx.print() != null) {
      return visit(ctx.print());
    } else {
      return visit(ctx.assign());
    }
  }

  @Override
  public Fraction visitPrint(CalFractionParser.PrintContext ctx) {
    Fraction f = visit(ctx.expr());
    System.out.println(f);
    return null;//or return f
  }

  @Override
  public Fraction visitAssign(CalFractionParser.AssignContext ctx) {
    Fraction expr = visit(ctx.expr());
    String id = ctx.ID().getText();
    symbolTable.put(id, expr);
    return expr;
  }

  @Override
  public Fraction visitAddSubExpr(CalFractionParser.AddSubExprContext ctx) {
    Fraction val1 = visit(ctx.expr(0));
    Fraction val2 = visit(ctx.expr(1));
    if (ctx.op.getText().equals("+")) {
       return Fraction.add(val1, val2);
    } else {
      return Fraction.subtract(val1, val2);
    }
  }

  @Override
  public Fraction visitPowerExpr(CalFractionParser.PowerExprContext ctx) {
    Fraction f = visit(ctx.expr());
    Integer value = Integer.parseInt(ctx.POWER().getText().substring(1));
    
    return Fraction.power(f, value);
  }

  @Override
  public Fraction visitReduceExpr(CalFractionParser.ReduceExprContext ctx) {
    Fraction f = visit(ctx.expr());
    return Fraction.reduce(f);
  }

  @Override
  public Fraction visitMultDivExpr(CalFractionParser.MultDivExprContext ctx) {
   Fraction val1 = visit(ctx.expr(0));
   Fraction val2 = visit(ctx.expr(1));
   if (ctx.op.getText().equals("*")) {
      return Fraction.multiply(val1, val2);
   } else {
     return Fraction.divide(val1, val2);
   }
 }
  

  @Override
  public Fraction visitParentExpr(CalFractionParser.ParentExprContext ctx) {
    return visit(ctx.expr());
  }

  @Override
  public Fraction visitFractionExpr(CalFractionParser.FractionExprContext ctx) {
    return new Fraction(ctx.FRACTION().getText());
  }

  @Override
  public Fraction visitIdExpr(CalFractionParser.IdExprContext ctx) {
    String key = ctx.ID().getText();
    if (!symbolTable.containsKey(key)) {
       System.err.println("ID " + key+ " is not valid!");
       System.exit(1);
    }
    return symbolTable.get(key);
  }

}