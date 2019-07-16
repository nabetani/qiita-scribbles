#include <atomic>
#include <chrono>
#include <cmath>
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;
using namespace std::chrono;

using clock_type = steady_clock;

int64_t tick() {
  static auto start = clock_type::now();
  return duration_cast<microseconds>(clock_type::now() - start).count();
}

int main(int argc, char const * argv[]) {
  std::mutex mutex;
  std::condition_variable cv;
  atomic<bool> stop_load = false;
  vector<thread> loads;
  atomic<int64_t> volatile sum = 0;
  const int load_count = argc<2 ? 10 : atoi(argv[1] );
  for (int i = 0; i < load_count; ++i) {
    loads.emplace_back([&] {
      while (!stop_load) {
        sum+=tick();
      }
    });
  }
  for (int i = 0; i < 20; ++i) {
    int64_t t1, t2;
    int64_t t0 = tick();
    thread th{[&]() {
      this_thread::sleep_for(milliseconds(1));
      t1 = tick();
      cv.notify_all();
      t2 = tick();
    }};
    unique_lock<std::mutex> lock(mutex);
    int64_t t3 = tick();
    cv.wait_for(lock, seconds(1));
    int64_t t4 = tick();
    th.join();
    cout              //
        << t1 - t0 << ", " //
        << t2 - t0 << ", " //
        << t3 - t0 << ", " //
        << t4 - t0 << ", " //
        << t4 - t1 << ", " //
        << endl;
  }
  stop_load = true;
  cout << "loads.size() = " << loads.size() << endl;
  for (auto &e : loads) {
    e.join();
  }
  cout << "sum=" << sum << endl;
  return 0;
}
