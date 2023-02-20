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

int specialSubframeConfigurations_run(void* arg) {

    {
        std::time_t time = std::time(0);
        cout << "Program begins here: " << std::string(ctime(&time)) << endl;
    }

    {
        // DL normal CP case; UL normal CP
        const lte::enums::cpType dlCpType = lte::enums::cpType::NORMAL;
        const lte::enums::cpType ulCpType = lte::enums::cpType::NORMAL;
        cout << "DL normal CP, UL normal CP " << endl;
        uint8_t numUlSymbols = 0;
        uint8_t numDlSymbols = 0;
        for (uint8_t specialSfCfg = 0; specialSfCfg < 11; ++specialSfCfg) {
            [[maybe_unused]] specialSubframeBreakdown_t breakDown;
            breakDown = specialSubframeConfiguration_T4P2_1(specialSfCfg,
                                                            dlCpType,
                                                            ulCpType,
                                                            numDlSymbols,
                                                            numUlSymbols);
            cout << uint32_t(numDlSymbols) << ", ";
        }
        cout << endl;
    }

    {
        // DL normal CP case; UL normal CP
        const lte::enums::cpType dlCpType = lte::enums::cpType::EXTENDED;
        const lte::enums::cpType ulCpType = lte::enums::cpType::NORMAL;
        cout << "DL normal EXT, UL normal CP " << endl;
        uint8_t numUlSymbols = 0;
        uint8_t numDlSymbols = 0;
        for (uint8_t specialSfCfg = 0; specialSfCfg < 8; ++specialSfCfg) {
            [[maybe_unused]] specialSubframeBreakdown_t breakDown;
            breakDown = specialSubframeConfiguration_T4P2_1(specialSfCfg,
                                                            dlCpType,
                                                            ulCpType,
                                                            numDlSymbols,
                                                            numUlSymbols);
            cout << uint32_t(numDlSymbols) << ", ";
        }
        cout << endl;
    }

    {
        std::time_t time = std::time(0);
        cout << "Program ends here: " << std::string(ctime(&time)) << endl;
    }
	return 0;
}
