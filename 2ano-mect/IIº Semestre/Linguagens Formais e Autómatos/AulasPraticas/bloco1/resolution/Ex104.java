import java.util.*;
import java.io.*;

/**
 * Nome Jodionisio da Lucinda João Muachifi
 * Nº Mec: 97147
 * Cadeira de : Linguagens Formais e Autómatos(LFA) | 2º Ano-2º semestre
 * Curso: MIECT  
 * Marcço 2021
 */
public class Ex104 {

    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        Map<String, Integer> map = readFile("../numbers.txt");
        while(sc.hasNextLine()) {
            String line = sc.nextLine().replace('-', ' ');
            Scanner scf = new Scanner(line);
   
            for(boolean bool = true; scf.hasNext(); bool = false) {
               String str;
               String s = (str = scf.next()).toLowerCase();
               if (!bool) {
                  System.out.print(" ");
               }
   
               if (map.containsKey(s)) {
                  str = ((Integer)map.get(s)).toString();
               }
   
               System.out.print(str);
            }
   
            System.out.println();

            scf.close();
         }
        
    }
    public static Map<String, Integer> readFile(String fname) {
        
        HashMap<String,Integer> map = new HashMap<>();

        try {
            Scanner scfile = new Scanner(new File(fname));
            while (scfile.hasNextLine()) {
                String str;
                if ((str = scfile.nextLine().trim()).length() > 0) {
                    String line[];
                    if ((line = str.split(" - ")).length != 2) {
                        System.err.println("ERROR: syntax error in number file!");
                        System.exit(1);
                    }

                    String numbers = line[1].toLowerCase();
                    if (map.containsKey(numbers)) {
                       System.err.println("ERROR: repeated number \"" + numbers + "\" in number file!");
                       System.exit(1);
                    }
                    try {
                        map.put(numbers, Integer.parseInt(line[0]));
                     } catch (NumberFormatException e) {
                        System.err.println("ERROR: invalid number \"" + line[0] + "\" in number file!");
                        System.exit(1);
                     }
                }
            }
            scfile.close();
            
        } catch (IOException e) {
            System.err.println("ERROR: reading number file!");
            System.exit(2);
        }

        return map;

    }
    
}
