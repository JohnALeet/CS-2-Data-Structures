#include <iostream>
#include <vector>
#include <numeric>
#include <iomanip>
#include <stdexcept>

struct ResidueClass
{
    int value;
    int gcdWithN;
    bool invertible;
};


struct PrimeFactor
{
    int prime;
    int exponent;
};


struct TotientData
{
    int enumeratedValue;       // Count units explicitly
    int structuralValue;       // Euler product formula

    std::vector<int> units;    // Actual invertible residues
};


struct BezoutResult
{
    int gcd;
    int x;
    int y;
};


struct CRTComponent
{
    int modulus;
    int residue;
};


// ============================================================
// MODULUS SYSTEM
// ============================================================

class ModulusSystem
{
private:

    int n;
    bool prime;

    std::vector<PrimeFactor> primeFactors;

    std::vector<ResidueClass> residues;

    std::vector<int> invertibleResidues;
    std::vector<int> nonInvertibleResidues;

    TotientData totient;


    // ========================================================
    // This will shrink an integer that excees the bounds of modulus.
    // Ex: normalize(14) with n = 12 will return 2. Because 14 occupies [2] in the domain of Z/12Z
    // Ensures that all numbers > n will wrap around to a place on Z/nZ
    // ========================================================

    int normalize(int a) const
    {
        int result = a % n;

        if (result < 0)
        {
            result += n;
        }

        return result;
    }


    // ========================================================
    // INTEGER POWER
    //
    // Used for prime powers in CRT.
    // ========================================================

    int integerPower(int base, int exponent) const
    {
        int result = 1;

        for (int i = 0; i < exponent; ++i)
        {
            result *= base;
        }

        return result;
    }


    // ========================================================
    // PRIME FACTORIZATION
    //
    // n = p1^e1 * p2^e2 * ...
    // ========================================================

    void factorize()
    {
        int remaining = n;

        for (int p = 2; p * p <= remaining; ++p)
        {
            if (remaining % p == 0)
            {
                int exponent = 0;

                while (remaining % p == 0)
                {
                    remaining /= p;
                    ++exponent;
                }

                PrimeFactor factor;

                factor.prime = p;
                factor.exponent = exponent;

                primeFactors.push_back(factor);
            }
        }


        if (remaining > 1)
        {
            PrimeFactor factor;

            factor.prime = remaining;
            factor.exponent = 1;

            primeFactors.push_back(factor);
        }
    }


    // ========================================================
    // CONSTRUCT ALL RESIDUE CLASSES
    //
    // Z/nZ = {0, 1, 2, ..., n - 1} Is the integer ring.
    //
    // Then separate into:
    //
    // gcd(a,n) = 1 (Invertible residues)
    //
    // and
    //
    // gcd(a,n) != 1 (Noninvertible residues)
    // ========================================================

    void buildResidues()
    {
        for (int a = 0; a < n; ++a)
        {
            int g = std::gcd(a, n);

            ResidueClass residue;

            residue.value = a;
            residue.gcdWithN = g;
            residue.invertible = (g == 1);

            residues.push_back(residue);


            if (residue.invertible)
            {
                invertibleResidues.push_back(a);
            }
            else
            {
                nonInvertibleResidues.push_back(a);
            }
        }
    }


    // ========================================================
    // PRIME TEST
    //
    // n is prime iff all nonzero residues are units.
    //
    // φ(n) = n - 1
    // ========================================================

    void determinePrime()
    {
        prime =
            invertibleResidues.size()
            ==
            static_cast<std::size_t>(n - 1);
    }


    // ========================================================
    // STRUCTURAL TOTIENT
    //
    // φ(n)
    //
    // = n Product[p|n] (1 - 1/p)
    //
    // Uses prime factorization instead of enumerating residues.
    // ========================================================

    int calculateStructuralTotient() const
    {
        int result = n;

        for (const PrimeFactor& factor : primeFactors)
        {
            result =
                result
                / factor.prime
                * (factor.prime - 1);
        }

        return result;
    }


    // ========================================================
    // BUILD TOTIENT DATA
    // ========================================================

    void buildTotient()
    {
        totient.enumeratedValue =
            static_cast<int>(
                invertibleResidues.size() //Totient is just the size of invertible residues.
            );


        totient.structuralValue =
            calculateStructuralTotient();


        totient.units =
            invertibleResidues;
    }


