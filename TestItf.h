#pragma once

#include <cstdint>

class CTestItf
{
    public:
        virtual ~CTestItf() = default;

        virtual uint32_t GetUint32() = 0;
        virtual uint32_t SetUint32(uint32_t a) = 0;
        virtual double Sum(double a, double b) = 0;

};
