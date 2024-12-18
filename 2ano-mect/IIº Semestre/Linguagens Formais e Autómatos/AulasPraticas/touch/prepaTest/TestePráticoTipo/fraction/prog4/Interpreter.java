import java.util.*;
import java.util.Scanner;

public class Interpreter extends CalFractionBaseVisitor<Fraction> {

		HashMap<String, Fraction> map = new HashMap<>();
		

   @Override public Fraction visitMain(CalFractionParser.MainContext ctx) {
      return visitChildren(ctx);
   }

   @Override public Fraction visitStat(CalFractionParser.StatContext ctx) {
      if(ctx.print() != null){
	return visit(ctx.print());
	}else{
	return visit(ctx.assign());
	}
   }

   @Override public Fraction visitAssign(CalFractionParser.AssignContext ctx) {
      Fraction f = visit(ctx.expr());
     String id = ctx.ID().getText();
	map.put(id,f);
	return f;
   }

   @Override public Fraction visitPrint(CalFractionParser.PrintContext ctx) {
	Fraction f = visit(ctx.expr());
	System.out.println(f);     
 	return f;
   }
    /*@Override public Fraction visitRead(CalFractionParser.ReadContext ctx) {
	return visit(ctx.read());
   }*/
    @Override public Fraction visitReadExpr(CalFractionParser.ReadExprContext ctx) {
      Scanner read = new Scanner(System.in);
      System.out.print(ctx.READ().getText()+": ");
      String fraction = read.next();
      try{
         String aux[] = fraction.split("/");
         return new Fraction(Integer.parseInt(aux[0]), Integer.parseInt(aux[1]));
     }
      catch(NumberFormatException | ArrayIndexOutOfBoundsException e) {
         System.err.println("ERROR: invalid sintax (insert <number></><number>)");
         return null;
      }
   }

   @Override public Fraction visitAddSubExpr(CalFractionParser.AddSubExprContext ctx) {
      Fraction val1 = visit(ctx.e1);
      Fraction val2 = visit(ctx.e2);
 	if(ctx.op.getText().equals("+")){
	return Fraction.add(val1, val2);
	}else{
	return Fraction.subtract(val1, val2);
	}
   }

   @Override public Fraction visitPowerExpr(CalFractionParser.PowerExprContext ctx) {
      Fraction f = visit(ctx.expr());
     Integer exp =Integer.parseInt(ctx.POWER().getText().substring(1));
	return Fraction.power(f,exp);
   }

   @Override public Fraction visitReduceExpr(CalFractionParser.ReduceExprContext ctx) {
      Fraction f = visit(ctx.expr());
	return Fraction.reduce(f);
   }

   @Override public Fraction visitMultDivExpr(CalFractionParser.MultDivExprContext ctx) {
      Fraction val1 = visit(ctx.e1);
      Fraction val2 = visit(ctx.e2);
        if(ctx.op.getText().equals("*")){
        return Fraction.multiply(val1, val2);
        }else{ 
        return Fraction.divide(val1, val2);
        }

   }

   @Override public Fraction visitParentExpr(CalFractionParser.ParentExprContext ctx) {
      return visit(ctx.expr());
   }

   @Override public Fraction visitFractionExpr(CalFractionParser.FractionExprContext ctx) {
      return new Fraction(ctx.FRACTION().getText());
   }

   @Override public Fraction visitIdExpr(CalFractionParser.IdExprContext ctx) {
      String key = ctx.ID().getText();
	if(!map.containsKey(key)){
		System.err.println("ID " + key + " is not validd!");
		System.exit(1);
	}
	return map.get(key);
   }
}
