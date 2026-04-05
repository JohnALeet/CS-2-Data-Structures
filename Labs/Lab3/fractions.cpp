#include "fractions.h"

fractions::Fraction::Fraction(int numerator, int denominator)
{
    _numerator = numerator;
    _denominator = denominator;

    if (_numerator == 0 && _denominator == 0)
    {
        cout << "Enter numerator: ";
        cin >> _numerator;
        cout << "Enter denominator: ";
        cin >> _denominator;
    }

    if (_denominator == 0)
    {
        _denominator = 1;
    }
    simplify();
}

fractions::Fraction fractions::Fraction::operator+(fractions::Fraction const &frac)
{
    int top = (_numerator * frac._denominator) + (frac._numerator* _denominator);
    int bottom = _denominator * frac._denominator;

    Fraction ans(top, bottom);

    return ans;

}

fractions::Fraction fractions::Fraction::operator-(fractions::Fraction const &frac)
{
    int top = (_numerator * frac._denominator) - (frac._numerator* _denominator);
    int bottom = _denominator * frac._denominator;

    Fraction ans(top, bottom);
    return ans;

}

fractions::Fraction fractions::Fraction::operator*(Fraction const &frac)
{
    int top = _numerator * frac._numerator ;
    int bottom = _denominator * frac._denominator;

    Fraction ans(top, bottom);

    return ans;

}

fractions::Fraction fractions::Fraction::operator/(Fraction const &frac)
{
    int top = _numerator * frac._denominator ;
    int bottom = _denominator * frac._numerator;

    Fraction ans(top, bottom);

    return ans;
}

fractions::Fraction fractions::Fraction::simplify(Fraction frac)
{
    frac.simplify();
    return frac;
}

void fractions::Fraction::simplify()
{
    int num = _numerator;
    int den = _denominator;
    
    int divideBy = gcd(num, den);

    if (divideBy != 0)
    {
        _numerator = _numerator / divideBy;
        _denominator = _denominator / divideBy;
    }

}

int fractions::Fraction::gcd(int a, int b)
{
    //Copyright Euclid (c) 300 BCE.
    if (a < 0)
    {
        a = -a;
    }
    if (b < 0)
    {
        b = -b;
    }
    
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

bool fractions::Fraction::operator==(Fraction const &frac)
{
    Fraction left = simplify(*this);
    Fraction right = simplify(frac);
    if (left._numerator == right._numerator && left._denominator == right._denominator)
    {
        return true;
    }
    return false;
}

ostream &fractions::operator<<(ostream &os, const Fraction &frac)
{
    os << frac._numerator<< "/" << frac._denominator;
    return os;
}