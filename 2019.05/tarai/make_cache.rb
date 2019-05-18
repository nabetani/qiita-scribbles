def make_cache(arity)
  seed = "{}"
  (arity - 1).times do
    seed = "Hash.new { |hash, key| hash[key] = #{seed} }"
  end
  eval(seed)
end

def make_cache2(arity)
  (arity - 1).times.inject({}){ |hash,| Hash.new{ |h, k| h[k] = hash } }
end

def make_cache3(arity)
  (arity - 1).times.inject({}){ |hash,| Hash.new{ |h, k| h[k] = hash.dup } }
end

def test(c)
  c[0][0][0] = 3
  c[1][1][1] = 4
  p c
end

test( make_cache(3) )
test( make_cache2(3) )
test( make_cache3(3) )
