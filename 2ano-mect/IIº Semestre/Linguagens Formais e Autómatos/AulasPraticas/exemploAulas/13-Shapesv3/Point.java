/**
 * @author Jodionisio Muachifi
 * Curso: MIECT
 *Universidade de Aveiro
 *Outubro 2020
 */

public class Point {

  private double x;
  private double y;

  public Point(double x, double y) {
    this.x = x;
    this.y = y;
  }

  public double getX() {
    return x;
  }

  public double getY() {
    return y;
  }

  public double distanceTo(Point p) {
    return Math.sqrt(Math.pow(x - p.getX(), 2) + Math.pow(y - p.getY(), 2));
  }

  @Override
  public String toString() {
    return "Ponto de coordenadas (" + x + " , " + y + ")";
  }

  @Override
  public boolean equals(Object obj) {
    if (this == obj) return true;
    if (obj == null) return false;
    if (getClass() != obj.getClass()) return false;
    Point other = (Point) obj;
    if (
      Double.doubleToLongBits(x) != Double.doubleToLongBits(other.x)
    ) return false;
    if (
      Double.doubleToLongBits(y) != Double.doubleToLongBits(other.y)
    ) return false;
    return true;
  }
}
