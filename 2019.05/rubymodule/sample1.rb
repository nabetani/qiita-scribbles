module ModA
  def run;p 'ModA';end
end

module ModB
  def run;p 'ModB';end
end

module ModC
  def run;p 'ModC';end
end

module ModD
  def run;p 'ModD';end
end

class Base
  include ModA
  def run;p 'Base';end
  include ModB
end

Base.new.run #=> "Base"

class Derived < Base
end

Derived.new.run #=> "Base"

class Derived
  include ModC
end

Derived.new.run #=> "ModC"

class Derived
  include ModD
end

Derived.new.run #=> "ModD"

o = Derived.new
def o.run; p 'def o.run'; end

o.run  #=> "def o.run"

class Derived
  def run; p 'Derived#run'; end
end

o.run  #=> "def o.run"
