import java.io.*;
import java.util.*;
import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.tree.ErrorNode;
import org.antlr.v4.runtime.tree.TerminalNode;

public class NumbersMaping extends NumbersBaseListener {

  public Map<String, Integer> map = new HashMap<>();

  @Override
  public void exitFile(NumbersParser.FileContext ctx) {}

  @Override
  public void exitLine(NumbersParser.LineContext ctx) {
    String key = ctx.Word().getText();
    Integer value = Integer.parseInt(ctx.Number().getText());

    if (exists(key)) {
      System.err.println("ERROR: Key " + key + " is repeated!");
      System.exit(1);
    }

    map.put(key, value);
   
  }

  // auxiliary functions
  public boolean exists(String key) {
    assert key != null;
    return map.containsKey(key);
  }

  public Integer value(String key) {
    assert key != null;
    assert exists(key);
    return map.get(key);
  }
}
