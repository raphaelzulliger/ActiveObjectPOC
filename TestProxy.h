#pragma once

#include "TestItf.h"
#include "MagicMacro.h"

// HACK: MPMCQueue complains about std::function not being no-throw copy-constructible. Since this is really just a
// POC, I don't care... (well, I still feel bad of course, but I do it never the less): Just disable the
// `static_assert`s
#define static_assert(...);
#include <rigtorp/MPMCQueue.h>

#include <functional>
#include <future>
#include <cassert>
#include <iostream>


class CTestProxy : public CTestItf
{
        using tQueueType = std::function<double()>;
    public:
        CTestProxy(CTestItf& obj)
            :   _obj(obj)
        {}

        MAGICAL_MACRO(uint32_t, GetUint32);
        MAGICAL_MACRO(uint32_t, SetUint32, uint32_t a);
        MAGICAL_MACRO(double, Sum, double a, double b);

    private:
        CTestItf& _obj;
        rigtorp::MPMCQueue<tQueueType> _q{32};
};
