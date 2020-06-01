#include <iostream>

using std::cout;    using std::endl;

/*
 * EXTENSION CHALLENGE:
 * Make our MySharedPtr class thread-safe (i.e. "correctly synchronized")!
 * 
 * Hint: Take a look at the atomic library in the STL. You can also read:
 * https://herbsutter.com/2014/01/13/gotw-95-solution-thread-safety-and-synchronization/
 * for more information.
 */
class Counter {
public:
    Counter() : counter(0) {}

    Counter(const Counter&) = delete;
    Counter& operator=(const Counter&) = delete;

    ~Counter() {}

    void reset() {
        counter = 0;
    }

    size_t get() {
        return counter;
    }

    // Overload increment operators
    void operator++() {
        ++counter;
    }

    void operator++(int) {
        ++counter;
    }

    // Overload decrement operators
    void operator--() {
        --counter;
    }

    void operator--(int) {
        --counter;
    }

    // Overload stream operator
    friend std::ostream& operator<<(std::ostream& os, const Counter& c) {
        os << "Counter val: " << c.counter << endl;
        return os;
    }
private:
    size_t counter;
};

template <typename T>
class MySharedPtr {
public:
    // Constructor
    explicit MySharedPtr(T* ptr = nullptr) : ptr(ptr), pcount(new Counter()) {
        if (ptr) {
            (*pcount)++;
        }
    }

    // Copy Constructor
    MySharedPtr(const MySharedPtr<T>& sp) : ptr(sp.ptr), pcount(sp.pcount) {
        if (ptr) {
            (*pcount)++;
        }
    }

    // Copy Assignment

    // * and -> operators

    // Destructor

    friend std::ostream& operator<<(std::ostream& os, MySharedPtr<T>& sp) {
        os << "Value pointed at: " << *sp << endl;
        os << *(sp.pcount) << endl;
        return os;
    }

private:
    T* ptr;
    Counter* pcount;
};

int main() {
    MySharedPtr<int> p1(new int(137));
    cout << "Shared pointers p1: " << endl;
    cout << p1;

    {
        MySharedPtr<int> p2 = p1;
        cout << "Shared pointers p1 and p2: " << endl;
        cout << p1 << p2;
    }

    cout << "Shared pointers p1: " << endl;
    cout << p1;
}
