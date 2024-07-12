import java.io.*;
import java.util.Map;
import java.util.Scanner;
import org.antlr.v4.misc.OrderedHashMap;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class PropertyFileLoaderV extends PropertyFileBaseVisitor<Void>{

   @Override public Void visitFile(PropertyFileParser.FileContext ctx) {
      return visitChildren(ctx);
   }

   @Override public Void visitProp(PropertyFileParser.PropContext ctx) {
      ​
      Map​<​String​,​String​> props = ​new​ OrderedHashMap<​String​, ​String​>();
​ 	    
   public​ ​Void​ visitProp(PropertyFileParser.PropContext ctx) {
   ​ 	
           ​String id = ctx.ID().getText(); ​
   ​ 	
           ​String​ value = ctx.STRING().getText();
   ​ 	
           props.put(id, value);
   ​ 	
           ​return​ null; ​// Java says must return something even when Void​
       }

    ​
   }
}
