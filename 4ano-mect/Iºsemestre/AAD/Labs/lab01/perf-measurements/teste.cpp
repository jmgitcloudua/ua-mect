#include <iostream>
#include <string>
using namespace std;

class MyClass
{
public:
    void myMethod()
    {
        cout << "Hello, this is my method in MyClass"
             << "\n";
    }
};
class Employe
{
private:
    int salary;

public:
    void setSalary(int s)
    {
        salary = s;
    }
    int getSalary()
    {
        return salary;
    }
};

int main()
{
    string cars[4] = {"Volvo", "BMW", "Ford", "Mazda"};
    for (size_t i = 0; i < 4; i++)
    {
        cout << cars[i] << "\n";
    }

    cout << "*******************"
         << "\n";

    struct
    {
        /* data */
        int num;
        string str;
    } myVars;

    myVars.num = 30;
    myVars.str = "Jodionisio Muachifi";

    cout << myVars.num + " " + myVars.str << "\n";

    cout << "*******************"
         << "\n";

    MyClass myObj;
    myObj.myMethod();

    cout << "*******************"
         << "\n";

    Employe myObj1;
    myObj1.setSalary(50000);
    cout << "Your salary is: " << myObj1.getSalary() << "\n";

    return 0;
}
