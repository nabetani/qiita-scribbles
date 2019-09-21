// A. 本ソフトウェアは Everyone'sWare です。このソフトを手にした一人一人が、
//    ご自分の作ったものを扱うのと同じように、自由に利用することが出来ます。
//   A-1. フリーウェアです。作者からは使用料等を要求しません。
//   A-2. 有料無料や媒体の如何を問わず、自由に転載・再配布できます。
//   A-3. いかなる種類の 改変・他プログラムでの利用 を行っても構いません。
//   A-4. 変更したものや部分的に使用したものは、あなたのものになります。
//        公開する場合は、あなたの名前の下で行って下さい。
// B. このソフトを利用することによって生じた損害等について、作者は
//    責任を負わないものとします。各自の責任においてご利用下さい。
// C. 著作者人格権は 鍋谷武典 に帰属します。著作権は放棄します。
// D. 以上の A, B, C は、ソース・実行バイナリの双方に適用されます。

#if !defined fixfunc_hpp_h_
#define fixfunc_hpp_h_

#include <array>

namespace nabetani {
namespace detail {

template <typename> class funcbase_t; // undefined

template <typename ret_t_, typename... args_t>
class funcbase_t<ret_t_(args_t...)> {
public:
  using ret_t = ret_t_;
  virtual ret_t operator()(args_t... args) = 0;
  virtual void clone_to(char *memory) const = 0;
  virtual ~funcbase_t() {}
};

template <typename instance_t, typename> class func_t; // undefined

template <typename instance_t, typename ret_t_, typename... args_t>
class func_t<instance_t, ret_t_(args_t...)>
    : public funcbase_t<ret_t_(args_t...)> {
public:
  using ret_t = ret_t_;
  func_t() = delete;
  instance_t i_;
  func_t(instance_t const &i) : i_(i) {}
  func_t(instance_t &&i) : i_(std::move(i)) {}
  void clone_to(char *memory) const override { new (memory) func_t(i_); }
  ret_t operator()(args_t... args) override { return i_(args...); }
};

template <typename t> inline void destruct(t *p) { p->~t(); }
} // namespace detail

template <typename> class func_type; // undefined
template <typename ret_t, typename ... args_t>
class func_type< ret_t(args_t...)>
{
  template< bool empty, typename ... arg_types  > struct size_impl;
  static constexpr size_t max_size_t( size_t a, size_t b ){
    return a<b ? b : a;
  }
  template< typename t > struct portable { using type=t; };
  template< typename r, typename ...a > struct portable< r(a...) >{ using type=r(*)(a...); };
public:
  template< typename args_t0, typename ... arg_types >//
  static constexpr size_t size()
  {
    using f0 = detail::func_t< typename portable<args_t0>::type, ret_t(args_t...)>;
    return max_size_t( sizeof(f0), size_impl<sizeof...(arg_types)==0, arg_types...>::count );
  }
private:
  template<typename ... arg_types  > struct size_impl<true, arg_types...>{
    enum{ count=0 };
  };
  template<typename ... arg_types  > struct size_impl<false, arg_types...>{
    enum{ count=func_type::size<arg_types...>() };
  };

};

template <typename, size_t> class fixfunc; // undefined

template <typename ret_t_, typename... args_t, size_t size_>
class fixfunc<ret_t_(args_t...), size_> {
public:
  using ret_t = ret_t_;
  constexpr static size_t size() { return size_; }

private:
  mutable std::array<char, size()> memory_;
  using func_t = detail::funcbase_t<ret_t(args_t...)>;
  func_t *func() { return reinterpret_cast<func_t *>(memory_.data()); };
  func_t *func() const { return reinterpret_cast<func_t *>(memory_.data()); };

public:
  ~fixfunc() { detail::destruct(func()); }

  // NOT explicit
  template <typename t> fixfunc(t const &v) {
    using actual_func_t = detail::func_t<t, ret_t(args_t...)>;
    static_assert(
        sizeof(actual_func_t) <= size(),
        "sizeof(actual_func_t) should not be greater than size of buffer");
    new (memory_.data()) actual_func_t(v);
  }
  // NOT explicit
  fixfunc(ret_t (*v)(args_t...)) {
    using actual_func_t = detail::func_t<decltype(v), ret_t(args_t...)>;
    static_assert(
        sizeof(actual_func_t) <= size(),
        "sizeof(actual_func_t) should not be greater than size of buffer");
    new (memory_.data()) actual_func_t(v);
  }

  fixfunc(fixfunc const &that) { that.func()->clone_to(memory_.data()); }

  fixfunc &operator=(fixfunc const &that) {
    fixfunc tmp(that);
    tmp.swap(*this);
    return *this;
  }

  void swap(fixfunc &that) noexcept { std::swap(memory_, that.memory_); }

  template <typename... proc_args_t> ret_t operator()(args_t... args) const {
    return (*func())(args...);
  }
  template <typename... proc_args_t> ret_t operator()(args_t... args) {
    return (*func())(args...);
  }
};
} // namespace nabetani

#endif
