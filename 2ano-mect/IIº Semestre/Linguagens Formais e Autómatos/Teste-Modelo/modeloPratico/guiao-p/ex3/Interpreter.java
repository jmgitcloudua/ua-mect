import java.util.*;

public class Interpreter extends StrLangBaseVisitor<String> {

  HashMap<String, String> symbolTable = new HashMap<>();

  @Override
  public String visitMain(StrLangParser.MainContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public String visitStat(StrLangParser.StatContext ctx) {
    if (ctx.print() != null) {
      return visit(ctx.print());
    } else {
      return visit(ctx.assign());
    }
  }

  @Override
  public String visitPrint(StrLangParser.PrintContext ctx) {
    String print = visit(ctx.expr());
    System.out.println(print);
    return print; //or return null
  }

  @Override
  public String visitAssign(StrLangParser.AssignContext ctx) {
    String id = ctx.ID().getText();
    String expr = visit(ctx.expr());
    symbolTable.put(id, expr);
    return expr;
  }

  @Override
  public String visitStringExpr(StrLangParser.StringExprContext ctx) {
    String str = ctx.STRING().getText();
    return str.substring(1, str.length() - 1);
  }

  @Override
  public String visitReplaceExpr(StrLangParser.ReplaceExprContext ctx) {
    String exprA= visit(ctx.expr(0));
    String exprB = visit(ctx.expr(1));
    String exprC = visit(ctx.expr(2));
    return exprA.replaceAll(exprB, exprC);
  }

  @Override
  public String visitInputExpr(StrLangParser.InputExprContext ctx) {
    return visit(ctx.input());
  }

  @Override
  public String visitTrimExpr(StrLangParser.TrimExprContext ctx) {
    String str = visit(ctx.expr());
    return str.trim();
  }

  @Override
  public String visitParentExpr(StrLangParser.ParentExprContext ctx) {
    return visit(ctx.expr());
  }

  @Override
  public String visitRemoveExpr(StrLangParser.RemoveExprContext ctx) {
    String exprA= visit(ctx.expr(0));
    String exprB = visit(ctx.expr(1));

    return exprA.replaceAll(exprB, "");
  }

  @Override
  public String visitIdExpr(StrLangParser.IdExprContext ctx) {
    String key = ctx.ID().getText();
    if (!symbolTable.containsKey(key)) {
      System.err.println("ERROR: ID " + key + " is invalid!");
      System.exit(1);
    }
    return symbolTable.get(key);
  }

  @Override
  public String visitConcatExpr(StrLangParser.ConcatExprContext ctx) {
    String exprA= visit(ctx.expr(0));
    String exprB = visit(ctx.expr(1));

    return exprA.concat(exprB);
  }

  @Override
  public String visitInput(StrLangParser.InputContext ctx) {
    Scanner sc = new Scanner(System.in);
    String str = ctx.STRING().getText();
    System.out.print(str.substring(1, str.length() - 1));
    String input = sc.nextLine();
    return input;
  }
}
