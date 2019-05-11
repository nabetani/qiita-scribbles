def make_cache(arity)
  (arity - 1).times.inject({}){ |hash,| Hash.new{ |h, k| h[k] = hash.dup } }
end

class Tarai
  def initialize
    @cache = make_cache(3)
  end

  def call(x, y, z)
    return y if x <= y
    @cache[x][y][z] ||= call(
      call(x - 1, y, z),
      call(y - 1, z, x),
      call(z - 1, x, y)
    )
  end
end

tarai = Tarai.new
p tarai.call(400, 50, 0)