    // ========================================================
    // EXTENDED EUCLIDEAN ALGORITHM:
    // This uses Bezout's identity to solve a Diophantine equation.
    // Which is a fancy way of saying there's an equation we plug a residue into to solve for its inverse in the domain of mod n.
    // Finds:
    //
    // ax + ny = gcd(a,n)
    //
    // Ex: 4(7) +9(-3) = 28 - 27 = 1 
    // a = 4, a^-1 = 7 
    // This pretty much means that 4 is invertible modulo 9, and 7 is the inverse of [4]_9
    // ========================================================

    BezoutResult extendedGCD(int a, int b) const
    {
        if (b == 0)
        {
            BezoutResult result;

            result.gcd = a;
            result.x = 1;
            result.y = 0;

            return result;
        }


        BezoutResult previous =
            extendedGCD(
                b,
                a % b
            );


        BezoutResult result;

        result.gcd =
            previous.gcd;

        result.x =
            previous.y;

        result.y =
            previous.x
            -
            (a / b) * previous.y;


        return result;
    }


public:
        // ========================================================
        // ADDITION COMMUTATIVITY
        //
        // Checks:
        //
        // a + b ≡ b + a mod n
        //
        // for every pair of residues.
        // ========================================================

        bool additionCommutative() const
        {
            for (const ResidueClass& a : residues)
            {
                for (const ResidueClass& b : residues)
                {
                    int left =
                        (a.value + b.value) % n;

                    int right =
                        (b.value + a.value) % n;


                    if (left != right)
                    {
                        return false;
                    }
                }
            }

            return true;
        }


        // ========================================================
        // ADDITION ASSOCIATIVITY
        //
        // Checks:
        //
        // (a + b) + c ≡ a + (b + c) mod n
        //
        // for every triple of residues.
        // ========================================================

        bool additionAssociative() const
        {
            for (const ResidueClass& a : residues)
            {
                for (const ResidueClass& b : residues)
                {
                    for (const ResidueClass& c : residues)
                    {
                        int left =
                            (
                                (
                                    a.value
                                    +
                                    b.value
                                ) % n
                                +
                                c.value
                            ) % n;


                        int right =
                            (
                                a.value
                                +
                                (
                                    b.value
                                    +
                                    c.value
                                ) % n
                            ) % n;


                        if (left != right)
                        {
                            return false;
                        }
                    }
                }
            }

            return true;
        }


        // ========================================================
        // MULTIPLICATION COMMUTATIVITY
        //
        // Checks:
        //
        // ab ≡ ba mod n
        //
        // for every pair of residues.
        // ========================================================

        bool multiplicationCommutative() const
        {
            for (const ResidueClass& a : residues)
            {
                for (const ResidueClass& b : residues)
                {
                    long long leftProduct =
                        static_cast<long long>(a.value)
                        *
                        b.value;


                    long long rightProduct =
                        static_cast<long long>(b.value)
                        *
                        a.value;


                    int left =
                        static_cast<int>(
                            leftProduct % n
                        );


                    int right =
                        static_cast<int>(
                            rightProduct % n
                        );


                    if (left != right)
                    {
                        return false;
                    }
                }
            }

            return true;
        }


        // ========================================================
        // MULTIPLICATION ASSOCIATIVITY
        //
        // Checks:
        //
        // (ab)c ≡ a(bc) mod n
        //
        // for every triple of residues.
        // ========================================================

        bool multiplicationAssociative() const
        {
            for (const ResidueClass& a : residues)
            {
                for (const ResidueClass& b : residues)
                {
                    for (const ResidueClass& c : residues)
                    {
                        long long ab =
                            static_cast<long long>(a.value)
                            *
                            b.value;


                        int abMod =
                            static_cast<int>(
                                ab % n
                            );


                        long long leftProduct =
                            static_cast<long long>(abMod)
                            *
                            c.value;


                        long long bc =
                            static_cast<long long>(b.value)
                            *
                            c.value;


                        int bcMod =
                            static_cast<int>(
                                bc % n
                            );


                        long long rightProduct =
                            static_cast<long long>(a.value)
                            *
                            bcMod;


                        int left =
                            static_cast<int>(
                                leftProduct % n
                            );


                        int right =
                            static_cast<int>(
                                rightProduct % n
                            );


                        if (left != right)
                        {
                            return false;
                        }
                    }
                }
            }

            return true;
        }
        // ========================================================
        // ZERO DIVISOR TEST
        //
        // A nonzero residue a is a zero divisor if there exists
        // another nonzero residue b such that:
        //
        // ab ≡ 0 mod n
        // ========================================================

