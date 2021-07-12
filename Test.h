#pragma once

#include "TestItf.h"

class CTest : public CTestItf
{

        uint32_t GetUint32() override
        {
            return 66;
        }
        uint32_t SetUint32(uint32_t a) override
        {
            return a;
        }
        double Sum(double a, double b) override {
            return a + b;
        }

};
