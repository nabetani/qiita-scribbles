# frozen_string_literal: true

require "json"

ENVS = [
  [ '2.6.2' ],
  [ '2.6.2', '--jit' ],
  [ 'jruby-9.2.6.0' ],
  [ 'truffleruby-1.0.0-rc14' ],
]

def rbenv(v)
  path = `RBENV_VERSION='#{v}' rbenv which ruby`.rstrip
  yield(path)
end

data = ENVS.each.with_object(Hash.new{ |h,k| h[k]={} }) do |(e,opt),o|
  name = [e,opt].compact.join("/")
  opt ||= ""
  (28..42).each do |n|
    rbenv(e) do |ruby|
      tick = /real\s+(\d+m[\d\.]+s)/.match(%x[(time "#{ruby}" #{opt} fibo.rb #{n}) 2>&1])[1]
      o[name][n]=tick
      $stderr.puts( [name, n, tick].join(" ") )
    end
  end
end

puts( JSON.pretty_generate(data))