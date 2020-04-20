
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

double timeVecAccess(int numValues) {
    vector<int> v(numValues);

    time_type t1 = std::chrono::high_resolution_clock::now();

    for(int i = 0; i < numValues; ++i) {
        v[i] = i;
    }

    time_type t2 = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();

}

double timeDeqAccess(int numValues) {
    deque<int> d(numValues);
    time_type t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < numValues; ++i) {
        d[i] = i;
    }
    time_type t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
}



int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    GraphWindow w;
    w.setTitle("Vector vs Deque Access");

    vector<double> x;
    vector<double> yVecAccess;
    vector<double> yDeqAccess;

    const int numIterations = 20;
    const int startVal = 500;

    int numToInsert = startVal;
    for(int i = 0; i < numIterations; ++i) {
        cout << (100.0*i)/numIterations << "% complete" << endl;
        x.push_back(numToInsert);
        double timeToVecAcces= timeVecAccess(numToInsert);
        double timeToDeqAcces = timeDeqAccess(numToInsert);
        yVecAccess.push_back(timeToVecAcces);
        yDeqAccess.push_back(timeToDeqAcces);
        numToInsert *= 2;
    }

    printVector(yVecAccess);
    printVector(yDeqAccess);


    w.setXAxisRange(0, numToInsert);
    w.setYAxisRange(0, 6000);
    w.addGraph("vector access", "lime", x, yVecAccess);
    w.addGraph("deque access", "purple", x, yDeqAccess);
    w.show();
    return app.exec();
}



