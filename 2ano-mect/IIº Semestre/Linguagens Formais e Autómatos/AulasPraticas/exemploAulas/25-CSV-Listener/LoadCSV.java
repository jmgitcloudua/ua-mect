import java.io.FileInputStream;
import java.io.InputStream;
import java.util.*;
import org.antlr.v4.runtime.ANTLRInputStream;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;
import java.util.Scanner;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.tree.*;
import org.antlr.v4.runtime.CharStreams.*;

public class LoadCSV extends CSVBaseListener {

  public static final String EMPTY = "";
  /** Load a list of row maps that map field name to value */
  List<Map<String, String>> rows = new ArrayList<Map<String, String>>();
  /** List of column names */
  List<String> header;
  /** Build up a list of fields in current row */
  List<String> currentRowFieldValues;

  public void exitHdr(CSVParser.HdrContext ctx) {
    header = new ArrayList<String>();
    header.addAll(currentRowFieldValues);
  }

  public void enterRow(CSVParser.RowContext ctx) {
    currentRowFieldValues = new ArrayList<String>();
  }

  public void exitRow(CSVParser.RowContext ctx) {
    // If this is the header row, do nothing
    // if ( ctx.parent instanceof CSVParser.HdrContext ) return; OR:
    if (ctx.getParent().getRuleIndex() == CSVParser.RULE_hdr) return;
    // It's a data row
    Map<String, String> m = new LinkedHashMap<String, String>();
    int i = 0;
    for (String v : currentRowFieldValues) {
      m.put(header.get(i), v);
      i++;
    }
    rows.add(m);
  }

  public void exitString(CSVParser.StringContext ctx) {
    currentRowFieldValues.add(ctx.STRING().getText());
  }

  public void exitText(CSVParser.TextContext ctx) {
    currentRowFieldValues.add(ctx.TEXT().getText());
  }

  public void exitEmpty(CSVParser.EmptyContext ctx) {
    currentRowFieldValues.add(EMPTY);
  }

  public static void main(String[] args) throws Exception {
   
   Scanner sc = new Scanner(System.in);
   String lineText = null;
   if (sc.hasNextLine()) lineText = sc.nextLine();

    //String inputFile = null;
    if (args.length > 0) lineText = args[0];
    //InputStream is = System.in;  
    CharStream  is = CharStreams.fromString(lineText + "\n"); //new FileInputStream(inputFile);
    CSVLexer lexer = new CSVLexer(is);
    CommonTokenStream tokens = new CommonTokenStream(lexer);
    CSVParser parser = new CSVParser(tokens);
    parser.setBuildParseTree(true); // tell ANTLR to build a parse tree
    ParseTree tree = parser.file();

    ParseTreeWalker walker = new ParseTreeWalker();
    LoadCSV loader = new LoadCSV();
    walker.walk(loader, tree);
    System.out.println(loader.rows);
  }
}
