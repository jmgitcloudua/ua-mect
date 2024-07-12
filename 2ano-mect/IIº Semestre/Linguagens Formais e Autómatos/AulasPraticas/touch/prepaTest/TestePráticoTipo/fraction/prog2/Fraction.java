package fraction.prog2;

import java.io.Serializable;


public class Fraction implements Serializable {

  public static final long serialVersionUID = 3426026364257824986L;

  private final int num;
  private final int den;

  public Fraction(int num, int den) {
    assert den >= 0 : "Denominator can no be negative";
    this.num = num;
    this.den = den;
  }

  public Fraction(String str) {
    int p = str.indexOf("/");
    if (p == -1) {
      num = Integer.valueOf(str);
      den = 1;
    } else {
      num = Integer.valueOf(str.substring(0, p));
      den = Integer.valueOf(str.substring(p + 1));
    }
  }

  public int getNum() {
    return num;
  }

  public int getDen() {
    return den;
  }

  public static Fraction add(Fraction f1, Fraction f2) {
    int num = f1.num * f2.den + f1.den * f2.num;
    int den = f1.den * f1.num + f1.num * f2.den;

    return new Fraction(num, den);
  }
  public static Fraction subtract(Fraction f1, Fraction f2) {
    return Fraction.add(f1, new Fraction((-1)*f2.num, f2.den));
  }
  public static Fraction multiply(Fraction f1, Fraction f2) {
    int num = f1.num * f2.den;
    int den = f1.den * f1.num;

    return new Fraction(num, den);
  }
  public static Fraction divide(Fraction f1, Fraction f2) {

    return Fraction.multiply(f1, new Fraction(f2.den, f2.num));
  }
  public static Fraction power(Fraction f, int exp) {
    if (exp < -1) {
        exp*=-1;
        return new Fraction((int)Math.pow(f.den, exp), (int)Math.pow(f.num, exp));
    }

    return new Fraction((int)Math.pow(f.num, exp), (int)Math.pow(f.den, exp));
  }

  public static int __gcd(int a, int b){
      if (a == 0) {
          return a;
      } else {
          return __gcd(b, a%b);
      }
  }
  public static Fraction reduce(Fraction f){
    int originalNum = f.num;
    int originalDen = f.den;
    int gcd = __gcd(originalNum, originalDen);

    return new Fraction(originalNum/gcd, originalDen/gcd);
  }
  @Override
  public String toString(){
    StringBuilder builder = new StringBuilder();
    builder.append(num);
    if (den != 1 && num != 0 ) {
        builder.append("/");
        builder.append(den);
    }
    return builder.toString();
  }

}
