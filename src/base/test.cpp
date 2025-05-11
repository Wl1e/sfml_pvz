#include <base/timer.hpp>
#include <iostream>

using namespace std;
using namespace demo;

void f(const string& s)
{
    cout << s << '\n';
}

int main()
{
    TimerQueue tq;
    tq.addTimer(0ms, []() { f("time1"); }, 200ms);
    while(true) {
        tq.update();
        cout << '.';
        this_thread::sleep_for(100ms);
    };
}