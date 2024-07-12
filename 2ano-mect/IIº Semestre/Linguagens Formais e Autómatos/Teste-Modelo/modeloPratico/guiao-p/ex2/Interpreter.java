import java.util.*;

public class Interpreter extends FracLangBaseVisitor<Fraction> {

  HashMap<String, Fraction> symbolTable = new HashMap<>();

  @Override
  public Fraction visitMain(FracLangParser.MainContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public Fraction visitStat(FracLangParser.StatContext ctx) {
    if (ctx.display() != null) {
      return visit(ctx.display());
    } else {
      return visit(ctx.assign());
    }
  }

  @Override
  public Fraction visitDisplay(FracLangParser.DisplayContext ctx) {
    Fraction f = visit(ctx.expr());
    System.out.println(f);
    return f; //or return null
  }

  @Override
  public Fraction visitAssign(FracLangParser.AssignContext ctx) {
    String id = ctx.ID().getText();
    Fraction f = visit(ctx.expr());
    symbolTable.put(id, f);
    return f;
  }

  @Override
  public Fraction visitUnaryExpr(FracLangParser.UnaryExprContext ctx) {
    Fraction f = visit(ctx.expr());
    if ("-".equals(ctx.op.getText())) {
      return Fraction.unaryOperator(f);
    } else {
      return f;
    }
  }

  @Override
  public Fraction visitAddSubExpr(FracLangParser.AddSubExprContext ctx) {
    Fraction v1 = visit(ctx.expr(0));
    Fraction v2 = visit(ctx.expr(1));
    if (ctx.op.getText().equals("+")) {
      return Fraction.addition(v1, v2);
    } else {
      return Fraction.subtract(v1, v2);
    }
  }

  @Override
  public Fraction visitReduceExpr(FracLangParser.ReduceExprContext ctx) {
    Fraction f = visit(ctx.expr());
    return Fraction.reduce(f);
  }

  @Override
  public Fraction visitReadExpr(FracLangParser.ReadExprContext ctx) {
    /*String s = ctx.STRING().getText();
    Scanner read = new Scanner(System.in);
    System.out.print(s.substring(1, s.length() - 1) + ": ");
    String input = read.nextLine();
    return null;*/
    String s = ctx.STRING().getText();
    Scanner read = new Scanner(System.in);
    System.out.print(s.substring(1, s.length() - 1) + ": ");
    String fraction = read.nextLine();
    try {
      String aux[] = fraction.split("/");
      return new Fraction(Integer.parseInt(aux[0]), Integer.parseInt(aux[1]));
    } catch (Exception e) {
      System.err.println("ERROR: invalid sintax (insert <number></><number>)");
     return null;
    }
    
  }

  @Override
  public Fraction visitMultDivExpr(FracLangParser.MultDivExprContext ctx) {
    Fraction v1 = visit(ctx.expr(0));
    Fraction v2 = visit(ctx.expr(1));
    if (ctx.op.getText().equals("*")) {
      return Fraction.multiply(v1, v2);
    } else {
      return Fraction.divide(v1, v2);
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
      System.err.println("ERROR: ID " + key + " is not valid!");
      System.exit(2);
    }
    return symbolTable.get(key);
  }
}
