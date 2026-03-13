#include <iostream>
#include <vector>
using namespace std;



// int addNums(int, int); //What if we wante this to work with floats? We do line 8
// float addNums(float, float);

template <class T1, class T2, class T3>//Both of these syntax work
//template <typename T1, class T2, typename T3>

T3 addNums(T1, T2); //This is a "function" that allows us to overload mixed type information.


int main(){
//These data-types are being passed into the functions.
    float num1, num2;
    float sum;
    
    vector <int> myVector; //This creates a templated class of vectors. We get to choose what valeus 

    cout << "";
    cin >> num1 >> num2;



    cout << num1 << "+" << num2 << "=" << addNums(num1, num2) << endl;

    return 0;

}

//What if we want to add an integer and a float?

float addNums(float, float)
{
    return 0.0f;
}
/*Basically, if we have multiple function overloads, it gets convoluted quickly. So we do templating to keep it more simple.*/


template <class T1, class T2, class T3>
T3 addNums(T1 n1, T2 n2) //This is a "function" that allows us to overload mixed type information.
{


    return n1 + n2;
}
