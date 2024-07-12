public class Fraction {

  private final int num;
  private final int den;

  public Fraction(int num, int den) {
    assert den >= 0 : "denominator can not be zero";
    this.num = num;
    this.den = den;
  }

  public Fraction(String s) {
    int p = s.indexOf('/');
    if (p == -1) {
      num = Integer.valueOf(s);
      den = 1;
    } else {
      num = Integer.valueOf(s.substring(0, p));
      den = Integer.valueOf(s.substring(p + 1));
    }
  }

  private int getNum() {
    return num;
  }

  private int getDen() {
    return den;
  }

  public static Fraction add(Fraction f1, Fraction f2) {
    int num = f1.num * f2.den + f1.den * f2.num;
    int den = f1.den * f2.den;
    return new Fraction(num, den);
  }

  public static Fraction sub(Fraction f1, Fraction f2) {
    return Fraction.add(f1, new Fraction((-1) * f2.num, f2.den));
  }

  public static Fraction mult(Fraction f1, Fraction f2) {
    int num = f1.num * f2.num;
    int den = f1.den * f2.den;
    return new Fraction(num, den);
  }
  public static Fraction div(Fraction f1, Fraction f2){
    return Fraction.mult(f1, new Fraction(f2.den, f2.num));
  }
  public static Fraction unaryOpt(Fraction f){
      int num = f.num;
    return new Fraction((-1)*num,1);
  }
  public static int _gcd(int a, int b){
        if (b == 0) {
            return a;
        }
        return _gcd(b, a%b);
  }
  public static Fraction reduce(Fraction f){
      int a = f.num;
      int b = f.den;
      int gcd = _gcd(a, b);
      return new Fraction(a/gcd, b/gcd);
  }
  @Override public String toString(){
      StringBuilder builder = new StringBuilder();
      builder.append(num);
      if (den != 1 && num != 0) {
          builder.append("/");
          builder.append(den);
      }
      return builder.toString();
  }
}
