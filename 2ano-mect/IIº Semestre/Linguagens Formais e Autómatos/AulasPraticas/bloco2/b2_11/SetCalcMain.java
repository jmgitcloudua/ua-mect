import java.util.Scanner;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;

public class SetCalcMain {
   public static void main(String[] args) {
      try {
         Scanner sc = new Scanner(System.in);
         String lineText = null;
         int numLine = 1;
         if (sc.hasNextLine())
            lineText = sc.nextLine();
         SetCalcParser parser = new SetCalcParser(null);
         // replace error listener:
         //parser.removeErrorListeners(); // remove ConsoleErrorListener
         //parser.addErrorListener(new ErrorHandlingListener());
         SetInterpreterV visitor0 = new SetInterpreterV();
         while(lineText != null) {
            // create a CharStream that reads from standard input:
            CharStream input = CharStreams.fromString(lineText + "\n");
            // create a lexer that feeds off of input CharStream:
            SetCalcLexer lexer = new SetCalcLexer(input);
            lexer.setLine(numLine);
            lexer.setCharPositionInLine(0);
            // create a buffer of tokens pulled from the lexer:
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            // create a parser that feeds off the tokens buffer:
            parser.setInputStream(tokens);
            // begin parsing at program rule:
            ParseTree tree = parser.program();
            if (parser.getNumberOfSyntaxErrors() == 0) {
               // print LISP-style tree:
               // System.out.println(tree.toStringTree(parser));
               visitor0.visit(tree);
            }
            if (sc.hasNextLine())
               lineText = sc.nextLine();
            else
               lineText = null;
            numLine++;
         }
      }
      catch(RecognitionException e) {
         e.printStackTrace();
         System.exit(1);
      }
   }
}
