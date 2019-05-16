class Foo
  def self.self_dot; p "self_dot"; end
  class << self
    def class_ltlt_self; p "class_ltlt_self"; end
  end
end

def Foo.foo_dot
  p "foo_dot"
end

Foo.define_singleton_method :with_dsm do
  p "with_dsm"
end

class Bar < Foo; end

Bar.self_dot # okay
Bar.class_ltlt_self # okay
Bar.foo_dot # okay
Bar.with_dsm # okay

Bar::self_dot # okay
Bar::class_ltlt_self # okay
Bar::foo_dot # okay
Bar::with_dsm # okay

class Baz < Foo
  def hoge
    self_dot # undefined local variable or method
    class_ltlt_self # undefined local variable or method
    foo_dot # undefined local variable or method
    with_dsm # undefined local variable or method
  end
end

Baz.new.hoge