        bool hasZeroDivisors() const
        {
            for (int a = 1; a < n; ++a)
            {
                for (int b = 1; b < n; ++b)
                {
                    long long product =
                        static_cast<long long>(a)
                        *
                        b;


                    if (product % n == 0)
                    {
                        return true;
                    }
                }
            }

            return false;
        }

        // ========================================================
        // DISPLAY ZERO DIVISORS
        //
        // Shows nonzero pairs:
        //
        // a * b ≡ 0 mod n
        // ========================================================

        void displayZeroDivisors() const
        {
            std::cout
                << "\nZero divisor pairs modulo "
                << n
                << ":\n\n";


            bool found = false;


            for (int a = 1; a < n; ++a)
            {
                for (int b = a; b < n; ++b)
                {
                    long long product =
                        static_cast<long long>(a)
                        *
                        b;


                    if (product % n == 0)
                    {
                        std::cout
                            << a
                            << " * "
                            << b
                            << " ≡ 0 mod "
                            << n
                            << '\n';


                        found = true;
                    }
                }
            }


            if (!found)
            {
                std::cout
                    << "No nonzero zero divisors exist.\n";
            }
        }

        // ========================================================
        // FULL MULTIPLICATION TABLE
        //
        // Displays multiplication over all residues in Z/nZ.
        //
        // A zero marked with * means:
        //
        // nonzero * nonzero ≡ 0 mod n
        //
        // which identifies a zero-divisor interaction.
        // ========================================================

        void displayMultiplicationTable() const
        {
            std::cout
                << "\nMultiplication table modulo "
                << n
                << ":\n\n";


            std::cout
                << "Commutative: "
                << (
                    multiplicationCommutative()
                    ? "yes"
                    : "no"
                )
                << "  (table should be symmetric across diagonal)\n";


            std::cout
                << "Associative: "
                << (
                    multiplicationAssociative()
                    ? "yes"
                    : "no"
                )
                << "  (checked over every triple a,b,c)\n";


            std::cout
                << "\n* marks a nonzero zero-divisor product.\n\n";


            std::cout
                << std::setw(6)
                << "*";


            for (const ResidueClass& column : residues)
            {
                std::cout
                    << std::setw(6)
                    << column.value;
            }


            std::cout << '\n';


            for (const ResidueClass& row : residues)
            {
                std::cout
                    << std::setw(6)
                    << row.value;


                for (const ResidueClass& column : residues)
                {
                    long long product =
                        static_cast<long long>(row.value)
                        *
                        column.value;


                    int result =
                        static_cast<int>(
                            product % n
                        );


                    if (
                        result == 0
                        &&
                        row.value != 0
                        &&
                        column.value != 0
                    )
                    {
                        std::cout
                            << std::setw(6)
                            << "0*";
                    }
                    else
                    {
                        std::cout
                            << std::setw(6)
                            << result;
                    }
                }


                std::cout << '\n';
            }
        }



    explicit ModulusSystem(int input):// I used explicit here because this is the n in mod(n) and I don't want to do implicit conversions.
        n(input),
        prime(false)
    {
        if (n < 2)
        {
            throw std::invalid_argument(
                "Modulus must be at least 2."
            );
        }


        factorize();

        buildResidues();

        determinePrime();

        buildTotient();
    }
    int getModulus() const
    {
        return n;
    }


    bool isPrime() const
    {
        return prime;
    }


    const std::vector<PrimeFactor>&
    getPrimeFactors() const
    {
        return primeFactors;
    }


    const std::vector<ResidueClass>&
    getResidues() const
    {
        return residues;
    }


    const std::vector<int>&
    getInvertibleResidues() const
    {
        return invertibleResidues;
    }


    const std::vector<int>&
    getNonInvertibleResidues() const
    {
        return nonInvertibleResidues;
    }


    const TotientData&
    getTotient() const
    {
        return totient;
    }


