public class Execute extends HelloBaseVisitor<String> {

   @Override public String visitGreetings(HelloParser.GreetingsContext ctx) {
      String name = ctx.ID().getText();
      System.out.println("Olá " +  name);
      return null;
   }

   @Override public String visitBye(HelloParser.ByeContext ctx) {
      String name = ctx.ID().getText();
      System.out.println("Adeus " +  name);
      return null;
   }
}
