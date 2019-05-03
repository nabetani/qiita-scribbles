N=1024

class Tarai
  def initialize
    @cache = {}
  end

  def call(x, y, z)
    return y if x <= y
    @cache[((x*N)+y)*N+z] ||= call(
      call(x - 1, y, z),
      call(y - 1, z, x),
      call(z - 1, x, y)
    )
  end
end

tarai = Tarai.new
p tarai.call(400, 50, 0)