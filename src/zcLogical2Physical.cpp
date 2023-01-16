/*
 * zcLogical2Physical.cpp
 *
 *  Some sanity checks on ZC logical to physical root table
 *  Copyright (C) 2021 Manu T. Sreedharan
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
 *  Created on: 10 Dec 2021
 */



#include <iostream>
#include <cassert>
#include <ctime>

#include "lte_3gpp.h"

using namespace std;

int zcLogical2Physical_run(void* arg) {
    // const auto& zcLogical2PhysicalTable = rootZCSequenceOrder_formats0_3;

    std::vector<uint16_t> zcLogical2PhysicalArray(838, 0xffff);
    std::vector<uint16_t> zcPhysical2PhysicalArray(838, 0xffff);

    uint32_t logRootIdx = 0;
    for(uint32_t rowIdx = 0; rowIdx < rootZCSequenceOrder_formats0_3.size(); ++rowIdx) {
        const auto& tableRow = rootZCSequenceOrder_formats0_3[rowIdx];

        const auto& logicalRootLimits = tableRow.first;
        const auto& physicalRootsArray = tableRow.second;

        assert(logRootIdx == logicalRootLimits.first);
        assert(physicalRootsArray.size() == 1 + logicalRootLimits.second - logicalRootLimits.first);

        uint32_t arrayIdx = 0;
        for(; logRootIdx <= logicalRootLimits.second; ++logRootIdx) {
            const auto phyRootIdx = physicalRootsArray.at(arrayIdx++);

            assert(zcLogical2PhysicalArray.at(logRootIdx) == 0xffff);
            zcLogical2PhysicalArray.at(logRootIdx) = phyRootIdx;
            assert(zcPhysical2PhysicalArray.at(phyRootIdx-1) == 0xffff);
            zcPhysical2PhysicalArray.at(phyRootIdx-1) = logRootIdx;
        }
    }

    for(uint32_t rootIdx = 0; rootIdx < zcLogical2PhysicalArray.size(); rootIdx++) {
        auto pRootIdx = zcLogical2PhysicalArray.at(rootIdx);
        auto lRootIdx = zcPhysical2PhysicalArray.at(pRootIdx-1);
        printf("%03d, %03d, %03d\n", rootIdx, pRootIdx, lRootIdx);
    }

    return(0);
}
