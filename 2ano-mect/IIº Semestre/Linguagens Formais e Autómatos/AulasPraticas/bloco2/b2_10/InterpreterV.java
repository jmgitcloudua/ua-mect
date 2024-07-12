import java.util.*;

public class InterpreterV extends QuizBaseVisitor<String> {

  @Override
  public String visitFile(QuizParser.FileContext ctx) {
    String s = visit(ctx.question());
    if (s != null) {
      System.out.println(s);
    }

    return null;
  }

  @Override
  public String visitQuestion(QuizParser.QuestionContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public String visitAnswer(QuizParser.AnswerContext ctx) {
    return visitChildren(ctx);
  }
}
