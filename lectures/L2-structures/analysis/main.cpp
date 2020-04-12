#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision

// the normal convention is that it's totally fine to use
// using namespace std; in the cpp file (not the .h file)
// Nevertheless, just out of habit, let's stick
// to using std's everywhere.

// forward declarations, so we don't have to implement them in order
struct Report;
std::pair<bool, Report> get_date_report(std::string country);
std::vector<std::tuple<std::string, size_t, size_t, double>> read_data();

/*
 * What's a struct? It's simply an open collection
 * of variables (which we call members).
 * 
 * If you are familar with classes, a struct is
 * a lightweight class where everything is by default 
 * public (in classes by default it is private)
 */
struct Report {
    size_t cases;
    size_t deaths;
    double increase_rate;
};

/*
 * We'll only talk about this function when
 * we discuss passing parameters.
 */
int main() {
    while (true) {
        std::string date;
        std::cout << "Enter a date (YYYY-MM-DD): ";
        getline(std::cin, date);
        if (date == "") return 0;
        auto [found, report] = get_date_report(date);
        if (found) {
            std::cout << "On " << date << " there were " << report.cases << " cases and "
                    << report.deaths << " deaths reported globally, an increase of " 
                    << std::setprecision(3) << report.increase_rate 
                    << "% from previous day." << std::endl;
        } else {
            std::cout << "The date " << date << " was not found in the database." << std::endl;
        }   
    } 
}

/*
 * Reads the data from file into a vector.
 * 
 * Parameters: date, represented as a std::string
 * Return value: pair of bool (if date entry was found) and found Report
 * 
 * Usage:
 *      auto [found, report] = get_date_report("2020-02-01");
 */
std::pair<bool, Report> get_date_report(std::string date) {
    std::vector< std::tuple<std::string, size_t, size_t, double> > data = read_data();
    
    // data is a vector of tuples (date, cases, deaths, increase_rate)
    for (const auto& [found_date, cases, deaths, increase_rate] : data) {
        if (found_date == date) {
            return {true, {cases, deaths, increase_rate}};
        }
    }
    return {false, {0, 0, 0.0}};
}

/*
 * Reads the data from file into a vector.
 * 
 * Parameters: none
 * Return value: vector of (country, cases, deaths, increase rate)
 * 
 * Usage:
 *      auto vector = read_data();
 */
std::vector<std::tuple<std::string, size_t, size_t, double>> read_data() {
    std::vector<std::tuple<std::string, size_t, size_t, double>> result;
    std::ifstream file("global.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        size_t cases, deaths;
        double increase_rate;
        iss >> date >> cases >> deaths >> increase_rate;
        result.push_back({date, cases, deaths, increase_rate});
    }
    return result;
}

