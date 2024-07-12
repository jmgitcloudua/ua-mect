import java.io.*;
import java.io.FileInputStream;
import java.io.InputStream;
import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.ParserRuleContext;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.CharStreams.*;
import java.util.*;

public class RowsMain {

  public static void main(String[] args) throws IOException {
    Scanner sc = new Scanner(System.in);
    String lineText = null;
    if (sc.hasNextLine()) lineText = sc.nextLine();
    CharStream input = CharStreams.fromString(lineText + "\n");
    //ANTLRInputStream input = new ANTLRInputStream(System.in);
    RowsLexer lexer = new RowsLexer(input);
    CommonTokenStream tokens = new CommonTokenStream(lexer);
    int col = Integer.valueOf(args[0]);
    RowsParser parser = new RowsParser(tokens, col); // pass column number!
    parser.setBuildParseTree(false); // don't waste time bulding a tree
    parser.file(); // parse
  }
}
