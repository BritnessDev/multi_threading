#include <iostream>
#include <thread>

using namespace std;



void helloThread(int value) {
    cout << value << endl;
}



int main() {
    thread th1(helloThread, 1);
    thread th2(helloThread, 2);

    th1.join();
    th2.join();

    return 0;
}
