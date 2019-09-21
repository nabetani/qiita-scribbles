#if !defined fixfunc_hpp_h_
#define fixfunc_hpp_h_

#include <array>

namespace nabetani {
namespace detail {

template <typename> class funcbase; // undefined

template <typename ret_t_, typename... args_t>
class funcbase<ret_t_(args_t...)> {
public:
  using ret_t = ret_t_;
  virtual ret_t operator()(args_t... args) const = 0;
  virtual ~funcbase() {}
};

template <typename instance_t, typename> class func; // undefined

template <typename instance_t, typename ret_t_, typename... args_t>
class func<instance_t, ret_t_(args_t...)> : public funcbase<ret_t_(args_t...)> {
public:
  using ret_t = ret_t_;
  func() = delete;
  instance_t i_;
  func(instance_t const &i) : i_(i) {}
  func(instance_t &&i) : i_(std::move(i)) {}
  virtual ret_t operator()(args_t... args) const override {
    return i_(args...);
  }
};

template<typename t >
inline void destruct( t * p ){
  p->~t();
}
} // namespace detail

template <typename, size_t> class fixfunc; // undefined

template <typename ret_t_, typename... args_t, size_t size_>
class fixfunc<ret_t_(args_t...), size_> {
public:
  using ret_t = ret_t_;
  constexpr static size_t size() { return size_; }

private:
  std::array<char, size()> memory_;
  detail::funcbase<ret_t(args_t...)> *func_;

public:
  ~fixfunc()
  {
    detail::destruct(func_);
  }
  template <typename t>
  fixfunc(t const &v)
      : func_(new (memory_.data()) detail::func<t, ret_t(args_t...)>(v)) //
  {
    static_assert(sizeof(func_) <= size(),
                  "sizeof(func_) should not be greater than size of buffer");
  }
  template <typename... proc_args_t> ret_t operator()(args_t... args) const {
    return (*func_)(args...);
  }
};
} // namespace nabetani

#endif
