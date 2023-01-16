//============================================================================
// Name        : tests.cpp
// Author      : Manu T. Sreedharan
// Version     :
// Copyright   : Copyright (C) 2021 Manu T. Sreedharan
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include "test_class.h"

int daiComputation_run(void* arg);
int zcLogical2Physical_run(void* arg);
int phichTimingTest_run(void* arg);
int modulationMapper_run(void* arg);
int prachF4N_RA(void* arg);

int main() {

    {
        test nRATest(&prachF4N_RA);
        nRATest.run(nullptr);
    }
//    {
//        test modulationTest(&modulationMapper_run);
//        modulationTest.run(nullptr);
//    }
//    {
//        test daiComputation(&daiComputation_run);
//        daiComputation.run(nullptr);
//    }
//    {
//        test zcLogical2Physical(zcLogical2Physical_run);
//        zcLogical2Physical.run(nullptr);
//    }
//    {
//        test phichTimingTest(phichTimingTest_run);
//        phichTimingTest.run(nullptr);
//    }

	return 0;
}
