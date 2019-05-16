module ModA
  def run; p :ModA ;end
end

module ModB
  def run; p :ModB ;end
end

module ModC
  def run; p :ModC ;end
end

module ModD
  def run; p :ModD ;end
end

class UseInclude
  include ModA
  def run; p :UseInclude; end
end

UseInclude.new.run #=> :UseInclude

class UsePrepend
  prepend ModA
  def run; p :UsePrepend; end
end

UsePrepend.new.run #=> :ModA

o = UsePrepend.new

def o.run; p :"o.run"; end
o.run #=> :"o.run"

o.class.prepend ModB

o.run #=> :"o.run"

o.singleton_class.include ModC

o.run #=> :"o.run"

o.singleton_class.prepend ModD

o.run #=> :ModD
