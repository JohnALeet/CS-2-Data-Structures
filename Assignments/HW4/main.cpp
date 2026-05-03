#include <iostream>
#include <string>
#include <sstream>
#include "stack.h"

using namespace std;

double evaluateRPN(string expression)
{
    Stack stack1;
    stringstream ss(expression);
    string token;

    while (ss >> token)
    {
        if (token == "+" || token == "-" || token =="*" || token == "/")
        {
                if (stack1.size() < 2)
                {
                    cout << "Invalid expression!";
                    return NAN;
                }
            
            double num2 = stack1.pop();
            double num1 = stack1.pop();
            double sum = 0.0;

            if (token == "+")
            {
                sum = num1 + num2;
            }
            else if (token == "-")
            {
                sum = num1 - num2;
            }
            else if (token == "*")
            {
                sum = num1 * num2;
            }           
            else if (token == "/")
            {
                if (num2 == 0)
                { 
                    cout << "Error: can't divide by 0!\n"; 
                    return NAN;
                }
                
                sum = num1 / num2;
            }

            stack1.push(sum);
    }

    else
    {
        stringstream convert(token);
        double number;

        if (!(convert >> number))
        {
            cout << "Can't convert token.\n";
            return NAN;
        }
        stack1.push(number);
    }
    }

    if (stack1.size() != 1)
    {
        cout << "Invalid expression.\n";
        return NAN;
    }    
    

    return stack1.pop();
    
}

int main(int argc, char *argv[])
{
    if (argc == 3 && string(argv[1]) == "-p")
    {
        double ans = evaluateRPN(argv[2]);
        if (!isnan(ans))
        {
            cout << argv[2] << " = " << ans << endl;
        }
        return 0;
    }
    string input;
    cout << "Enter an RPN expression: ";
    getline (cin, input);
    
    double ans = evaluateRPN(input);
    if (!isnan(ans))
    {
        cout << input << " = " << ans << endl;
    }

    return 0;
}

void test()
{
    string test[ ]= 
    {
        "3 4 + 5 6 - *",
        "8 0 1 + - ",
        "1 1 *",
        "6 9 - 5 +",
        "4 2 - 1"
    };

    for (int i = 0; i< 5 ; i++)
    {
        double result = evaluateRPN(test[i]);
        if (!isnan(result))
        {
            cout << test[i] << " = " << result << endl;
        }
    }


};
