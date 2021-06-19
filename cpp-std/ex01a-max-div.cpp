#include <iostream>
#include "mytool-time.hpp"
using namespace std;



int main() {
    constexpr int RANGE_START = 1;
    constexpr int RANGE_STOP = 100000;

    int resValue = 0;
    int resNumDiv = 0;  // number of divisors of result

    auto tpStart = mytool::HiResClock::now();


    for (int i = RANGE_START; i <= RANGE_STOP; ++i) {
        int numDiv = 0;

        for (int j = i / 2; j > 0; --j)
            if (i % j == 0)
                ++numDiv;

        if (resNumDiv < numDiv) {
            resNumDiv = numDiv;
            resValue = i;
        }
    }


    auto timeSpan = mytool::HiResClock::getTimeSpan(tpStart);

    cout << "The integer which has largest number of divisors is " << resValue << endl;
    cout << "The largest number of divisor is " << resNumDiv << endl;
    cout << "Time elapsed = " << timeSpan.count() << endl;

    return 0;
}
