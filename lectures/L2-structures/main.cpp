#include <iostream>
#include <utility>
#include <tuple>
#include <array>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

struct Report;

std::pair<bool, Report> get_country_report(std::string country);
std::vector<std::tuple<std::string, size_t, size_t, double>> read_data();

struct Report {
    size_t cases;
    size_t deaths;
    double increase_rate;
};

int main() {
    while (true) {
        std::string date;
        std::cout << "Enter a date (YYYY/MM/DD): ";
        getline(std::cin, date);
        if (date == "") return 0;
        auto [found, report] = get_country_report(date);
        if (found) {
            std::cout << "On " << date << " there were "
                    << report.cases << " cases and "
                    << report.deaths << " deaths reported globally, an increase of " 
                    << std::setprecision(3) << report.increase_rate 
                    << "% from previous day." << std::endl;
        } else {
            std::cout << "The date " << date << " was not found in the database." << std::endl;
        }   
    }
    
}

std::pair<bool, Report> get_country_report(std::string date) {
    std::vector<std::tuple<std::string, size_t, size_t, double>> data = read_data();
    for (size_t i = 0; i < data.size(); ++i) {
        auto entry = data[i];
        if (std::get<0>(entry) == date) {
            auto [date_name, cases, deaths, increase_rate] = entry;
            Report result{cases, deaths, increase_rate};
            return {true, result};
        }
    }

    return {false, {}};
}


std::vector<std::tuple<std::string, size_t, size_t, double>> read_data() {
    std::vector<std::tuple<std::string, size_t, size_t, double>> result;
    std::ifstream file("global.txt");
    std::string line;
    while (getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        size_t cases, deaths;
        double increase_rate;
        iss >> date >> cases >> deaths >> increase_rate;
        result.push_back({date, cases, deaths, increase_rate});
    }
    return result;
}
