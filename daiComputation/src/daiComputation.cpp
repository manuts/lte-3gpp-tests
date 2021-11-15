//============================================================================
// Name        : daiComputation.cpp
// Author      : Manu T. Sreedharan
// Version     :
// Copyright   : Copyright (C) 2021 Manu T. Sreedharan
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cassert>
#include <ctime>

#include "lte_3gpp.h"

using namespace std;

int main() {

    {
        std::time_t time = std::time(0);
        cout << "Program begins here: " << std::string(ctime(&time)) << endl;
    }

    // suppose a PDSCH is sent in subframe n, HARQ feedback for this PDSCH will be sent in subframe n+k.
    // The table below provides the value of k.
    // This table is a derivative of downlinkAssociationSet_T10P1P3P1_1;
    std::array<std::array<uint8_t, lte::consts::numSubframesPerRadioFrame>, lte::consts::numTddUlDlConfigurations> pdschHarqOffset;

    // set every element in pdschHarqOffset to zero.
    for(uint32_t ulDlConfig = 0; ulDlConfig < lte::consts::numTddUlDlConfigurations; ++ulDlConfig) {
        for(uint32_t sfIdx = 0; sfIdx < lte::consts::numSubframesPerRadioFrame; ++sfIdx) {
            pdschHarqOffset.at(ulDlConfig).at(sfIdx) = 0;
        }
    }

    for(uint32_t ulDlConfig = 0; ulDlConfig < lte::consts::numTddUlDlConfigurations; ++ulDlConfig) {
        for(uint32_t sfIdx = 0; sfIdx < lte::consts::numSubframesPerRadioFrame; ++sfIdx) {
            auto dlAssociationSet = downlinkAssociationSet_T10P1P3P1_1.at(ulDlConfig).at(sfIdx);
            for(const auto k : dlAssociationSet) {
                {
                    auto sfType = tddUlDlConfigurations_T4P2_2.at(ulDlConfig).second.at(size_t(sfIdx));
                    assert(lte::enums::tddSubframeType::U == sfType);
                }
                int dlSfIdx = int(sfIdx) - int(k);
                while(dlSfIdx < 0) {
                    dlSfIdx += 10;
                }
                auto sfType = tddUlDlConfigurations_T4P2_2.at(ulDlConfig).second.at(size_t(dlSfIdx));
                if(lte::enums::tddSubframeType::U == sfType) {
                    printf("error at ulDlConfig = %u, sfIdx = %u, k = %hu\n", ulDlConfig, sfIdx, k);
                    assert(0);
                }

                assert(0 == pdschHarqOffset.at(ulDlConfig).at(size_t(dlSfIdx)));
                pdschHarqOffset.at(ulDlConfig).at(size_t(dlSfIdx)) = k;
            }
        }
    }

    for(uint8_t ulDlConfig = 0; ulDlConfig < lte::consts::numTddUlDlConfigurations; ulDlConfig++)
    {
        printf("{");
        for(uint8_t dlSfIdx = 0; dlSfIdx < lte::consts::numSubframesPerRadioFrame; dlSfIdx++) {
            {
                auto sfType = tddUlDlConfigurations_T4P2_2.at(ulDlConfig).second.at(size_t(dlSfIdx));
                assert((lte::enums::tddSubframeType::U == sfType) || (0 != pdschHarqOffset.at(ulDlConfig).at(dlSfIdx)));
            }

            printf("%d,", pdschHarqOffset.at(ulDlConfig).at(dlSfIdx));
        }
        printf("},\n");
    }


    {
        std::time_t time = std::time(0);
        cout << "Program ends here: " << std::string(ctime(&time)) << endl;
    }
	return 0;
}