    // ========================================================
    // MULTIPLICATIVE INVERSE
    //
    // Find x such that:
    //
    // ax = 1 mod n
    //
    // From Bezout:
    //
    // ax + ny = 1
    //
    // Therefore:
    //
    // ax = 1 mod n
    // ========================================================

    int inverse(int a) const
    {
        a = normalize(a);


        BezoutResult result =
            extendedGCD(a, n);


        if (result.gcd != 1)
        {
            throw std::invalid_argument
            (
                "Residue has no multiplicative inverse."
            );
        }


        return normalize
        (
            result.x
        );
    }


    // ========================================================
    // MULTIPLICATIVE ORDER
    //
    // ord_n(a)
    //
    // = smallest positive k such that
    //
    // a^k = 1 mod n
    //
    // ========================================================

    int order(int a) const
    {
        a = normalize(a);


        if (std::gcd(a, n) != 1)
        {
            throw std::invalid_argument(
                "Multiplicative order requires a unit."
            );
        }


        int current = 1;


        for (
            int k = 1;
            k <= totient.enumeratedValue;
            ++k
        )
        {
            current =
                (current * a) % n;


            if (current == 1)
            {
                return k;
            }
        }


        throw std::runtime_error(
            "Could not determine multiplicative order."
        );
    }


    // ========================================================
    // CRT DECOMPOSITION
    //
    // Example:
    //
    // 12 = 4 * 3
    //
    // [11]_12
    //
    // ->
    //
    // ([3]_4, [2]_3)
    // ========================================================

    std::vector<CRTComponent>
    crtDecompose(int a) const
    {
        std::vector<CRTComponent>
            components;


        for (const PrimeFactor& factor : primeFactors)
        {
            int componentModulus =
                integerPower(
                    factor.prime,
                    factor.exponent
                );


            int componentResidue =
                a % componentModulus;


            if (componentResidue < 0)
            {
                componentResidue +=
                    componentModulus;
            }


            CRTComponent component;

            component.modulus =
                componentModulus;

            component.residue =
                componentResidue;


            components.push_back(
                component
            );
        }


        return components;
    }
  
    // ========================================================
    // DISPLAY SUMMARY
    // ========================================================

    void displaySummary() const
    {
        std::cout
            << "\n====================================\n";

        std::cout
            << "MODULAR SYSTEM Z/"
            << n
            << "Z\n";

        std::cout
            << "====================================\n";


        std::cout
            << "Modulus: "
            << n
            << '\n';


        std::cout
            << "Prime: "
            << (prime ? "true" : "false")
            << '\n';


        std::cout
            << "Number of residues: "
            << residues.size()
            << '\n';


        std::cout
            << "Number of units: "
            << invertibleResidues.size()
            << '\n';


        std::cout
            << "Number of nonunits: "
            << nonInvertibleResidues.size()
            << '\n';
    }


    // ========================================================
    // DISPLAY PRIME FACTORIZATION
    // ========================================================

    void displayPrimeFactorization() const
    {
        std::cout
            << "\nPrime factorization:\n";

        std::cout
            << n
            << " = ";


        for (
            std::size_t i = 0;
            i < primeFactors.size();
            ++i
        )
        {
            std::cout
                << primeFactors[i].prime;


            if (primeFactors[i].exponent > 1)
            {
                std::cout
                    << "^"
                    << primeFactors[i].exponent;
            }


            if (i + 1 < primeFactors.size())
            {
                std::cout
                    << " * ";
            }
        }


        std::cout
            << '\n';
    }


    // ========================================================
    // DISPLAY TOTIENT
    //
    // Method 1:
    // explicitly count units
    //
    // Method 2:
    // use prime factor structure
    // ========================================================

    void displayTotient() const
    {
        std::cout
            << "\nEuler Totient φ :\n";


        std::cout
            << "Enumerated φ("
            << n
            << ") = "
            << totient.enumeratedValue
            << '\n';


        std::cout
            << "Structural φ("
            << n
            << ") = "
            << totient.structuralValue
            << '\n';


        if (
            totient.enumeratedValue
            ==
            totient.structuralValue
        )
        {
            std::cout
                << "Both methods agree.\n";
        }


        if (prime)
        {
            std::cout
                << n
                << " is prime, therefore φ("
                << n
                << ") = "
                << n
                << " - 1 = "
                << n - 1
                << '\n';
        }
    }


