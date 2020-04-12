// This is a code playground where we answer misc questions
// and we'll type everything here (code and notes), so
// you'll have access to everything
#include <iostream> 
#include <utility>
struct S {
    int a, b;
    std::string c;
};

struct Time {
    int hour;
    int minute;
    int second;
};

int main() {
    S my_struct;
    my_struct.a = 1;
    my_struct.b = 2;
    my_struct.c = "hello";

    std::pair<int, double> p;
    p.first = 3;
    p.second = 3.14;

    std::tuple<int, double, int> t;
    std::get<0>(t) = 1;
    std::get<1>(t) = 3.14;
    std::get<2>(t) = 2;

    Time time;
    time.hour = 3;
    time.minute = 50;
    time.second = 0;

    auto i = 1L;
    auto pi = 3.1415;

    auto copy = time;

    auto pair_copy = p;

    auto num = 3.2;

    auto str = std::string("Hello");

    auto func = [](int a) {return a;};

}
