import java.util.*;

public class StrLangInterpreter extends StrLangBaseVisitor<String> {

  private static Scanner read = new Scanner(System.in);
  HashMap<String, String> symbolTable = new HashMap<>();

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
    String result = visit(ctx.text());
    System.out.println(result);
    return result;
  }

  @Override
  public String visitAssignment(StrLangParser.AssignmentContext ctx) {
    String result = visit(ctx.text());
    symbolTable.put(ctx.ID().getText(), result);
    return result;
  }

  @Override
  public String visitTextID(StrLangParser.TextIDContext ctx) {
    String key = ctx.ID().getText();
    if (!symbolTable.containsKey(key)) {
      System.err.println("ERROR: Variable \"" + key + "\" not defined!");
      System.exit(1);
    }
    return symbolTable.get(key);
  }

  @Override
  public String visitTextInput(StrLangParser.TextInputContext ctx) {
    return visit(ctx.input());
  }

  @Override
  public String visitTextParenthesis(StrLangParser.TextParenthesisContext ctx) {
    return visit(ctx.text());
  }

  @Override
  public String visitTextConcat(StrLangParser.TextConcatContext ctx) {
    String textA = visit(ctx.text(0));
    String textB = visit(ctx.text(1));

    return textA.concat(textB);
  }

  @Override
  public String visitTextReplace(StrLangParser.TextReplaceContext ctx) {
    String textA = visit(ctx.text(0));
    String textB = visit(ctx.text(1));
    String textC = visit(ctx.text(2));

    return textA.replaceAll(textB, textC);
  }

  @Override
  public String visitTextString(StrLangParser.TextStringContext ctx) {
    String text = ctx.STRING().getText();
    return text.substring(1,text.length()-1);//ommit the initial quote marks
  }

  @Override
  public String visitInput(StrLangParser.InputContext ctx) {
    String prompt = ctx.STRING().getText();
    System.out.println(prompt.substring(1,prompt.length()-1));//ommit the initial quote marks
   String text = read.nextLine();

   return text;
   }
}
