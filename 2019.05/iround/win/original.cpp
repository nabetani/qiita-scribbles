#  include <chrono>
#  include <thread>
#  include <cmath>
#  include <iostream>

//これが定義していあると、templateを使ったプログラミングに便利
template<class INTEGRAL_TYPE>
constexpr int iround(INTEGRAL_TYPE v)
{
  return static_cast<int>(v);
}

constexpr int iround(float v)
{
  if(v >= 0) {
    return static_cast<int>(v + 0.5f);
  } else {
    return -static_cast<int>(-v + 0.5f);
  }
}

constexpr int iround(double v)
{
  if(v >= 0) {
    return static_cast<int>(v + 0.5);
  } else {
    return -static_cast<int>(-v + 0.5);
  }
}

constexpr int iround(long double v)
{
  if(v >= 0) {
    return static_cast<int>(v + 0.5l);
  } else {
    return -static_cast<int>(-v + 0.5l);
  }
}

//round関数がconstexprでないので、consteprにできない
inline int iround2(float v) { return static_cast<int>(std::round(v)); }
inline int iround2(double v) { return static_cast<int>(std::round(v)); }
inline int iround2(long double v) { return static_cast<int>(std::round(v)); }

//lround関数がconstexprでないので、consteprにできない
inline int iround3(float v) { return static_cast<int>(std::lround(v)); }
inline int iround3(double v) { return static_cast<int>(std::lround(v)); }
inline int iround3(long double v) { return static_cast<int>(std::lround(v)); }

struct StopWatch
{
public:
  StopWatch() { pre_ = std::chrono::high_resolution_clock::now(); }

  ///returns lap time in ms.
  double lap()
  {
    auto tmp = std::chrono::high_resolution_clock::now();  //sotres time.
    auto dur = tmp - pre_;
    pre_ = tmp;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count() / 1000000.0;
  }

private:
  std::chrono::high_resolution_clock::time_point pre_;
};


template<class T>
void test(T r)
{
    using namespace std;

    int x, x1, x2;
    int loop_count = 1000000;

    StopWatch sw;
    for (int z = 0; z < loop_count; z++) {
        x = iround(r);
    }
    cout << "self implementation: " << sw.lap() << " ms" << endl;
    sw.lap();
    for (int z = 0; z < loop_count; z++) {
        x1 = iround2(r);
    }
    cout << "round base: " << sw.lap() << " ms" << endl;
    sw.lap();
    for (int z = 0; z < loop_count; z++) {
        x2 = iround3(r);
    }
    cout << "lround base: " << sw.lap() << " ms" << endl;

    cout << r << " " << x << " " << x1 << " "<< x2 <<endl;
}

void main()
{
    using namespace std;
    cout << "float" << endl;
    float rf = rand() / 10.f;
    test(rf);

    cout << endl << "double" << endl;
    double rd = rand() / 10.0;
    test(rd);

    cout << endl<< "long double" << endl;
    long double rlld = rand() / 10.l;
    test(rlld);
}
