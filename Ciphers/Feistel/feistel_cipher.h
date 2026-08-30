#include <iostream>
#include <bitset>
#include <array>

class FeistelCipher
{
private:
    std::array<int, 16> sbox =
    {
        14, 4, 13, 1,
        2, 15, 11, 8,
        3, 10, 6, 12,
        5, 9, 0, 7
    };

    int masterKey;

    int mask4(int value) const
    {
        return value & 0x0F;
    }

    int rotateLeft4(int value) const
    {
        value = mask4(value);

        return mask4(
            (value << 1) |
            (value >> 3)
        );
    }

    int getRoundKey(int round) const
    {
        int key = masterKey;

        for (int i = 0; i < round; i++)
        {
            key = rotateLeft4(key);
        }

        return key;
    }

    int roundFunction(
        int right,
        int roundKey,
        bool showSteps
    ) const
    {
        int xorResult = mask4(right ^ roundKey);

        int sboxResult = sbox[xorResult];

        if (showSteps)
        {
            std::cout << "\n    ROUND FUNCTION F(R, K)\n";
            std::cout << "    ----------------------\n";

            std::cout
                << "    Right half:   "
                << std::bitset<4>(right)
                << "\n";

            std::cout
                << "    Round key:    "
                << std::bitset<4>(roundKey)
                << "\n";

            std::cout
                << "                   ----\n";

            std::cout
                << "    XOR result:   "
                << std::bitset<4>(xorResult)
                << "\n";

            std::cout
                << "\n    S-box lookup:\n";

            std::cout
                << "    SBox["
                << xorResult
                << "] = "
                << sboxResult
                << "\n";

            std::cout
                << "    S-box output: "
                << std::bitset<4>(sboxResult)
                << "\n";
        }

        return sboxResult;
    }

public:
    explicit FeistelCipher(int key)
    {
        masterKey = mask4(key);
    }

    int encrypt(
        int plaintext,
        bool showSteps = true
    ) const
    {
        int left = (plaintext >> 4) & 0x0F;
        int right = plaintext & 0x0F;

        if (showSteps)
        {
            std::cout
                << "\n====================================\n"
                << "        FEISTEL ENCRYPTION\n"
                << "====================================\n";

            std::cout
                << "\nPlaintext: "
                << std::bitset<8>(plaintext)
                << "\n";

            std::cout
                << "\nInitial split:\n";

            std::cout
                << "L0 = "
                << std::bitset<4>(left)
                << "\n";

            std::cout
                << "R0 = "
                << std::bitset<4>(right)
                << "\n";
        }

        for (int round = 0; round < 4; round++)
        {
            int roundKey = getRoundKey(round);

            if (showSteps)
            {
                std::cout
                    << "\n====================================\n"
                    << "ROUND "
                    << round + 1
                    << "\n"
                    << "====================================\n";

                std::cout
                    << "\nCurrent state:\n";

                std::cout
                    << "L"
                    << round
                    << " = "
                    << std::bitset<4>(left)
                    << "\n";

                std::cout
                    << "R"
                    << round
                    << " = "
                    << std::bitset<4>(right)
                    << "\n";

                std::cout
                    << "\nSelected half for F(): R"
                    << round
                    << "\n";
            }

            int fOutput =
                roundFunction(
                    right,
                    roundKey,
                    showSteps
                );

            int newLeft = right;
            int newRight = mask4(left ^ fOutput);

            if (showSteps)
            {
                std::cout
                    << "\n    FEISTEL XOR\n"
                    << "    -----------\n";

                std::cout
                    << "    Old left:     "
                    << std::bitset<4>(left)
                    << "\n";

                std::cout
                    << "    F output:     "
                    << std::bitset<4>(fOutput)
                    << "\n";

                std::cout
                    << "                  ----\n";

                std::cout
                    << "    New right:    "
                    << std::bitset<4>(newRight)
                    << "\n";

                std::cout
                    << "\nSwap / assignment:\n";

                std::cout
                    << "L"
                    << round + 1
                    << " = old R"
                    << round
                    << " = "
                    << std::bitset<4>(newLeft)
                    << "\n";

                std::cout
                    << "R"
                    << round + 1
                    << " = "
                    << std::bitset<4>(newRight)
                    << "\n";
            }

            left = newLeft;
            right = newRight;
        }

        int ciphertext =
            (left << 4) | right;

        if (showSteps)
        {
            std::cout
                << "\n====================================\n"
                << "CIPHERTEXT\n"
                << "====================================\n";

            std::cout
                << "\nCiphertext: "
                << std::bitset<8>(ciphertext)
                << "\n";
        }

        return ciphertext;
    }

    int decrypt(
        int ciphertext,
        bool showSteps = true
    ) const
    {
        int left = (ciphertext >> 4) & 0x0F;
        int right = ciphertext & 0x0F;

        if (showSteps)
        {
            std::cout
                << "\n====================================\n"
                << "        FEISTEL DECRYPTION\n"
                << "====================================\n";

            std::cout
                << "\nCiphertext: "
                << std::bitset<8>(ciphertext)
                << "\n";
        }

        for (int round = 3; round >= 0; round--)
        {
            int roundKey = getRoundKey(round);

            int oldRight = left;

            int fOutput =
                roundFunction(
                    oldRight,
                    roundKey,
                    showSteps
                );

            int oldLeft =
                mask4(right ^ fOutput);

            if (showSteps)
            {
                std::cout
                    << "\nRecovering previous state:\n";

                std::cout
                    << "Previous right = current left = "
                    << std::bitset<4>(oldRight)
                    << "\n";

                std::cout
                    << "Previous left = current right XOR F(...)\n";

                std::cout
                    << std::bitset<4>(right)
                    << "\nXOR\n"
                    << std::bitset<4>(fOutput)
                    << "\n----\n"
                    << std::bitset<4>(oldLeft)
                    << "\n";
            }

            left = oldLeft;
            right = oldRight;
        }

        int plaintext =
            (left << 4) | right;

        if (showSteps)
        {
            std::cout
                << "\n====================================\n"
                << "RECOVERED PLAINTEXT\n"
                << "====================================\n";

            std::cout
                << "\nPlaintext: "
                << std::bitset<8>(plaintext)
                << "\n";
        }

        return plaintext;
    }

    void displayKeySchedule() const
    {
        std::cout
            << "\n====================================\n"
            << "KEY SCHEDULE\n"
            << "====================================\n";

        std::cout
            << "\nMaster key: "
            << std::bitset<4>(masterKey)
            << "\n\n";

        for (int round = 0; round < 4; round++)
        {
            std::cout
                << "K"
                << round + 1
                << " = "
                << std::bitset<4>(
                    getRoundKey(round)
                )
                << "\n";
        }
    }
};
