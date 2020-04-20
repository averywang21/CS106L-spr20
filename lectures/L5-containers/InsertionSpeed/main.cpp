#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <chrono>
#include "graphwindow.h"

using std::cout;    using std::endl;
using std::vector;  using std::deque;

void printVector(const vector<double>& vec) {
    cout << "{";
    for(auto i : vec) {
        cout << i << " ";
    }
    cout << "}" << endl;
}


using duration_type = std::chrono::milliseconds::rep;
using time_type = std::chrono::high_resolution_clock::time_point;

double timePushBack(int numValues) {
    vector<int> v;
    time_type t1 = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < numValues; ++i) {
        v.push_back(i);
    }

    time_type t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
}

double timePushFront(int numValues) {
    vector<int> v;
    time_type t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < numValues; ++i) {
        v.insert(v.begin(),i);
    }
    time_type t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
}



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GraphWindow w;
    w.setTitle("PushBack vs PushFront");

    vector<double> x;
    vector<double> yPushBack;
    vector<double> yPushFront;

    const int numIterations = 10;
    const int startVal = 500;

    int numToInsert = startVal;
    for(int i = 0; i < numIterations; ++i) {
        cout << (100.0*i)/numIterations << "% complete" << endl;
        x.push_back(numToInsert);
        double timeToPushBack = timePushBack(numToInsert);
        double timeToPushFront = timePushFront(numToInsert);
        yPushBack.push_back(timeToPushBack);
        yPushFront.push_back(timeToPushFront);
        numToInsert *= 2;
    }

    printVector(yPushBack);
    printVector(yPushFront);


    w.setXAxisRange(0, numToInsert);
    w.setYAxisRange(0, 6000);
    w.addGraph("PushBack", "lime", x, yPushBack);
    w.addGraph("PushFront", "purple", x, yPushFront);
    w.show();
    return app.exec();

}




