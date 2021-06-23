/*
DATA RACE

Version 01 - without multithreading.
*/


#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
using namespace std;



int getResult(int N) {
    vector<bool> a;
    a.resize(N + 1, false);

    for (int i = 1; i <= N; ++i)
        if (0 == i % 2 || 0 == i % 3)
            a[i] = true;

    // result = sum of a (i.e. count numbers of true values in a)
    int result = std::accumulate(a.begin(), a.end(), 0);
    return result;
}



int main() {
    constexpr int N = 8;

    int result = getResult(N);

    cout << "Numbers of integers that are divisible by 2 or 3 is: " << result << endl;
    return 0;
}
