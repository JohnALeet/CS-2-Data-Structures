#include <iostream>

using namespace std;

class Marker
{
    private: //These are access specifiers. These are attributes of the objects or "variables".
        string _color; //The _ implies an attribute in a class
        float _inklevel;
        string _brand;
        bool _cap;


    public:
        //This is how we access the members of the private class. This is just accessing methods, which sometimes people (Bergen) call function.
        string getcolor()//This is a getter
        {
            return _color;
        }
        void setColor(string color)//This is a setter
        {

            _color = color;
        }
        
        void toggleCap()
        {
            if (_cap) _cap = false;
            else _cap = true;

        }

};



int main(int argc, char* argv[])
{
    //What do I mean by OOP? Instead of functions for generalized things. It's a description of objects and methods for generalized use for that thing.
    Marker marker1;
    marker1.setColor("Black")

    return 0;
}