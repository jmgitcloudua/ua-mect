import java.io.*;
import java.util.Scanner;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;


public class FracLangMain {

   private static File file = null;
   public static void main(String[] args) throws IOException {
      for (String filename : args) {
         file = new File(filename);
         if (!file.exists()) {
            System.err.println("ERROR: File" + filename + " does not exits!");
            System.exit(1);
         }
         if (file.isDirectory()) {
            System.err.println("ERROR: File" + filename + " is disrectory");
            System.exit(1);
         }
         if (!file.canRead()) {
            System.err.println("ERROR: File" + filename + " can not read!");
            System.exit(1);
         }
      }
      try {
         Scanner sc = new Scanner(file);
         String lineText = null;
         int numLine = 1;
         if (sc.hasNextLine())
            lineText = sc.nextLine();
         FracLangParser parser = new FracLangParser(null);
         // replace error listener:
         //parser.removeErrorListeners(); // remove ConsoleErrorListener
         //parser.addErrorListener(new ErrorHandlingListener());
         Interpreter visitor0 = new Interpreter();
         while(lineText != null) {
            // create a CharStream that reads from standard input:
            CharStream input = CharStreams.fromString(lineText + "\n");
            // create a lexer that feeds off of input CharStream:
            FracLangLexer lexer = new FracLangLexer(input);
            lexer.setLine(numLine);
            lexer.setCharPositionInLine(0);
            // create a buffer of tokens pulled from the lexer:
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            // create a parser that feeds off the tokens buffer:
            parser.setInputStream(tokens);
            // begin parsing at main rule:
            ParseTree tree = parser.main();
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
