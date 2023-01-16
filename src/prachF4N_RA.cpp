/*
 * prachF4N_RA.cpp
 *
 *  <one line to give the program's name and a brief idea of what it does.>
 *  Copyright (C) 2023 Manu T. Sreedharan
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
 *  Created on: 16 Jan 2023
 */

#include <iostream>
#include <cassert>
#include <ctime>

#include "lte_3gpp.h"

using namespace std;

/*typedef struct {
    // frequency resource index within the considered time instance
    uint8_t freqResIdx;
    // uint8_t tRA0;
    lte::enums::prachOccasionTDDFrameRepMode tRA0;
    // uint8_t tRA1;
    lte::enums::prachOccasionTDDNhf tRA1;
    // startSubframe: the uplink subframe number where the preamble starts,
    // counting from 0 at the first uplink subframe between 2 consecutive
    // downlink-to-uplink switch points.
    uint8_t startSubframe;
} randomAccessPremableMappingFSType2Elem;*/

void updateNra(const randomAccessPremableMappingFSType2Elem& prach,
                uint32_t& nRA0,
                uint32_t& nRA1)
{
    if (lte::enums::prachOccasionTDDNhf::nHf0 == prach.tRA1) {
        nRA0++;
    } else if (lte::enums::prachOccasionTDDNhf::nHf1 == prach.tRA1) {
        nRA1++;
    }
}

int prachF4N_RA(void* arg)
{
    {
        std::time_t time = std::time(0);
        cout << "Program begins here: " << std::string(ctime(&time)) << endl;
    }


    auto const& preambleMappings = randomAccessPreambleMappingFSType2_T5P7P1_4();

    uint32_t tddCfg = 0;
    cout << "Computing N_RA values for tddCfg = " << tddCfg << endl;

    for (uint8_t prachCfgIdx = 48; prachCfgIdx < 58; ++prachCfgIdx) {
        for (uint8_t frameIdx = 0; frameIdx < 2; ++frameIdx) {
            auto const& prachOccasions = preambleMappings[prachCfgIdx].second[tddCfg];
            uint32_t nRA0 = 0;
            uint32_t nRA1 = 0;
            for (auto const& prach : prachOccasions) {
                if (lte::enums::prachOccasionTDDFrameRepMode::any == prach.tRA0) {
                    updateNra(prach, nRA0, nRA1);
                } else if ((lte::enums::prachOccasionTDDFrameRepMode::even == prach.tRA0) && (0 == frameIdx)) {
                    updateNra(prach, nRA0, nRA1);
                } else if ((lte::enums::prachOccasionTDDFrameRepMode::odd == prach.tRA0) && (1 == frameIdx)) {
                    updateNra(prach, nRA0, nRA1);
                }
            }
            cout << "[" << nRA0 << "," << nRA1 << "],";
        }
        cout << endl;
    }

    tddCfg = 3;
    cout << "Computing N_RA values for tddCfg = " << tddCfg << endl;

    for (uint8_t prachCfgIdx = 48; prachCfgIdx < 58; ++prachCfgIdx) {
        for (uint8_t frameIdx = 0; frameIdx < 2; ++frameIdx) {
            auto const& prachOccasions = preambleMappings[prachCfgIdx].second[tddCfg];
            uint32_t nRA0 = 0;
            uint32_t nRA1 = 0;
            for (auto const& prach : prachOccasions) {
                if (lte::enums::prachOccasionTDDFrameRepMode::any == prach.tRA0) {
                    updateNra(prach, nRA0, nRA1);
                } else if ((lte::enums::prachOccasionTDDFrameRepMode::even == prach.tRA0) && (0 == frameIdx)) {
                    updateNra(prach, nRA0, nRA1);
                } else if ((lte::enums::prachOccasionTDDFrameRepMode::odd == prach.tRA0) && (1 == frameIdx)) {
                    updateNra(prach, nRA0, nRA1);
                }
            }
            cout << "[" << nRA0 << "," << nRA1 << "],";
        }
        cout << endl;
    }

    {
        std::time_t time = std::time(0);
        cout << "Program ends here: " << std::string(ctime(&time)) << endl;
    }

    return(0);
}


