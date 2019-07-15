#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;

using clock_type = steady_clock;

int64_t tick() {
  static auto start = clock_type::now();
  return duration_cast<microseconds>(clock_type::now() - start).count();
}

int main() {
  std::mutex mutex;
  std::condition_variable cv;
  for (int i = 0; i < 10; ++i) {
    int64_t t1, t2;
    int64_t t0 = tick();
    thread th{[&]() {
      this_thread::sleep_for( milliseconds(1) );
      t1 = tick();
      cv.notify_all();
      t2 = tick();
    }};
    unique_lock<std::mutex> lock(mutex);
    int64_t t3 = tick();
    cv.wait_for(lock, seconds(1));
    int64_t t4 = tick();
    th.join();
    std::cout              //
        << t1 - t0 << ", " //
        << t2 - t0 << ", " //
        << t3 - t0 << ", " //
        << t4 - t0 << ", " //
        << t4 - t1 << ", " //
        << std::endl;
  }
  return 0;
}
