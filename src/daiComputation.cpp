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

int daiComputation_run(void* arg) {

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
        // we should be able to derive uplinkAssociationIndex_T7P3_Y from k_forTddConfigurations_T8_2, and vis-a-vis.
        printf("Begin testing uplinkAssociationIndex_T7P3_Y and k_forTddConfigurations_T8_2\n");
        for(uint8_t ulDlConfig = 0; ulDlConfig < lte::consts::numTddUlDlConfigurations; ulDlConfig++) {
            for(uint8_t sfIdx = 0; sfIdx < lte::consts::numSubframesPerRadioFrame; ++sfIdx) {
                if (uplinkAssociationIndex_T7P3_Y.at(ulDlConfig).at(sfIdx) != 0) {
                    // if we come here, it must be an uplink subframe!
                    auto sfType = tddUlDlConfigurations_T4P2_2.at(ulDlConfig).second.at(size_t(sfIdx));
                    assert(lte::enums::tddSubframeType::U == sfType);

                    int tempSfIfx = int(sfIdx) - int(uplinkAssociationIndex_T7P3_Y.at(ulDlConfig).at(sfIdx));
                    while(tempSfIfx < 0) {
                        tempSfIfx += 10;
                    }
                    assert(tempSfIfx >= 0);
                    assert(tempSfIfx < 10);
                    const uint8_t dlSfIdx = uint8_t(tempSfIfx);
                    sfType = tddUlDlConfigurations_T4P2_2.at(ulDlConfig).second.at(size_t(dlSfIdx));
                    assert(lte::enums::tddSubframeType::U != sfType);

                    // the value from k_forTddConfigurations_T8_2 at dlSfIdx must match!
                    assert(uplinkAssociationIndex_T7P3_Y.at(ulDlConfig).at(sfIdx) == k_forTddConfigurations_T8_2.at(ulDlConfig).at(dlSfIdx));
                }
            }
        }
        for(uint8_t ulDlConfig = 1; ulDlConfig < lte::consts::numTddUlDlConfigurations; ulDlConfig++) {
            for(uint8_t dlSfIdx = 0; dlSfIdx < lte::consts::numSubframesPerRadioFrame; ++dlSfIdx) {

                if (k_forTddConfigurations_T8_2.at(ulDlConfig).at(dlSfIdx) != 0) {
                    // if we come here, it must be not an uplink subframe!
                    auto sfType = tddUlDlConfigurations_T4P2_2.at(ulDlConfig).second.at(size_t(dlSfIdx));
                    assert(lte::enums::tddSubframeType::U != sfType);

                    int tempSfIfx = int(dlSfIdx) + int(k_forTddConfigurations_T8_2.at(ulDlConfig).at(dlSfIdx));
                    while(tempSfIfx > 10) {
                        tempSfIfx -= 10;
                    }
                    assert(tempSfIfx >= 0);
                    assert(tempSfIfx < 10);
                    const uint8_t ulSfIdx = uint8_t(tempSfIfx);
                    sfType = tddUlDlConfigurations_T4P2_2.at(ulDlConfig).second.at(size_t(ulSfIdx));
                    assert(lte::enums::tddSubframeType::U == sfType);

                    // the value from k_forTddConfigurations_T8_2 at dlSfIdx must match!
                    assert(uplinkAssociationIndex_T7P3_Y.at(ulDlConfig).at(ulSfIdx) == k_forTddConfigurations_T8_2.at(ulDlConfig).at(dlSfIdx));
                }
            }
        }
        printf("End testing uplinkAssociationIndex_T7P3_Y and k_forTddConfigurations_T8_2\n");
    }

    // set every element in pdschHarqOffset to zero.
    for(uint32_t ulDlConfig = 0; ulDlConfig < lte::consts::numTddUlDlConfigurations; ++ulDlConfig) {
        for(uint32_t sfIdx = 0; sfIdx < lte::consts::numSubframesPerRadioFrame; ++sfIdx) {
            pdschHarqOffset.at(ulDlConfig).at(sfIdx) = 0;
        }
    }

    for(uint32_t ulDlConfig = 0; ulDlConfig < lte::consts::numTddUlDlConfigurations; ++ulDlConfig) {
        for(uint32_t sfIdx = 0; sfIdx < lte::consts::numSubframesPerRadioFrame; ++sfIdx) {
            auto dlAssociationSet = downlinkAssociationSet_T10P1P3A_1.at(ulDlConfig).at(sfIdx);
            for(const auto k : dlAssociationSet) {
                {
                    auto sfType = tddUlDlConfigurations_T4P2_2.at(ulDlConfig).second.at(size_t(sfIdx));
                    assert(lte::enums::tddSubframeType::U == sfType);
                }
                int dlSfIdx = int(sfIdx) - int(k);
                while(dlSfIdx < 0) {
                    dlSfIdx += 10;
                }
                // auto sfType = tddUlDlConfigurations_T4P2_2.at(ulDlConfig).second.at(size_t(dlSfIdx));
                // if(lte::enums::tddSubframeType::U == sfType) {
                //     printf("error at ulDlConfig = %u, sfIdx = %u, k = %hu\n", ulDlConfig, sfIdx, k);
                //     assert(0);
                // }

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
