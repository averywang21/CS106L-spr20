#include <iostream>     // for cout, cin
#include <utility>      // for pair
#include <tuple>        // for tuple
#include <array>        // for array
#include <vector>       // for vector
#include <fstream>      // for ifstream
#include <sstream>      // for istringstream
#include <iomanip>      // for setprecision

int main() {
    // not much to run here
}

// return type: string, notice can’t use auto for parameter
auto calculateSum(const std::vector<string>& v) { 
  auto multiplier = 2.4; 								// double 
  auto name = "Ito-En"; 								// char* (c-string)
  auto betterName1 = std::string{"Ito-En"};				// string
  const auto& betterName2 = std::string{"Ito-En"};		// const string&
  auto copy = v; 										// vector<string>
  auto& refMult = multiplier; 						    // double&	 
  auto func = [](auto i) {return i*2;};				    // ???

  return betterName1;
}

struct Discount {
  double discountFactor;
  int expirationDate;
  std::string nameOfDiscount;
}; // don’t forget this semicolon :/


void structures() {
        // make_pair/tuple (C++11) automatically deduces the type!
    auto prices = std::make_pair(3.4, 5); 			// pair<double, int>
    auto values = std::make_tuple(3, 4, "hi"); 	    // tuple<int, int, char*>

    // access via get/set
    prices.first = prices.second; 			        // prices = {5.0, 5};
    std::get<0>(values) = std::get<1>(values);	    // values = {4, 4, “hi”};

    // structured binding (C++17) – extract each component
    auto [a, b] = prices;						    // a, b are copies of 5.0 and 5
    const auto& [x, y, z] = values;		            // x, y, z are const references
                                                    // to the 4, 4, and “hi”.

    // Call to Discount’s constructor or initializer list
    auto coupon1 = Discount{0.9, 30, "New Years"};	
    Discount coupon2 {0.75, 7, "Valentine’s Day"};

    coupon1.discountFactor = 0.8;					
    coupon2.expirationDate = coupon1.expirationDate; 

    // structured binding (C++17) – extract each component
    auto [factor, date, name] = coupon1;
}






