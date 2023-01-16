/*
 * phichTiming.cpp
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
 *  Created on: 9 Sep 2022
 */

#include <iostream>
#include <cassert>
#include <ctime>

#include "lte_3gpp.h"

using namespace std;

int phichTimingTest_run(void* arg) {

    {
        std::time_t time = std::time(0);
        cout << "Program begins here: " << std::string(ctime(&time)) << endl;
    }

    // phich in subframe n will be associated with PUSCH in subframe n-k
    std::array<std::array<uint8_t, lte::consts::numSubframesPerRadioFrame>, lte::consts::numTddUlDlConfigurations> pusch2PhichOffset;

    for(uint32_t ulDlConfig = 0; ulDlConfig < lte::consts::numTddUlDlConfigurations; ++ulDlConfig) {
        for(uint32_t sfIdx = 0; sfIdx < lte::consts::numSubframesPerRadioFrame; ++sfIdx) {
            // printf("read pusch2PhichOffset.at(%d).at(%d)\n", ulDlConfig, sfIdx);
            pusch2PhichOffset.at(ulDlConfig).at(sfIdx) = 0;
        }
    }

    for(uint32_t ulDlConfig = 0; ulDlConfig < lte::consts::numTddUlDlConfigurations; ++ulDlConfig) {
        for(uint32_t sfIdx = 0; sfIdx < lte::consts::numSubframesPerRadioFrame; ++sfIdx) {
            // printf("read k_forTddConfigurations_T8P3_2.at(%d).at(%d)\n", ulDlConfig, sfIdx);
            auto const k = k_forTddConfigurations_T8P3_2.at(ulDlConfig).at(sfIdx);
            if (k != 0) {
                int puschSf = sfIdx-k;
                if (puschSf < 0) {
                    puschSf += 10;
                }
                // printf("write pusch2PhichOffset.at(%d).at(%d)\n", ulDlConfig, puschSf);
                assert(0 == pusch2PhichOffset.at(ulDlConfig).at(puschSf));
                pusch2PhichOffset.at(ulDlConfig).at(puschSf) = k;
            }
        }
    }

    for(uint8_t ulDlConfig = 0; ulDlConfig < lte::consts::numTddUlDlConfigurations; ulDlConfig++)
    {
        printf("{");
        for(uint8_t dlSfIdx = 0; dlSfIdx < lte::consts::numSubframesPerRadioFrame; dlSfIdx++) {
            printf("%d,", pusch2PhichOffset.at(ulDlConfig).at(dlSfIdx));
        }
        printf("},\n");
    }
    return(0);
}

