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
  virtual ret_t operator()(args_t... args) = 0;
  virtual void clone_to( char * memory ) = 0;
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
  void clone_to( char * memory )  override {
    new (memory)instance_t(i_);
  }
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
  detail::funcbase<ret_t(args_t...)> *func_;

public:
  ~fixfunc() { detail::destruct(func_); }

  // NOT explicit
  template <typename t>
  fixfunc(t const &v)
      : func_(new (memory_.data()) detail::func<t, ret_t(args_t...)>(v)) //
  {
    static_assert(sizeof(*func_) <= size(),
                  "sizeof(func_) should not be greater than size of buffer");
  }

  fixfunc(fixfunc const &that)
      : func_(reinterpret_cast<decltype(func_)>(memory_.data())) {
    static_assert(sizeof(*func_) <= size(),
                  "sizeof(func_) should not be greater than size of buffer");
    that.func_->clone_to(memory_.data());
  }

  fixfunc & operator=(fixfunc const &that)
  {
    fixfunc tmp(that);
    tmp.swap(*this);
    return *this;
  }

  void swap( fixfunc &that) noexcept
  {
    std::swap( func_, that.func_ );
    std::swap( memory_, that.memory_ );
  }



  template <typename... proc_args_t> ret_t operator()(args_t... args) const {
    return (*func_)(args...);
  }
};
} // namespace nabetani

#endif
