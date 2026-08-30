#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <limits>

#include "feistel_cipher.h"
#include "crypt_analysis.h"


int main()
{
    int choice = 0;

    while (choice != 5)
    {
        std::cout
            << "\n====================================\n"
            << "        FEISTEL CIPHER\n"
            << "====================================\n"
            << "1. Encrypt and decrypt text\n"
            << "2. Differential cryptanalysis\n"
            << "3. Linear cryptanalysis\n"
            << "4. Run all cryptanalysis\n"
            << "5. Exit\n"
            << "====================================\n"
            << "Choice: ";

        std::cin >> choice;


        // =========================================================
        // OPTION 1
        // ENCRYPT AND DECRYPT TEXT
        // =========================================================

        if (choice == 1)
        {
            int key;
            std::string plaintext;

            std::cout
                << "\n====================================\n"
                << "        TEXT ENCRYPTION\n"
                << "====================================\n";

            std::cout
                << "\nEnter a key from 0 to 15: ";

            std::cin >> key;

            while (key < 0 || key > 15)
            {
                std::cout
                    << "Key must be between 0 and 15.\n"
                    << "Enter key: ";

                std::cin >> key;
            }


            // Clear newline left behind by std::cin.
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );


            std::cout
                << "\nEnter plaintext: ";

            std::getline(std::cin, plaintext);


            // Create cipher using user's key.
            FeistelCipher cipher(key);


            // Stores encrypted value of each character.
            std::vector<int> ciphertext;


            std::cout
                << "\n====================================\n"
                << "INPUT\n"
                << "====================================\n";


            std::cout
                << "\nMaster key:\n"
                << "Decimal: " << key << "\n"
                << "Binary:  "
                << std::bitset<4>(key)
                << "\n";


            std::cout
                << "\nPlaintext:\n"
                << plaintext
                << "\n";


            cipher.displayKeySchedule();


            // =====================================================
            // DISPLAY PLAINTEXT BYTES
            // =====================================================

            std::cout
                << "\n====================================\n"
                << "PLAINTEXT BYTES\n"
                << "====================================\n";


            for (int i = 0;
                 i < static_cast<int>(plaintext.length());
                 i++)
            {
                int characterValue =
                    static_cast<int>(
                        static_cast<unsigned char>(
                            plaintext[i]
                        )
                    );


                std::cout
                    << "\nCharacter: '"
                    << plaintext[i]
                    << "'\n"

                    << "Decimal:   "
                    << characterValue
                    << "\n"

                    << "Binary:    "
                    << std::bitset<8>(
                        characterValue
                    )
                    << "\n";
            }


            // =====================================================
            // ENCRYPTION
            // =====================================================

            std::cout
                << "\n====================================\n"
                << "ENCRYPTION\n"
                << "====================================\n";


            for (int i = 0;
                 i < static_cast<int>(plaintext.length());
                 i++)
            {
                int characterValue =
                    static_cast<int>(
                        static_cast<unsigned char>(
                            plaintext[i]
                        )
                    );


                std::cout
                    << "\n\n************************************\n"
                    << "Encrypting character: '"
                    << plaintext[i]
                    << "'\n"
                    << "************************************\n";


                int encrypted =
                    cipher.encrypt(
                        characterValue
                    );


                ciphertext.push_back(
                    encrypted
                );
            }


            // =====================================================
            // CIPHERTEXT OUTPUT
            // =====================================================

            std::cout
                << "\n====================================\n"
                << "CIPHERTEXT\n"
                << "====================================\n";


            std::cout
                << "\nCiphertext as binary values:\n";


            for (int i = 0;
                 i < static_cast<int>(ciphertext.size());
                 i++)
            {
                std::cout
                    << std::bitset<8>(
                        ciphertext[i]
                    )
                    << " ";
            }


            std::cout
                << "\n\nCiphertext as decimal values:\n";


            for (int i = 0;
                 i < static_cast<int>(ciphertext.size());
                 i++)
            {
                std::cout
                    << ciphertext[i]
                    << " ";
            }


            std::cout << "\n";


            // =====================================================
            // DECRYPTION
            // =====================================================

            std::string recoveredText;


            std::cout
                << "\n====================================\n"
                << "DECRYPTION\n"
                << "====================================\n";


            for (int i = 0;
                 i < static_cast<int>(ciphertext.size());
                 i++)
            {
                std::cout
                    << "\n\n************************************\n"
                    << "Decrypting block "
                    << i + 1
                    << "\n"
                    << "************************************\n";


                int recovered =
                    cipher.decrypt(
                        ciphertext[i]
                    );


                recoveredText +=
                    static_cast<char>(
                        recovered
                    );
            }


            // =====================================================
            // FINAL RESULTS
            // =====================================================

            std::cout
                << "\n====================================\n"
                << "FINAL RESULTS\n"
                << "====================================\n";


            std::cout
                << "\nOriginal plaintext:\n"
                << plaintext
                << "\n";


            std::cout
                << "\nRecovered plaintext:\n"
                << recoveredText
                << "\n";


            if (plaintext == recoveredText)
            {
                std::cout
                    << "\nSUCCESS: Decryption recovered "
                    << "the original text.\n";
            }
            else
            {
                std::cout
                    << "\nERROR: Recovered text does not "
                    << "match the original.\n";
            }
        }


        // =========================================================
        // OPTION 2
        // DIFFERENTIAL CRYPTANALYSIS
        // =========================================================

        else if (choice == 2)
        {
            Cryptanalysis analyst;

            analyst.differentialAnalysis();
        }


        // =========================================================
        // OPTION 3
        // LINEAR CRYPTANALYSIS
        // =========================================================

        else if (choice == 3)
        {
            Cryptanalysis analyst;

            analyst.linearAnalysis();
        }


        // =========================================================
        // OPTION 4
        // RUN BOTH ATTACKS
        // =========================================================

        else if (choice == 4)
        {
            Cryptanalysis analyst;

            analyst.runAllAnalysis();
        }


        // =========================================================
        // OPTION 5
        // EXIT
        // =========================================================

        else if (choice == 5)
        {
            std::cout
                << "\n====================================\n"
                << "EXITING FEISTEL CIPHER\n"
                << "====================================\n";
        }


        // =========================================================
        // INVALID MENU CHOICE
        // =========================================================

        else
        {
            std::cout
                << "\nInvalid choice.\n"
                << "Please enter a number from 1 to 5.\n";
        }
    }


    return 0;
}