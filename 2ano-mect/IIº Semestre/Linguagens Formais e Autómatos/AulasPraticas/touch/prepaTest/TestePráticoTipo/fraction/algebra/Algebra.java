//package algebra;

import java.util.List;

public class Algebra {

    public static void main(String[] args) {

        int numerator;
        int denominator;
        int whole_number;

        System.out.println("Welcome to our demonstration sequels");
        System.out.println("Hope you enjoy (and follow) the lessons.");
        System.out.println("");

        /*
        * Convert fractions from Mixed to Improper
         */
        whole_number = 3;
        numerator = 1;
        denominator = 3;

        System.out.println("Converting from Mixed to Improper the fraction:");
        // Print as fraction
        System.out.printf("%55d%n", numerator);
        System.out.printf("%54d%s%n", whole_number, "?");
        System.out.printf("%55d%n", denominator);

        // use the MixedToImproper class
        MixedToImproper mix_imp = new MixedToImproper(whole_number, numerator, denominator);
        numerator = mix_imp.doConvert();

        System.out.println();

        System.out.printf("%52d%n", numerator);
        System.out.printf("%51s%n", "Answer =  ?");
        System.out.printf("%52d%n", denominator);

        System.out.println("\n\n");
        
    }

}