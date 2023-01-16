/*
 * modulationMapper.cpp
 *
 *  <one line to give the program's name and a brief idea of what it does.>
 *  Copyright (C) 2022 Manu T. Sreedharan
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 *  Created on: 16 Dec 2022
 */


#include <iostream>
#include <cassert>
#include <ctime>
#include <math.h>

#include "lte_3gpp.h"

using namespace std;


void qam256test()
{
    uint16_t constexpr numBitsPerSym = 8;
    uint16_t constallationSize = 1;
    // double constexpr scaling = 1.0/std::sqrt(double(170.0));

    for (uint16_t bitIdx = 0; bitIdx < numBitsPerSym; ++bitIdx) {
        constallationSize *= 2;
    }

    for (uint16_t val = 0; val < constallationSize; ++val) {

        std::array<int32_t, numBitsPerSym> bits;
        for(uint8_t bitIdx = 0; bitIdx < numBitsPerSym; ++bitIdx) {
            uint8_t shift = ((numBitsPerSym - 1) - bitIdx);
            bits[bitIdx] = (val & (1 << shift)) ? 1 : 0;
        }

        int16_t realC, imagC;
        realC = (1 - (2.0*bits[6]));
        imagC = (1 - (2.0*bits[7]));

        realC = (1 - (2.0*bits[4]))*(2 - realC);
        imagC = (1 - (2.0*bits[5]))*(2 - imagC);

        realC = (1 - (2.0*bits[2]))*(4 - realC);
        imagC = (1 - (2.0*bits[3]))*(4 - imagC);

        realC = (1 - (2.0*bits[0]))*(8 - realC);
        imagC = (1 - (2.0*bits[1]))*(8 - imagC);

        auto const map = modulationMapper256QAM[val];
        assert(map.first == val);
        assert(map.second.first == realC);
        assert(map.second.second == imagC);

        printf("%d, %d, %d, %d, %d\n", val, realC, imagC, map.second.first, map.second.second);
    }
}

void qam64test()
{
    uint16_t constexpr numBitsPerSym = 6;
    uint16_t constallationSize = 1;

    for (uint16_t bitIdx = 0; bitIdx < numBitsPerSym; ++bitIdx) {
        constallationSize *= 2;
    }

    for (uint16_t val = 0; val < constallationSize; ++val) {

        std::array<int32_t, numBitsPerSym> bits;
        for(uint8_t bitIdx = 0; bitIdx < numBitsPerSym; ++bitIdx) {
            uint8_t shift = ((numBitsPerSym - 1) - bitIdx);
            bits[bitIdx] = (val & (1 << shift)) ? 1 : 0;
        }

        int16_t realC, imagC;
        realC = (1 - (2.0*bits[4]));
        imagC = (1 - (2.0*bits[5]));

        realC = (1 - (2.0*bits[2]))*(2 - realC);
        imagC = (1 - (2.0*bits[3]))*(2 - imagC);

        realC = (1 - (2.0*bits[0]))*(4 - realC);
        imagC = (1 - (2.0*bits[1]))*(4 - imagC);

        auto const map = modulationMapper64QAM[val];
        assert(map.first == val);
        assert(map.second.first == realC);
        assert(map.second.second == imagC);

        printf("%d, %d, %d, %d, %d\n", val, realC, imagC, map.second.first, map.second.second);
    }
}

void qam16test()
{
    uint16_t constexpr numBitsPerSym = 4;
    uint16_t constallationSize = 1;

    for (uint16_t bitIdx = 0; bitIdx < numBitsPerSym; ++bitIdx) {
        constallationSize *= 2;
    }

    for (uint16_t val = 0; val < constallationSize; ++val) {

        std::array<int32_t, numBitsPerSym> bits;
        for(uint8_t bitIdx = 0; bitIdx < numBitsPerSym; ++bitIdx) {
            uint8_t shift = ((numBitsPerSym - 1) - bitIdx);
            bits[bitIdx] = (val & (1 << shift)) ? 1 : 0;
        }

        int16_t realC, imagC;
        realC = (1 - (2.0*bits[2]));
        imagC = (1 - (2.0*bits[3]));

        realC = (1 - (2.0*bits[0]))*(2 - realC);
        imagC = (1 - (2.0*bits[1]))*(2 - imagC);

        auto const map = modulationMapper16QAM[val];
        printf("%d, %d, %d, %d, %d\n", val, realC, imagC, map.second.first, map.second.second);

        assert(map.first == val);
        assert(map.second.first == realC);
        assert(map.second.second == imagC);

    }
}

void qpsktest()
{
    uint16_t constexpr numBitsPerSym = 2;
    uint16_t constallationSize = 1;

    for (uint16_t bitIdx = 0; bitIdx < numBitsPerSym; ++bitIdx) {
        constallationSize *= 2;
    }

    for (uint16_t val = 0; val < constallationSize; ++val) {

        std::array<int32_t, numBitsPerSym> bits;
        for(uint8_t bitIdx = 0; bitIdx < numBitsPerSym; ++bitIdx) {
            uint8_t shift = ((numBitsPerSym - 1) - bitIdx);
            bits[bitIdx] = (val & (1 << shift)) ? 1 : 0;
        }

        int16_t realC, imagC;
        realC = (1 - (2.0*bits[0]));
        imagC = (1 - (2.0*bits[1]));

        auto const map = modulationMapperQPSK[val];
        assert(map.first == val);
        assert(map.second.first == realC);
        assert(map.second.second == imagC);

        printf("%d, %d, %d, %d, %d\n", val, realC, imagC, map.second.first, map.second.second);
    }
}

int modulationMapper_run(void* arg) {

    std::time_t time = std::time(0);
    {
        cout << "Program begins here: " << std::string(ctime(&time)) << endl;
    }

    cout << "QAM 256 begins here: " << std::string(ctime(&time)) << endl;
    qam256test();

    cout << "QAM 64 begins here: " << std::string(ctime(&time)) << endl;
    qam64test();

    cout << "QAM 16 begins here: " << std::string(ctime(&time)) << endl;
    qam16test();

    cout << "QPSK  begins here: " << std::string(ctime(&time)) << endl;
    qpsktest();

    {
        std::time_t time = std::time(0);
        cout << "Program ends here: " << std::string(ctime(&time)) << endl;
    }
    return(0);
}

