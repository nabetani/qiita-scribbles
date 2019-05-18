def make_tarai
  cache = {}
  tarai = lambda do |x, y, z|
    return y if x <= y
    cache[:"#{x}|#{y}|#{z}"] ||= tarai.call(
      tarai.call(x - 1, y, z),
      tarai.call(y - 1, z, x),
      tarai.call(z - 1, x, y)
    )
  end
end

tarai = make_tarai
p tarai.call(400, 50, 0)