#include <iostream>
#include <vector>
#include <chrono>
#include <mutex>
#include <thread>

using std::cout;    using std::endl;
using std::string;  using std::vector;
using std::thread;

const size_t NUM_THREADS = 10;
static std::mutex mtx;

void greet(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
	std::lock_guard<std::mutex> lg(mtx);
    cout << "Thread " << id << ": Hello world!" << endl;
}

int main() {
    cout << "Greetings from my threads..." << endl;

    // Create threads
	vector<thread> threads;
	for (size_t i = 0; i < NUM_THREADS; ++i) {
		threads.push_back(thread(greet, i));
	}

    // Wait for threads to finish
	for (std::thread& t: threads) {
	    t.join();
	}

    cout << "All greetings done!" << endl;

    return 0;
}
