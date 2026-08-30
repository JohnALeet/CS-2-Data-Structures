#pragma once

#include <iostream>
#include <array>
#include <bitset>
#include <iomanip>
#include <cmath>

class Cryptanalysis
{
private:

    
    std::array<int, 16> sbox =
    {
        14, 4, 13, 1,
        2, 15, 11, 8,
        3, 10, 6, 12,
        5, 9, 0, 7
    };

    
    int countBits(int value) const
    {
        int count = 0;

        for (int i = 0; i < 4; i++)
        {
            if ((value >> i) & 1)
            {
                count++;
            }
        }

        return count;
    }


    int parity(int value) const
    {
        return countBits(value) % 2;
    }

public:

    void differentialAnalysis() const
    {
        int ddt[16][16] = {};

        std::cout
            << "\n============================================\n"
            << "       DIFFERENTIAL CRYPTANALYSIS\n"
            << "============================================\n";

        /*
            For every possible input difference:

                deltaX = X1 XOR X2

            calculate:

                deltaY = S(X1) XOR S(X2)

            Then count how often each
            deltaX -> deltaY transition occurs.
        */

        for (int deltaX = 0; deltaX < 16; deltaX++)
        {
            for (int x = 0; x < 16; x++)
            {
                int x2 = x ^ deltaX;

                int y1 = sbox[x];
                int y2 = sbox[x2];

                int deltaY = y1 ^ y2;

                ddt[deltaX][deltaY]++;
            }
        }

        std::cout
            << "\nDIFFERENCE DISTRIBUTION TABLE\n\n";

        std::cout << "dX\\dY ";

        for (int deltaY = 0; deltaY < 16; deltaY++)
        {
            std::cout
                << std::setw(3)
                << deltaY;
        }

        std::cout << "\n";

        for (int deltaX = 0; deltaX < 16; deltaX++)
        {
            std::cout
                << std::setw(5)
                << deltaX
                << " ";

            for (int deltaY = 0; deltaY < 16; deltaY++)
            {
                std::cout
                    << std::setw(3)
                    << ddt[deltaX][deltaY];
            }

            std::cout << "\n";
        }

        int bestInputDifference = 0;
        int bestOutputDifference = 0;
        int bestCount = 0;

        for (int deltaX = 1; deltaX < 16; deltaX++)
        {
            for (int deltaY = 0; deltaY < 16; deltaY++)
            {
                if (ddt[deltaX][deltaY] > bestCount)
                {
                    bestCount =
                        ddt[deltaX][deltaY];

                    bestInputDifference =
                        deltaX;

                    bestOutputDifference =
                        deltaY;
                }
            }
        }

        double probability =
            static_cast<double>(bestCount) / 16.0;

        std::cout
            << "\n============================================\n"
            << "STRONGEST DIFFERENTIAL\n"
            << "============================================\n";

        std::cout
            << "\nInput difference:\n"
            << "Decimal: "
            << bestInputDifference
            << "\nBinary:  "
            << std::bitset<4>(
                bestInputDifference
            )
            << "\n";

        std::cout
            << "\nOutput difference:\n"
            << "Decimal: "
            << bestOutputDifference
            << "\nBinary:  "
            << std::bitset<4>(
                bestOutputDifference
            )
            << "\n";

        std::cout
            << "\nOccurrences: "
            << bestCount
            << " / 16\n";

        std::cout
            << "Probability: "
            << probability
            << "\n";

        std::cout
            << "Percentage: "
            << probability * 100.0
            << "%\n";

        std::cout
            << "\nInterpretation:\n";

        std::cout
            << "If two S-box inputs differ by "
            << std::bitset<4>(
                bestInputDifference
            )
            << ", their outputs differ by "
            << std::bitset<4>(
                bestOutputDifference
            )
            << " unusually often.\n";

        std::cout
            << "\nA perfectly uniform 4-bit S-box "
            << "would average about 1 occurrence "
            << "for each output difference.\n";
    }

    void linearAnalysis() const
    {
        int lat[16][16] = {};

        std::cout
            << "\n============================================\n"
            << "          LINEAR CRYPTANALYSIS\n"
            << "============================================\n";

        for (int inputMask = 0;
             inputMask < 16;
             inputMask++)
        {
            for (int outputMask = 0;
                 outputMask < 16;
                 outputMask++)
            {
                int matches = 0;

                for (int x = 0; x < 16; x++)
                {
                    int inputParity =
                        parity(
                            inputMask & x
                        );

                    int outputParity =
                        parity(
                            outputMask &
                            sbox[x]
                        );

                    if (inputParity == outputParity)
                    {
                        matches++;
                    }
                }

                // Bias around 8.
                lat[inputMask][outputMask] =
                    matches - 8;
            }
        }

        std::cout
            << "\nLINEAR APPROXIMATION TABLE\n\n";

        std::cout << "In\\Out ";

        for (int outputMask = 0;
             outputMask < 16;
             outputMask++)
        {
            std::cout
                << std::setw(4)
                << outputMask;
        }

        std::cout << "\n";

        for (int inputMask = 0;
             inputMask < 16;
             inputMask++)
        {
            std::cout
                << std::setw(6)
                << inputMask
                << " ";

            for (int outputMask = 0;
                 outputMask < 16;
                 outputMask++)
            {
                std::cout
                    << std::setw(4)
                    << lat[inputMask][outputMask];
            }

            std::cout << "\n";
        }


        int bestInputMask = 0;
        int bestOutputMask = 0;
        int bestBias = 0;

        for (int inputMask = 1;
             inputMask < 16;
             inputMask++)
        {
            for (int outputMask = 1;
                 outputMask < 16;
                 outputMask++)
            {
                int currentBias =
                    std::abs(
                        lat[inputMask][outputMask]
                    );

                if (currentBias > bestBias)
                {
                    bestBias = currentBias;

                    bestInputMask =
                        inputMask;

                    bestOutputMask =
                        outputMask;
                }
            }
        }

        int signedBias =
            lat[bestInputMask][bestOutputMask];

        int matches =
            8 + signedBias;

        double probability =
            static_cast<double>(matches) / 16.0;

        std::cout
            << "\n============================================\n"
            << "STRONGEST LINEAR APPROXIMATION\n"
            << "============================================\n";

        std::cout
            << "\nInput mask:\n"
            << "Decimal: "
            << bestInputMask
            << "\nBinary:  "
            << std::bitset<4>(
                bestInputMask
            )
            << "\n";

        std::cout
            << "\nOutput mask:\n"
            << "Decimal: "
            << bestOutputMask
            << "\nBinary:  "
            << std::bitset<4>(
                bestOutputMask
            )
            << "\n";

        std::cout
            << "\nSigned bias: "
            << signedBias
            << "\n";

        std::cout
            << "Absolute bias: "
            << bestBias
            << "\n";

        std::cout
            << "Matching inputs: "
            << matches
            << " / 16\n";

        std::cout
            << "Probability: "
            << probability
            << "\n";

        std::cout
            << "Percentage: "
            << probability * 100.0
            << "%\n";

        std::cout
            << "\nInterpretation:\n";

        std::cout
            << "The selected XOR/parity of input bits "
            << "has a statistical relationship with "
            << "the selected XOR/parity of output bits.\n";

        std::cout
            << "\nFor a perfectly unbiased relation, "
            << "we would expect 8 matches out of 16.\n";
    }

    void runAllAnalysis() const
    {
        differentialAnalysis();

        linearAnalysis();
    }
};