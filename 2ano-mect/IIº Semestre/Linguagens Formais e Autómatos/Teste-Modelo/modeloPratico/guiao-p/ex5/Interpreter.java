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
    String s = visit(ctx.expr());
    System.out.println(s);
    return s;
  }

  @Override
  public String visitAssign(StrLangParser.AssignContext ctx) {
    String id = ctx.ID().getText();
    String resExpr = visit(ctx.expr());
    symbolTable.put(id, resExpr);
    return resExpr;
  }

  @Override
  public String visitStringExpr(StrLangParser.StringExprContext ctx) {
    String s = ctx.STRING().getText();
    return s.substring(1, s.length() - 1);
  }

  @Override
  public String visitReplaceExpr(StrLangParser.ReplaceExprContext ctx) {
    String strA = visit(ctx.expr(0));
    String strB = visit(ctx.expr(1));
    String strC = visit(ctx.expr(2));
    return strA.replaceAll(strB, strC);
  }

  @Override
  public String visitInputExpr(StrLangParser.InputExprContext ctx) {
    return visit(ctx.input());
  }

  @Override
  public String visitTrimExpr(StrLangParser.TrimExprContext ctx) {
    String s = visit(ctx.expr());
    return s.trim();
  }

  @Override
  public String visitParentExpr(StrLangParser.ParentExprContext ctx) {
    return visit(ctx.expr());
  }

  @Override
  public String visitRemoveExpr(StrLangParser.RemoveExprContext ctx) {
    String strA = visit(ctx.expr(0));
    String strB = visit(ctx.expr(1));
    return strA.replaceAll(strB, "");
  }

  @Override
  public String visitIdExpr(StrLangParser.IdExprContext ctx) {
    String key = ctx.ID().getText();
    if (!symbolTable.containsKey(key)) {
      System.err.println("ERROR: ID" + key + " is not valid");
      System.exit(1);
    }
    return symbolTable.get(key);
  }

  @Override
  public String visitConcatExpr(StrLangParser.ConcatExprContext ctx) {
    String strA = visit(ctx.expr(0));
    String strB = visit(ctx.expr(1));
    return strA.concat(strB);
  }

  @Override
  public String visitInput(StrLangParser.InputContext ctx) {
    String s = ctx.STRING().getText();
    System.out.print(s.substring(1, s.length() - 1));
    Scanner sc = new Scanner(System.in);
    String input = sc.nextLine();
    return input;
  }
}
