#include <windows.h>
#include <cstdint>
#include <vector>
#include <cmath>
#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <array>

std::int64_t fibo(int n)
{
    if (n <= 1)
    {
        return 1;
    }
    return fibo(n - 1) + fibo(n - 2);
}

template <typename t>
auto make(size_t n, t const &v) -> std::vector<t>
{
    return std::vector<t>(n, v);
}

std::int64_t sum(std::int64_t n) { return n; }

template <typename t>
auto sum(std::vector<t> const &v) -> std::int64_t
{
    std::int64_t r = 0;
    for (auto const &e : v)
    {
        r += sum(e);
    }
    return r;
}

std::int64_t vec()
{
    constexpr int N = 10;
    auto v0 = std::vector<int64_t>(N);
    std::fill(v0.begin(), v0.end(), 1);
    auto v1 = make(N, v0);
    auto v2 = make(N, v1);
    auto v3 = make(N, v2);
    auto v4 = make(N, v3);
    auto v5 = make(N, v4);
    auto v6 = make(N, v5);
    auto v7 = make(N, v6);
    v7.insert(v7.begin(), v7.front());
    return sum(v7);
}

std::int64_t strmap()
{
    std::map<std::string,std::int64_t> m;
    constexpr int N=30000;
    std::string key{};
    for( int i=0 ; i<N ; ++i ){
        m[key]=i;
        key = static_cast<char>( i & 0x7f ) + key;
    }
    std::int64_t r = 0;
    for( auto[_,v] : m ){
        r+=v;
    }
    return r;
}

template< typename fp >
fp fpcalc( int n ){
    using ary = std::array<fp, 8>;
    ary a{ 1, 2, 3, 4, 5, 6, 7, 8 };
    ary b{ 9, 8, 7, 6, 5, 4, 3, 2 };
    ary c{0};
    auto f = []( ary const & x, ary const & y, ary & z ){
        for( size_t i=0 ; i<x.size() ; ++i ){
            z[i] = x[i]/(y[i]+1)/(z[(i+1)%z.size()]+1)+1;
        }
        for( auto & v : z ){
            v = std::fmod( v, fp(10) );
        }
    };
    for( int i=0 ; i<n ; ++i ){
        f(a,b,c);
        f(b,c,a);
        f(c,a,b);
    }
    return a[0];
}

void bench(char const *name, std::function<void()> func)
{
    LARGE_INTEGER freq{};
    QueryPerformanceFrequency(&freq);
    LARGE_INTEGER start{}, end{};
    QueryPerformanceCounter(&start);
    func();
    QueryPerformanceCounter(&end);
    auto diff = end.QuadPart - start.QuadPart;
    std::cout << name << ": " << (diff * 1.0 / freq.QuadPart) << std::endl;
}

int __cdecl main()
{
    bench("fpcalc<float>", []() { std::cout << fpcalc<float>(10000000) << std::endl; });
    bench("fpcalc<double>", []() { std::cout << fpcalc<double>(10000000) << std::endl; });
    bench("strmap", []() { std::cout << strmap() << std::endl; });
    bench("fibo(42)", []() { std::cout << fibo(42) << std::endl; });
    bench("vec", []() { std::cout << vec() << std::endl; });
    return 0;
}
