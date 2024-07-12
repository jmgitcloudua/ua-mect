import java.util.*;

public class StrLangInterpreter extends StrLangBaseVisitor<String> {

  HashMap<String, String> symbolTable = new HashMap<>();
  private static Scanner read = new Scanner(System.in);

  private String parseString(String s){
    return s.replace("\"", "");
 }
  @Override
  public String visitMain(StrLangParser.MainContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public String visitStatement(StrLangParser.StatementContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public String visitPrint(StrLangParser.PrintContext ctx) {
    if (ctx.STRING() != null) {
      System.out.println(parseString(ctx.STRING().getText()));
    } else if (ctx.VAR() != null) {
      if (symbolTable.containsKey(ctx.VAR().getText())) {
        System.out.println(symbolTable.get(ctx.VAR().getText()));
      } else {
        System.err.println(
          "ERROR: variable" + ctx.VAR().getText() + " does not exist"
        );
        System.exit(1);
      }
    } else if (ctx.op() != null) {
      System.out.println(visit(ctx.op()));
    }
    return null;
  }

  @Override
  public String visitDeclarationString(
    StrLangParser.DeclarationStringContext ctx
  ) {
    symbolTable.put(ctx.VAR().getText(), parseString(ctx.STRING().getText()));
    return null;
  }

  @Override
  public String visitDeclarationInput(
    StrLangParser.DeclarationInputContext ctx
  ) {
    symbolTable.put(ctx.VAR().getText(), visit(ctx.input()));
    return null;
  }

  @Override
  public String visitInput(StrLangParser.InputContext ctx) {
    System.out.println(parseString(ctx.STRING().getText()));
    String result = read.nextLine();

    return result;
  }

  @Override
  public String visitOpAdd(StrLangParser.OpAddContext ctx) {
    String textA = visit(ctx.op(0));
    String textB = visit(ctx.op(1));

    return textA.concat(textB);
  }

  @Override
  public String visitOpString(StrLangParser.OpStringContext ctx) {
    return parseString(ctx.STRING().getText());
  }

  @Override
  public String visitOpReplace(StrLangParser.OpReplaceContext ctx) {
    String textA = visit(ctx.op(0));
    String textB = visit(ctx.op(1));
    String textC = visit(ctx.op(2));
    return textA.replaceAll(textB, textC);
  }

  @Override
  public String visitOpVar(StrLangParser.OpVarContext ctx) {
    if (symbolTable.containsKey(ctx.VAR().getText())) {
      return symbolTable.get(ctx.VAR().getText());
    }
    System.err.println("ERROR: variable " + ctx.VAR().getText() + " does not exist");
    System.exit(0);
    
    return null;
  }
}
