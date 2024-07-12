public class Fraction {

  private final int num;
  private final int den;

  public Fraction(int num, int den) {
    assert den >= 0 : "Denominator can not be zero";
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

  public int getNum() {
    return num;
  }

  public int getDen() {
    return den;
  }

  public static Fraction addition(Fraction f1, Fraction f2) {
    int num = f1.num * f2.den + f1.den * f2.num;
    int den = f1.den * f2.den;
    return new Fraction(num, den);
  }

  public static Fraction subtraction(Fraction f1, Fraction f2) {
    return Fraction.addition(f1, new Fraction((-1) * f2.num, f2.den));
  }

  public static Fraction multiply(Fraction f1, Fraction f2) {
    int num = f1.num * f2.num;
    int den = f1.den * f2.den;
    return new Fraction(num, den);
  }

  public static Fraction divide(Fraction f1, Fraction f2) {
    return Fraction.multiply(f1, new Fraction(f2.den, f2.num));
  }

  public static Fraction unaryOpt(Fraction f1) {
    return new Fraction((-1) * f1.num, 1);
  }

  public static int _gcd(int a, int b) {
    if (b == 0) {
      return a;
    }
    return _gcd(b, a % b);
  }

  public static Fraction reduce(Fraction f1) {
    int originalNum = f1.num;
    int originalDen = f1.den;
    int gcd = _gcd(originalNum, originalDen);
    return new Fraction(originalNum / gcd, originalDen / gcd);
  }
  public String toString(){
      StringBuilder builder = new StringBuilder();
      builder.append(num);
      if(den != 1 && num != 0){
        builder.append("/");
        builder.append(den);
      }
      return builder.toString();
  }
}
