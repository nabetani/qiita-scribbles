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
  func_t const *func() const {
    return reinterpret_cast<func_t const *>(memory_.data());
  };

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
