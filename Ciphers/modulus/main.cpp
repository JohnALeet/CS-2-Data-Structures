#include <iostream>
#include "modulus.h"


void returnToMenu()
{
    std::cout
        << "\nPress Enter to return to the menu...";

    std::cin.ignore(10000, '\n');
    std::cin.get();
}


int main()
{
    while (true)
    {
        int input;

        std::cout
            << "\n====================================\n"
            << "MODULUS RINGS\n"
            << "====================================\n"
            << "\nEnter modulus (n): ";

        std::cin >> input;


        // n defines the entire modular system.
        ModulusSystem mod(input);

        int choice = -1;

        while (choice != 16)
        {
            std::cout
                << "\n====================================\n"
                << " MODULAR SYSTEM Z/"
                << mod.getModulus()
                << "Z\n"
                << "====================================\n"

                << "\n---------- SYSTEM -------------------\n"
                << "1. Display summary\n"
                << "2. Display prime factorization\n"

                << "\n---------- RESIDUES -----------------\n"
                << "3. Display all residue classes\n"
                << "4. Display units and nonunits\n"

                << "\n---------- ADDITION -----------------\n"
                << "5. Display additive inverses\n"
                << "6. Display addition table\n"
                << "7. Add two integers modulo n\n"

                << "\n---------- MULTIPLICATION -----------\n"
                << "8. Display multiplicative inverses\n"
                << "9. Display multiplicative orders\n"
                << "10. Display unit multiplication table\n"
                << "11. Display full multiplication table\n"
                << "12. Display zero divisors\n"
                << "13. Display unit/nonunit matrix\n"
                << "14. Multiply two integers modulo n\n"

                << "\n---------- RING STRUCTURE -----------\n"
                << "15. Display ring/field properties\n"

                << "\n---------- NUMBER THEORY ------------\n"
                << "16. Enter new modulus\n"
                << "17. Display Euler totient\n"
                << "18. Display CRT decomposition\n"

                << "\n0. Exit\n"

                << "\nSelect an option: ";

            std::cin >> choice;


            switch (choice)
            {
                // ====================================================
                // SYSTEM
                // ====================================================

                case 1:
                {
                    mod.displaySummary();

                    returnToMenu();

                    break;
                }


                case 2:
                {
                    mod.displayPrimeFactorization();

                    returnToMenu();

                    break;
                }


                // ====================================================
                // RESIDUES
                // ====================================================

                case 3:
                {
                    mod.displayResidues();

                    returnToMenu();

                    break;
                }


                case 4:
                {
                    mod.displayClasses();

                    returnToMenu();

                    break;
                }


                // ====================================================
                // ADDITION
                // ====================================================

                case 5:
                {
                    mod.displayAdditiveInverses();

                    returnToMenu();

                    break;
                }


                case 6:
                {
                    mod.displayAdditionTable();

                    returnToMenu();

                    break;
                }


                case 7:
                {
                    int a;
                    int b;

                    std::cout
                        << "\nEnter first integer: ";

                    std::cin >> a;


                    std::cout
                        << "Enter second integer: ";

                    std::cin >> b;


                    long long sum =
                        static_cast<long long>(a)
                        +
                        static_cast<long long>(b);


                    int result =
                        static_cast<int>(
                            sum % mod.getModulus()
                        );


                    if (result < 0)
                    {
                        result +=
                            mod.getModulus();
                    }


                    std::cout
                        << "\n"
                        << a
                        << " + "
                        << b
                        << " = "
                        << sum
                        << '\n';


                    std::cout
                        << sum
                        << " mod "
                        << mod.getModulus()
                        << " = "
                        << result
                        << '\n';


                    std::cout
                        << "\nTherefore:\n"

                        << "["
                        << a
                        << "]_"
                        << mod.getModulus()

                        << " + "

                        << "["
                        << b
                        << "]_"
                        << mod.getModulus()

                        << " = "

                        << "["
                        << result
                        << "]_"
                        << mod.getModulus()

                        << '\n';


                    returnToMenu();

                    break;
                }


                // ====================================================
                // MULTIPLICATION
                // ====================================================

                case 8:
                {
                    mod.displayInverses();

                    returnToMenu();

                    break;
                }


                case 9:
                {
                    mod.displayOrders();

                    returnToMenu();

                    break;
                }


                case 10:
                {
                    mod.displayUnitTable();

                    returnToMenu();

                    break;
                }


                case 11:
                {
                    mod.displayMultiplicationTable();

                    returnToMenu();

                    break;
                }


                case 12:
                {
                    mod.displayZeroDivisors();

                    returnToMenu();

                    break;
                }


                case 13:
                {
                    mod.displayMixedMatrix();

                    returnToMenu();

                    break;
                }


                case 14:
                {
                    int a;
                    int b;

                    std::cout
                        << "\nEnter first integer: ";

                    std::cin >> a;


                    std::cout
                        << "Enter second integer: ";

                    std::cin >> b;


                    // long long allows the intermediate product
                    // to hold values larger than a normal int.
                    long long product =
                        static_cast<long long>(a)
                        *
                        static_cast<long long>(b);


                    int result =
                        static_cast<int>(
                            product % mod.getModulus()
                        );


                    if (result < 0)
                    {
                        result +=
                            mod.getModulus();
                    }


                    std::cout
                        << "\n"
                        << a
                        << " * "
                        << b
                        << " = "
                        << product
                        << '\n';


                    std::cout
                        << product
                        << " mod "
                        << mod.getModulus()
                        << " = "
                        << result
                        << '\n';


                    std::cout
                        << "\nTherefore:\n"

                        << "["
                        << a
                        << "]_"
                        << mod.getModulus()

                        << " * "

                        << "["
                        << b
                        << "]_"
                        << mod.getModulus()

                        << " = "

                        << "["
                        << result
                        << "]_"
                        << mod.getModulus()

                        << '\n';


                    returnToMenu();

                    break;
                }


                // ====================================================
                // RING STRUCTURE
                // ====================================================

                case 15:
                {
                    mod.displayRingProperties();

                    returnToMenu();

                    break;
                }


                // ====================================================
                // NEW MODULUS
                // ====================================================

                case 16:
                {
                    std::cout
                        << "\nChanging modulus...\n";

                    break;
                }


                // ====================================================
                // NUMBER THEORY
                // ====================================================

                case 17:
                {
                    mod.displayTotient();

                    returnToMenu();

                    break;
                }


                case 18:
                {
                    int a;

                    std::cout
                        << "\nEnter an integer to decompose: ";

                    std::cin >> a;

                    mod.displayCRT(a);

                    returnToMenu();

                    break;
                }


                // ====================================================
                // EXIT
                // ====================================================

                case 0:
                {
                    std::cout << R"(⢀⡴⠑⡄⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣤⣤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠸⡇⠀⠿⡀⠀⠀⠀⣀⡴⢿⣿⣿⣿⣿⣿⣿⣿⣷⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠑⢄⣠⠾⠁⣀⣄⡈⠙⣿⣿⣿⣿⣿⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢀⡀⠁⠀⠀⠈⠙⠛⠂⠈⣿⣿⣿⣿⣿⠿⡿⢿⣆⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⢀⡾⣁⣀⠀⠴⠂⠙⣗⡀⠀⢻⣿⣿⠭⢤⣴⣦⣤⣹⠀⠀⠀⢀⢴⣶⣆
⠀⠀⢀⣾⣿⣿⣿⣷⣮⣽⣾⣿⣥⣴⣿⣿⡿⢂⠔⢚⡿⢿⣿⣦⣴⣾⠁⠸⣼⡿
⠀⢀⡞⠁⠙⠻⠿⠟⠉⠀⠛⢹⣿⣿⣿⣿⣿⣌⢤⣼⣿⣾⣿⡟⠉⠀⠀⠀⠀⠀
⠀⣾⣷⣶⠇⠀⠀⣤⣄⣀⡀⠈⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀
⠀⠉⠈⠉⠀⠀⢦⡈⢻⣿⣿⣿⣶⣶⣶⣶⣤⣽⡹⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠉⠲⣽⡻⢿⣿⣿⣿⣿⣿⣿⣷⣜⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣷⣶⣮⣭⣽⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⣀⣀⣈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠛⠻⠿⠿⠿⠿⠛⠉
)";

                    return 0;
                }

                default:
                {
                    std::cout
                        << "\nInvalid menu option.\n";

                    returnToMenu();

                    break;
                }
            }
        }
    }
}