    // ========================================================
    // DISPLAY ALL RESIDUES
    // ========================================================

    void displayResidues() const
    {
        std::cout
            << "\nResidue classes modulo "
            << n
            << ":\n\n";


        std::cout
            << std::setw(10)
            << "Residue"

            << std::setw(10)
            << "gcd"

            << std::setw(15)
            << "Invertible"

            << '\n';


        for (const ResidueClass& residue : residues)
        {
            std::cout
                << std::setw(10)
                << residue.value

                << std::setw(10)
                << residue.gcdWithN

                << std::setw(15)
                << (
                    residue.invertible
                    ?
                    "yes"
                    :
                    "no"
                )

                << '\n';
        }
    }


    // ========================================================
    // DISPLAY UNIT AND NONUNIT CLASSES
    // ========================================================

    void displayClasses() const
    {
        std::cout
            << "\nInvertible residues:\n{ ";


        for (int value : invertibleResidues)
        {
            std::cout
                << value
                << ' ';
        }


        std::cout
            << "}\n";


        std::cout
            << "\nNoninvertible residues:\n{ ";


        for (int value : nonInvertibleResidues)
        {
            std::cout
                << value
                << ' ';
        }


        std::cout
            << "}\n";
    }


    // ========================================================
    // DISPLAY MULTIPLICATIVE INVERSES
    // ========================================================

    void displayInverses() const
    {
        std::cout
            << "\nMultiplicative inverses:\n\n";


        for (int a : invertibleResidues)
        {
            std::cout
                << std::setw(5)
                << a

                << "^-1 = "

                << std::setw(5)
                << inverse(a)

                << " mod "
                << n

                << '\n';
        }
    }


    // ========================================================
    // DISPLAY MULTIPLICATIVE ORDERS
    // ========================================================

    void displayOrders() const
    {
        std::cout
            << "\nMultiplicative orders:\n\n";


        for (int a : invertibleResidues)
        {
            std::cout
                << "ord_"
                << n
                << "("
                << a
                << ") = "
                << order(a)
                << '\n';
        }
    }


    // ========================================================
    // UNIT MULTIPLICATION TABLE
    //
    // Displays:
    //
    // (Z/nZ)^*
    //
    // ========================================================

    void displayUnitTable() const
    {
        std::cout
            << "\nUnit multiplication table modulo "
            << n
            << ":\n\n";


        std::cout
            << std::setw(6)
            << "*";


        for (int column : invertibleResidues)
        {
            std::cout
                << std::setw(6)
                << column;
        }


        std::cout
            << '\n';


        for (int row : invertibleResidues)
        {
            std::cout
                << std::setw(6)
                << row;


            for (int column : invertibleResidues)
            {
                int result =
                    (row * column) % n;


                std::cout
                    << std::setw(6)
                    << result;
            }


            std::cout
                << '\n';
        }
    }


    // ========================================================
    // MIXED MATRIX
    //
    // Units across top.
    //
    // Nonunits down left.
    //
    // Interior:
    //
    // row * column mod n
    // ========================================================

    void displayMixedMatrix() const
    {
        std::cout
            << "\nUnits across top; nonunits down left:\n\n";


        std::cout
            << std::setw(6)
            << "*";


        for (int unit : invertibleResidues)
        {
            std::cout
                << std::setw(6)
                << unit;
        }


        std::cout
            << '\n';


        for (int nonUnit : nonInvertibleResidues)
        {
            std::cout
                << std::setw(6)
                << nonUnit;


            for (int unit : invertibleResidues)
            {
                int result =
                    (nonUnit * unit) % n;


                std::cout
                    << std::setw(6)
                    << result;
            }


            std::cout
                << '\n';
        }
    }


    // ========================================================
    // DISPLAY CRT DECOMPOSITION
    // ========================================================

    void displayCRT(int a) const
    {
        std::vector<CRTComponent> components =
            crtDecompose(a);


        std::cout
            << "\nChinese Remainder decomposition:\n";


        std::cout
            << "["
            << normalize(a)
            << "]_"
            << n
            << " -> ( ";


        for (
            std::size_t i = 0;
            i < components.size();
            ++i
        )
        {
            std::cout
                << "["
                << components[i].residue
                << "]_"
                << components[i].modulus;


            if (i + 1 < components.size())
            {
                std::cout
                    << ", ";
            }
        }


        std::cout
            << " )\n";
    }

