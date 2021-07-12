# Active Object C++ (POC)

POC C++ Implementation of the [Active Object pattern](http://www.diranieh.com/DP/POSA_ActiveObject.htm) that minimizes boilerplate code using compile time reflection.

Note: This is a POC and it is *NOT* properly working!!! It was created to see if something like that would be feasible. And yes, I believe this work could be continued and end up as a production ready library. Although, right now, I do *not* intend to do that.

Note: Why do I make it public then? Because for my very own reference and because it may inspire others.

## Quick start

Prerequisites: This project uses CMake and Conan (both require to be pretty up-to-date)

Build it:

```sh
mkdir build && \
cd build && \
cmake .. -DCMAKE_BUILD_TYPE=Debug && \
cmake --build . --config Debug
```

Run it:

```sh
./bin/ActiveObject
```

(There's actually not too much to see - but you may want to run it anyway ;-))

## Introduction

This project was hacked together because I was curious if it's possible to avoid most of the "dispatching boilerplate code" that's usually written when forwarding calls between the proxy and the actual implementation.

Right now (2021) it seems to be impossible to use "compile time reflection" using the C++ compiler - unless patching compilers. Therefore, this POC uses "macro magic" to capture function name and parameters and forwards it from a "proxy" to the "implementation". Credits for that goes to the author of one of the answers here https://stackoverflow.com/questions/44758329/c-or-macro-magic-to-generate-method-and-forward-arguments.

Because of that, the code must be "poluted" slightly by using macros. But the code almost looks like non-macro code, so it's pretty "ok". Here's the "interface", the "proxy" and the actual implementation look like:

```c++
// The interface
class CTestItf
{
    public:
        virtual ~CTestItf() = default;

        virtual uint32_t GetUint32() = 0;
        virtual uint32_t SetUint32(uint32_t a) = 0;
        virtual double Sum(double a, double b) = 0;

};

// The proxy implementation
class CTestProxy : public CTestItf
{
...
        MAGICAL_MACRO(uint32_t, GetUint32);
        MAGICAL_MACRO(uint32_t, SetUint32, uint32_t a);
        MAGICAL_MACRO(double, Sum, double a, double b);
...
};

// The actual implementation
class CTest : public CTestItf
{
        uint32_t GetUint32() override {
            return 66;
        }
        uint32_t SetUint32(uint32_t a) override {
            return a;
        }
        double Sum(double a, double b) override {
            return a + b;
        }
};
```
