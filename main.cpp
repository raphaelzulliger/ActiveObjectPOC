#include "TestItf.h"
#include "Test.h"
#include "TestProxy.h"

#include <iostream>

int main() {
    CTest test;
    CTestProxy proxy(test);

    std::cout << proxy.GetUint32() << std::endl;
    std::cout << proxy.SetUint32(69) << std::endl;
    std::cout << proxy.Sum(1.0, 2.0) << std::endl;

    return 0;
}