#include <iostream>
#include <vector>
#include <numeric>   // std::gcd

struct Totient {
    int n;                       // The modulus
    std::vector<int> coprimes;   // Integers relatively prime to n
    int cardinality;             // φ(n)
};

Totient totient(int n) {
    Totient result;

    result.n = n;

    for (int k = 1; k <= n; ++k) {
        if (std::gcd(k, n) == 1) {
            result.coprimes.push_back(k);
        }
    }

    result.cardinality = result.coprimes.size();

    return result;
}

int main() {
    Totient t = totient(12);

    std::cout << "n = " << t.n << '\n';

    std::cout << "Coprime elements: ";

    for (int x : t.coprimes) {
        std::cout << x << " ";
    }

    std::cout << "\nCardinality = " << t.cardinality << '\n';

    return 0;
}