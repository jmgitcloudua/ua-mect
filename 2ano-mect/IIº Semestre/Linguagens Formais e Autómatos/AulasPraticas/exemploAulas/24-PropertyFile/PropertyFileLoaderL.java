import java.io.*;
import java.util.Map;
import java.util.Scanner;
import org.antlr.v4.misc.OrderedHashMap;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class PropertyFileLoaderL extends PropertyFileBaseListener {

  Map<String, String> props = new OrderedHashMap<String, String>();

  public void exitFile(PropertyFileParser.FileContext ctx) {
    String s = props.get(ctx.prop());
    if (s != null) {
      System.out.println("[Listener: ] " + s);
    }
  }

  public void exitProp(PropertyFileParser.PropContext ctx) {
    String id = ctx.ID().getText(); // prop : ID '=' STRING '\n' ;
    String value = ctx.STRING().getText();
    props.put(id, value);
  }
}
