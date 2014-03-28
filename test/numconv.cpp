
#include <iostream>
#include <iomanip>

#include "readfile.hpp"
#include "timer.hpp"
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <jsxx/core/handlers.hpp>

using std::cout;
using std::endl;

int main(/*int argc, char const* argv[]*/)
{
//  if (argc < 3) {
//    cout << "error. missing input argument. usage: prog <numrun> <test_string>\n";
//    return 0; // tmp
//  }

//  int NUM_RUN = atoi(argv[1]);
//  std::string s = std::string(argv[2]);
//  auto beg = s.begin();

//  cout << "string: " << s << "\n";

//  {
//    std::vector<int> items;
//    int res;
//    try {
//      jsxx::timer t;
//      for (int i = 0; i < NUM_RUN; ++i) {
//        t.start();

//        res = jsxx::string_to_integer<int>(beg, s.end());

//        t.stop();
//        items.push_back(t.ms());
//      }
//    }
//    catch (std::exception& e) {
//      cout << "EXCEPTION: " << e.what() << "\n";
//    }
//    auto size = items.size();
//    if (size != 0) {
//      auto sum = std::accumulate(items.begin(), items.end(), 0);
//      cout << "INT: " << res << " AV.DUR: " << sum/size << "ms (" << sum << "ms total)\n";
//    }
//  }

//  {
//    double res = -1.;
//    jsxx::timer t;
//    try {
//      t.start();
//      for (int i = 0; i < NUM_RUN; ++i) {
//        res = jsxx::string_to_real<double>(beg, s.end());
//      }
//      t.stop();
//    }
//    catch (std::exception& e) {
//      cout << "EXCEPTION: " << e.what() << "\n";
//    }
//    cout << "DOUBLE: " << std::setprecision(std::numeric_limits<double>::digits10)
//                        << std::scientific << res << " " << t.ms() << " ms total\n";
//  }

//  {
//    float res = -1.;
//    jsxx::timer t;
//    try {
//      t.start();
//      for (int i = 0; i < NUM_RUN; ++i) {
//        res = jsxx::string_to_real<float>(beg, s.end());
//      }
//      t.stop();
//    }
//    catch (std::exception& e) {
//      cout << "EXCEPTION: " << e.what() << "\n";
//    }
//    cout << "FLOAT: " << std::setprecision(std::numeric_limits<float>::digits10)
//                        << std::scientific << res << " " << t.ms() << " ms total\n";
//  }


  return 0;
}
