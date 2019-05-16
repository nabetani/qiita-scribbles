#  include <chrono>
#  include <thread>
#  include <cmath>
#  include <iostream>
#  include <array>

//これが定義していあると、templateを使ったプログラミングに便利
template<class INTEGRAL_TYPE>
constexpr int iround(INTEGRAL_TYPE v)
{
  return static_cast<int>(v);
}

template<>
constexpr int iround(float v)
{
  if(v >= 0) {
    return static_cast<int>(v + 0.5f);
  } else {
    return -static_cast<int>(-v + 0.5f);
  }
}

template<>
constexpr int iround(double v)
{
  if(v >= 0) {
    return static_cast<int>(v + 0.5);
  } else {
    return -static_cast<int>(-v + 0.5);
  }
}

template<>
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

template<size_t n>
double average(std::array<int,n> const & a ){
    double sum=0;
    for( auto e : a ){
        sum+=e;
    }
    return sum/a.size();
}


template<class T>
void test(T r)
{
    using namespace std;

    constexpr int loop_count = 1000000;
    using dest_t = std::array<int,loop_count>;
    dest_t & dest0 = *new dest_t; // memory leaks!
    dest_t & dest1 = *new dest_t; // memory leaks!
    dest_t & dest2 = *new dest_t; // memory leaks!

    using src_t = std::array<T,loop_count>;
    src_t & src = *new src_t; // memory leaks!
    std::fill(src.begin(), src.end(), r);

    StopWatch sw;
    for (int z = 0; z < loop_count; z++) {
        dest0[z] = iround(src[z]);
    }
    auto lap0 = sw.lap();
    cout << "self implementation: " << lap0 << " ms" << endl;
    sw.lap();
    for (int z = 0; z < loop_count; z++) {
        dest1[z] = iround2(src[z]);
    }
    auto lap1 = sw.lap();
    cout << "round base: " << lap1 << " ms" << endl;
    sw.lap();
    for (int z = 0; z < loop_count; z++) {
        dest2[z] = iround3(src[z]);
    }
    auto lap2 = sw.lap();
    cout << "lround base: " << lap2 << " ms" << endl;

    cout << r << " " << average(dest0) << " " << average(dest1) << " "<< average(dest2) <<endl;
}

int main()
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

    return 0;
}
