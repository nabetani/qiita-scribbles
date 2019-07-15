#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono;

using clock_type = steady_clock;

int64_t tick()
{
  static auto start = clock_type::now();
  return duration_cast<microseconds>(clock_type::now() - start).count();
}

int main()
{
  std::mutex mutex;
  std::condition_variable cv;
  for (auto usec : {1, 100, 10000, 1000000})
  {
    std::cout << "usec=" << usec << std::endl;
    for (int i = 0; i < 10; ++i)
    {
      std::uint64_t t0, t1, t2;
      t0 = tick();
      unique_lock<std::mutex> lock(mutex);
      t1 = tick();
      cv.wait_for(lock, microseconds(usec));
      t2 = tick();
      std::cout              //
          << t1 - t0 << ", " //
          << t2 - t0 << ", " //
          << std::endl;
    }
  }
  return 0;
}
