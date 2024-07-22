#include <iostream>

#include "BigInt.h"
using namespace std;

//**************************************************************
// Programmer: Ayana Tran
// Date: 05/21/2024
// Purpose: main program - test BigInt class w/List class
// Input: BigInt
// Output: comparison and arithmetic operations on BigInt
//**************************************************************

int main()
{
    // test cases:
    // 1 / 1
    // 0 / 0
    // 9 / 0
    // 0 / 9 r9
    // 9 / 1
    // 2 / 9 r9
    // 28 / 8 = 3 r4
    // 22 / 11 = 2
    // 90 / 9 = 10
    // 423 / 5 = 84 r3
    // 5 / 432 = r5
    // 435 / 2 = 217 r1
    // 159 / 28 = 5 r19
    // 8901 / 432 = 20 r261
    // 4239084 / 1234290 = 3 r536214
    // 841824918275 / 128380124 = 6557 r36445207
    // 12481248129 / 3928104 = 3177 r1661721
    // 3928104 / 12481248129 = r3928104
    // 1234567 / 1234 = 1000 r1111167

    string input;

    while (input != "q")
    {
        BigInt num1;
        BigInt num2;
        BigInt num3;

        // cout << "   chicken23\n\n";
        cout << "Enter the first large integer : ";
        cin >> num1;

        cout << "Enter the second large integer : ";
        cin >> num2;

        cout << "num1: " << num1 << endl;
        cout << "num2: " << num2 << endl;

        num3 = num1;
        num1 = num2;
        cout << "\n    Assigned num2 to num1\nnum1: " << num1
             << "\nnum2: " << num2;
        num1 = num3;
        cout << "\n    Put back num1\nnum1: " << num1 << "\nnum2: " << num2
             << endl
             << endl;

        if (num1 == num2)
        {
            cout << num1 << " == " << num2 << " : true" << endl;
        }
        if (num1 != num2)
        {
            cout << num1 << " == " << num2 << " : false" << endl;
        }

        if (num1 > num2)
        {
            cout << num1 << " > " << num2 << " : true\n";
        }
        if (num1 < num2)
        {
            cout << num1 << " < " << num2 << " : true\n";
        }

        if (num1 >= num2)
        {
            cout << num1 << " >= " << num2 << " : true\n";
        }
        if (num1 <= num2)
        {
            cout << num1 << " <= " << num2 << " : true\n";
        }

        cout << "\n" << num1 << " + " << num2 << " = " << (num1 + num2);
        cout << "\n" << num1 << " - " << num2 << " = " << (num1 - num2);
        cout << "\n" << num1 << " * " << num2 << " = " << (num1 * num2);
        cout << "\n" << num1 << " / " << num2 << " = " << (num1 / num2);
        cout << "\n" << num1 << " % " << num2 << " = " << (num1 % num2);

        cout << endl << "----------------------------------------\n";

        cout << "press q to exit, press c to continue\n";
        cin >> input;
    }
}
