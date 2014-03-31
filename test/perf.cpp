
#include <iostream>
#include <jsxx/val.hpp>
#include <jsxx/reader.hpp>
#include <jsxx/writer.hpp>
#include "readfile.hpp"
#include "timer.hpp"


using namespace jsxx;
using std::cout;
using std::endl;


int main(int argc, char const* argv[])
{
  if (argc < 3) {
    cout << "error. missing input argument. usage: prog <num_run> <filename>\n";
    return 0; // tmp
  }

  int NUM_RUN = atoi(argv[1]);
  timer t;
  try {
    std::string const s = read_file(argv[2]);
    t.start();
    for (int i = 0; i < NUM_RUN; ++i) {
      auto v = read<val>(s);
    }
    t.stop();
  } catch (std::exception& e) {
    cout << "EXCEPTION: " << e.what() << " ";
  }

  cout << t.ms() << " ms\n";

  // TMP
  if (argc == 4) {
    std::string const s = read_file(argv[2]);
    auto v = read<val>(s);
    cout.precision(std::numeric_limits<double>::digits10+2);
    cout << s << " int:" << is_integer(v) << " real:" << is_real(v) << " " << v << endl;
  }


  return 0;
}