    // ========================================================
    // ADDITIVE INVERSE
    //
    // Find b such that:
    //
    // a + b ≡ 0 mod n
    //
    // Every residue modulo n has an additive inverse.
    // ========================================================

    int additiveInverse(int a) const
    {
        a = normalize(a);

        return normalize(-a);
    }


    // ========================================================
    // DISPLAY ADDITIVE INVERSES
    //
    // Additive identity = 0
    //
    // For every a:
    //
    // a + (-a) ≡ 0 mod n
    // ========================================================

    void displayAdditiveInverses() const
    {
        std::cout
            << "\nAdditive identity: 0\n";

        std::cout
            << "\nAdditive inverses modulo "
            << n
            << ":\n\n";

        for (const ResidueClass& residue : residues)
        {
            int inverse =
                additiveInverse(residue.value);

            std::cout
                << std::setw(5)
                << residue.value

                << " + "

                << std::setw(5)
                << inverse

                << " = "

                << std::setw(5)
                << (
                    residue.value
                    +
                    inverse
                ) % n

                << " mod "
                << n

                << '\n';
        }
    }


    // ========================================================
// ADDITION TABLE
//
// Displays the additive group:
//
// (Z/nZ, +)
//
// Every residue participates.
// Identity = 0.
// Every residue has an additive inverse.
// ========================================================

void displayAdditionTable() const
{
    std::cout
        << "\nAddition table modulo "
        << n
        << ":\n\n";


    std::cout
        << "Commutative: "
        << (
            additionCommutative()
            ? "yes"
            : "no"
        )
        << "  (table symmetric across diagonal)\n";


    std::cout
        << "Associative: "
        << (
            additionAssociative()
            ? "yes"
            : "no"
        )
        << "  (checked over every triple a,b,c)\n\n";


    // Top-left operation symbol
    std::cout
        << std::setw(6)
        << "+";


    // Column labels
    for (const ResidueClass& column : residues)
    {
        std::cout
            << std::setw(6)
            << column.value;
    }


    std::cout << '\n';


    // Row labels and table contents
    for (const ResidueClass& row : residues)
    {
        std::cout
            << std::setw(6)
            << row.value;


        for (const ResidueClass& column : residues)
        {
            int result =
                (
                    row.value
                    +
                    column.value
                ) % n;


            std::cout
                << std::setw(6)
                << result;
        }


        std::cout << '\n';
    }
}


    // ========================================================
// DISPLAY RING / FIELD PROPERTIES
// ========================================================

void displayRingProperties() const
{
    std::cout
        << "\n====================================\n"
        << " RING PROPERTIES OF Z/"
        << n
        << "Z\n"
        << "====================================\n\n";


    std::cout
        << "Addition associative: "
        << (
            additionAssociative()
            ? "yes"
            : "no"
        )
        << '\n';


    std::cout
        << "Addition commutative: "
        << (
            additionCommutative()
            ? "yes"
            : "no"
        )
        << '\n';


    std::cout
        << "Additive identity: 0\n";


    std::cout
        << "Every residue has an additive inverse: yes\n\n";


    std::cout
        << "Multiplication associative: "
        << (
            multiplicationAssociative()
            ? "yes"
            : "no"
        )
        << '\n';


    std::cout
        << "Multiplication commutative: "
        << (
            multiplicationCommutative()
            ? "yes"
            : "no"
        )
        << '\n';


    std::cout
        << "Multiplicative identity: 1\n";


    std::cout
        << "Zero divisors: "
        << (
            hasZeroDivisors()
            ? "yes"
            : "no"
        )
        << "\n\n";


    if (hasZeroDivisors())
    {
        std::cout
            << "Because nonzero zero divisors exist,\n"
            << "Z/"
            << n
            << "Z is not an integral domain.\n";


        std::cout
            << "Therefore it is not a field.\n";
    }
    else
    {
        std::cout
            << "No nonzero zero divisors exist.\n";


        std::cout
            << "Z/"
            << n
            << "Z is a finite integral domain.\n";


        std::cout
            << "Every finite integral domain is a field.\n";


        std::cout
            << "Therefore Z/"
            << n
            << "Z is a field.\n";
    }
}

};