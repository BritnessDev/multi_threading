/*
READ-WRITE LOCKS
*/


#include <iostream>
#include <numeric>
#include <thread>
#include <shared_mutex>
#include <chrono>
#include "mylib-random.hpp"
using namespace std;



volatile int resource = 0;
auto rwlock = std::shared_mutex();



void readFunc(int timeWait) {
    std::this_thread::sleep_for(std::chrono::seconds(timeWait));

    rwlock.lock_shared();

    cout << "read: " << resource << endl;

    rwlock.unlock_shared();
}



void writeFunc(int timeWait) {
    std::this_thread::sleep_for(std::chrono::seconds(timeWait));

    rwlock.lock();

    resource = mylib::RandInt::staticGet() % 100;
    cout << "write: " << resource << endl;

    rwlock.unlock();
}



int main() {
    constexpr int NUM_THREADS_READ = 10;
    constexpr int NUM_THREADS_WRITE = 4;
    constexpr int NUM_ARGS = 3;

    std::thread lstThRead[NUM_THREADS_READ];
    std::thread lstThWrite[NUM_THREADS_WRITE];
    int lstArg[NUM_ARGS];

    mylib::RandInt randInt(1, 1000);


    // INITIALIZE
    // lstArg = { 0, 1, 2, ..., NUM_ARG - 1 }
    std::iota(lstArg, lstArg + NUM_ARGS, 0);


    // CREATE THREADS
    for (auto&& th : lstThRead) {
        int arg = lstArg[ randInt.get() % NUM_ARGS ];
        th = std::thread(readFunc, arg);
    }

    for (auto&& th : lstThWrite) {
        int arg = lstArg[ randInt.get() % NUM_ARGS ];
        th = std::thread(writeFunc, arg);
    }


    // JOIN THREADS
    for (auto&& th : lstThRead) {
        th.join();
    }
    for (auto&& th : lstThWrite) {
        th.join();
    }


    return 0;
}
