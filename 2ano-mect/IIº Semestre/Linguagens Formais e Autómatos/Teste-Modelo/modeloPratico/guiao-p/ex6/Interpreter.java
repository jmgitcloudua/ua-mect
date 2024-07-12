import java.util.*;

public class Interpreter extends FracLangBaseVisitor<Fraction> {

  HashMap<String, Fraction> symbolTable = new HashMap<>();

  @Override
  public Fraction visitMain(FracLangParser.MainContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public Fraction visitStat(FracLangParser.StatContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public Fraction visitDisplay(FracLangParser.DisplayContext ctx) {
    Fraction res = visit(ctx.expr());
    if (res != null) {
      System.out.println(res);
    }
    return null;
  }

  @Override
  public Fraction visitAssign(FracLangParser.AssignContext ctx) {
    String key = ctx.ID().getText();
    Fraction value = visit(ctx.expr());
    if (value == null) {
      System.err.println("ERROR: Valaue" + value + " can not be null");
      System.exit(1);
    }
    return symbolTable.put(key, value);
  }

  @Override
  public Fraction visitUnaryExpr(FracLangParser.UnaryExprContext ctx) {
    Fraction res = visit(ctx.expr());
    if ("-".equals(ctx.op.getText())) {
      return Fraction.unaryOpt(res);
    }
    return res;
  }

  @Override
  public Fraction visitAddSubExpr(FracLangParser.AddSubExprContext ctx) {
    Fraction f1 = visit(ctx.expr(0));
    Fraction f2 = visit(ctx.expr(1));
    if (ctx.op.getText().equals("+")) {
      return Fraction.add(f1, f2);
    } else {
      return Fraction.sub(f1, f2);
    }
  }

  @Override
  public Fraction visitReduceExpr(FracLangParser.ReduceExprContext ctx) {
    Fraction res = visit(ctx.expr());
    return Fraction.reduce(res);
  }

  @Override
  public Fraction visitReadExpr(FracLangParser.ReadExprContext ctx) {
    String s = ctx.STRING().getText();
    System.out.print(s.substring(1, s.length() - 1) + ": ");
    Scanner sc = new Scanner(System.in);
    String f = sc.nextLine();
    try {
      String aux[] = f.split("/");
      return new Fraction(Integer.parseInt(aux[0]), Integer.parseInt(aux[1]));
    } catch (Exception e) {
      System.err.println("ERROR: Invalid Syntax (insert <num>/<num>)");
      return null;
    }
  }

  @Override
  public Fraction visitMultDivExpr(FracLangParser.MultDivExprContext ctx) {
    Fraction f1 = visit(ctx.expr(0));
    Fraction f2 = visit(ctx.expr(1));
    if (ctx.op.getText().equals("*")) {
      return Fraction.mult(f1, f2);
    } else {
      return Fraction.div(f1, f2);
    }
  }

  @Override
  public Fraction visitParentExpr(FracLangParser.ParentExprContext ctx) {
    return visit(ctx.expr());
  }

  @Override
  public Fraction visitFractionExpr(FracLangParser.FractionExprContext ctx) {
    return new Fraction(ctx.FRACTION().getText());
  }

  @Override
  public Fraction visitIdExpr(FracLangParser.IdExprContext ctx) {
    String key = ctx.ID().getText();
    if (!symbolTable.containsKey(key)) {
      System.err.println("ERROR: ID " + key + " not found!");
      System.exit(1);
    }
    return symbolTable.get(key);
  }
}
