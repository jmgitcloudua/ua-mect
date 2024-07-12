import java.util.*;
import java.util.stream.*;

public class VectorInterpreter extends VectorBaseVisitor<Object> {

  HashMap<String, Value> symbolTable = new HashMap<>();
  
  @Override
  public Object visitMain(VectorParser.MainContext ctx) {
    return visitChildren(ctx);
  }

  @Override
  public Object visitShowStat(VectorParser.ShowStatContext ctx) {
    System.out.println(visit(ctx.value()).toString());
   return visitChildren(ctx);
  }

  @Override
  public Object visitAssignStat(VectorParser.AssignStatContext ctx) {
    String var = ctx.ID().getText();
    Value val = (Value)visit(ctx.value());
    symbolTable.put(var, val);
    return visitChildren(ctx);
  }

  @Override
  public Object visitAddSubValue(VectorParser.AddSubValueContext ctx) {
    Value val1 = (Value) visit(ctx.v1);
    Value val2 = (Value) visit(ctx.v1);
  
    if (ctx.op.getText().equals("+")) {
         val1.add(val2);
    }
    return val1.sub(val2);
  }

  @Override
  public Object visitRealValue(VectorParser.RealValueContext ctx) {
   return new Real(Double.parseDouble(ctx.getText()));
  }

  @Override
  public Object visitVectorValue(VectorParser.VectorValueContext ctx) {
    return visit(ctx.vector());
  }

  @Override
  public Object visitIdValue(VectorParser.IdValueContext ctx) {
    String key =  ctx.ID().getText();
    if (!symbolTable.containsKey(key)) {
      System.out.println("ERROR: variable - " + key + " not found!");
      System.exit(1);
    }
   Value v = symbolTable.get(key);

   return v;
  }

  @Override
  public Object visitParentValue(VectorParser.ParentValueContext ctx) {
    return visit(ctx.value());
  }

  @Override
  public Object visitSignalValue(VectorParser.SignalValueContext ctx) {
   Value v = (Value) visit(ctx.value());
   if (ctx.op.getText().equals("-")) {
      v.invert();
   }
   return v;
  }

  @Override
  public Object visitVector(VectorParser.VectorContext ctx) {
 Vector v = new Vector();
 v.list = ctx.REAL().stream().map(x -> new Real(Double.parseDouble(x.getText()))).collect(Collectors.toList());
   return v;
  }
}
