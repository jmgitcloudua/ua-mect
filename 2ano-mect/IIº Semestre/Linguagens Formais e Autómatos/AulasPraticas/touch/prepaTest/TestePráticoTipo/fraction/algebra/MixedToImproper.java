//package algebra;

public class MixedToImproper {

    private final int numerator;
    private final int denominator;
    private final int whole_number;

    public MixedToImproper(int whole_num, int num, int denom) {
        whole_number = whole_num;
        numerator = num;
        denominator = denom;
    }

    public int doConvert() {
        return (whole_number * denominator) + numerator;
    }
}