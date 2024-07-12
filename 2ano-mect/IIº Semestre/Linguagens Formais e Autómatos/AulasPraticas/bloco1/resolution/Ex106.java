import java.util.*;
import java.io.*;

/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Linguagens Formais e Autómatos(LFA) | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
public class Ex106 {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.err.println("Usage: java -ea Ex106 <dictionary-file> <input-file> ...");
            System.exit(1);
         }
   
         Map<String, String> map = readFile(args[0]);
   
         for(int i = 1; i < args.length; i++) {
            try {
               File file = new File(args[i]);
               Scanner scf = new Scanner(file);
   
               while(scf.hasNextLine()) {
                  String line = scf.nextLine();
                  System.out.print("\"" + line + "\" -> \"");
                  String[] split = line.split("\\s+");
   
                  for(int j = 0; j < split.length; j++) {
                     if (j > 0) {
                        System.out.print(" ");
                     }
   
                     System.out.print(translation(map, split[j], new String[0]));
                  }
   
                  System.out.println("\"");
               }
   
               scf.close();
            } catch (IOException s) {
               System.err.println("ERROR: reading input file \"" + args[i] + "\"!");
               System.exit(1);
            }
         }
        
    }

    public static Map<String,String> readFile(String fname) {
        HashMap<String,String> map = new HashMap<>();
  
        try {
           File file = new File(fname);
           Scanner scf = new Scanner(file);
  
           while(true) {
              String[] strLine;
              do {
                 if (!scf.hasNextLine()) {
                    scf.close();
                    return map;
                 }
              } while((strLine = scf.nextLine().split("\\s+")).length <= 0);
  
              if (strLine.length < 2) {
                 System.err.println("ERRO: linha mal formatada!");
                 System.exit(1);
              }
  
              if (map.containsKey(strLine[0])) {
                 System.err.println("ERRO: palavra já existe!");
                 System.exit(1);
              }
  
              String str = strLine[1];
  
              for(int i = 2; i < strLine.length; i++) {
                 str = str + " " + strLine[i];
              }
              map.put(strLine[0], str);
           }
        } catch (IOException e) {
           System.err.println("ERROR: reading dictionary file!");
           System.exit(1);
           
           return map;
        }
     }


    public static String translation(Map<String,String> map, String str, String[] array) {
        String resultStr = "";
        String s;
        if ((s = map.get(str)) != null) {
           String[] strv = s.split("\\s+");
  
           for(int i = 0; i < strv.length; i++) {
              String str2 = str;
              String[] arr = array;
              boolean bool = false;
  
              for(int j = 0; !bool && j < arr.length; j++) {
                 bool = str2.equals(arr[j]);
              }
  
              if (bool) {
                 System.err.println("ERRO: dicionário com recursão infinita!");
                 System.exit(1);
              }
  
              if (resultStr.length() > 0) {
                 resultStr = resultStr + " ";
              }
  
              arr = new String[array.length + 1];
              System.arraycopy(array, 0, arr, 0, array.length);
              arr[array.length] = str;
              resultStr = resultStr + translation(map, strv[i], arr);
           }
        } else {
           resultStr = str;
        }
  
        return resultStr;
     }
    
}
