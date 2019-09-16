// clang++ -std=c++17 -O3 -Wall -lpthread && ./a.out 10000

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

class foo {
  thread th_;
  mutex mutex_;
  condition_variable cv_;

public:
  void notify() { cv_.notify_all(); }
  foo()
      : th_([this]() {
          unique_lock<mutex> lock(mutex_);
          if (cv_status::no_timeout == cv_.wait_for(lock, 100us)) {
            cout << "received\n";
            return;
          }
          cout << "time out\n";
        }) {}
  ~foo() { stop(); }
  void stop() {
    if (th_.joinable()) {
      th_.join();
    }
  }
};

int main(int argc, char const *argv[]) {
  for (int i = 0; i < (argc<2 ? 10 : atoi(argv[1])); ++i) {
    std::cout << i << " ";
    foo f;
    this_thread::yield();
    f.notify();
    this_thread::sleep_for(200us);
  }
}