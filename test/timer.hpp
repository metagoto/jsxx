#include <chrono>

namespace jsxx {

  struct timer
  {
    using clock_type = std::conditional<std::chrono::high_resolution_clock::is_steady
                                       ,std::chrono::high_resolution_clock
                                       ,std::chrono::steady_clock>::type;

    void start() { state_ = 1; start_ = clock_type::now(); }
    void stop() { stop_ = clock_type::now(); state_ |= 2; }
    int ms() {
      if ((state_ & 3) == state_)
        return std::chrono::duration_cast<std::chrono::milliseconds>(stop_-start_).count();
      return std::numeric_limits<int>::min();
    }


    unsigned char state_ = 0;
    decltype(clock_type::now()) start_;
    decltype(clock_type::now()) stop_;
  };

}

