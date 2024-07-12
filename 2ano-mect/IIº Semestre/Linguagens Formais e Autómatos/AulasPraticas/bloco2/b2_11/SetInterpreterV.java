import java.util.*;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.TerminalNode;

public class SetInterpreterV extends SetCalcBaseVisitor<Set<String>> {

  private Map<String, Set<String>> symbolTable = new HashMap<>();

  @Override
  public Set<String> visitProgram(SetCalcParser.ProgramContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public Set<String> visitLine(SetCalcParser.LineContext ctx) {
    Set<String> result = visit(ctx.expr());
    String str = result.toString();
    str = "{" + str.substring(1, str.length() - 1).replaceAll(" ", "") + "}";
    System.out.println("Result: " + str + "\n");
    return result;
  }

  @Override
  public Set<String> visitExprParentesis(
    SetCalcParser.ExprParentesisContext ctx
  ) {
    return visit(ctx.expr());
  }

  @Override
  public Set<String> visitExprDiference(
    SetCalcParser.ExprDiferenceContext ctx
  ) {
    Set<String> set = new HashSet<>();
    set.addAll(visit(ctx.expr(0)));
    set.removeAll(visit(ctx.expr(1))); // difference
    return set;
  }

  @Override
  public Set<String> visitExprUnion(SetCalcParser.ExprUnionContext ctx) {
    Set<String> set = new HashSet<>();
    ctx.expr().forEach(expr -> set.addAll(visit(expr)));
    return set;
  }

  @Override
  public Set<String> visitExprIntersection(
    SetCalcParser.ExprIntersectionContext ctx
  ) {
    Set<String> set = new HashSet<>();
    set.addAll(visit(ctx.expr(0)));
    set.retainAll(visit(ctx.expr(1))); //intersection
    return set;
  }

  @Override
  public Set<String> visitExprAssignment(
    SetCalcParser.ExprAssignmentContext ctx
  ) {
    return visit(ctx.assignment());
  }

  @Override
  public Set<String> visitExprID(SetCalcParser.ExprIDContext ctx) {
    String key = ctx.ID().getText();
    if (!symbolTable.containsKey(key)) {
      System.err.println("ID " + key + " not valid!");
      System.exit(1);
    }
    return symbolTable.get(key);
  }

  @Override
  public Set<String> visitExprSet(SetCalcParser.ExprSetContext ctx) {
    return visit(ctx.set());
  }

  @Override
  public Set<String> visitAssignment(SetCalcParser.AssignmentContext ctx) {
    Set<String> result = visit(ctx.expr());
    symbolTable.put(ctx.ID().getText(), result);
    return result;
  }

  @Override
  public Set<String> visitSet(SetCalcParser.SetContext ctx) {
    Set<String> set = new HashSet<>();

    List<TerminalNode> nums = ctx.NUM();
    if (nums.size() != 0) {
      nums.forEach(num -> set.add(num.getText()));
    } else {
      ctx.WORD().forEach(word -> set.add(word.getText()));
    }

    System.out.println("set: " + set);
    return set;
  }
}
