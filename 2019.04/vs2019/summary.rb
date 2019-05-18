require "json"

EXES = [
  ["g++8.1(MinGW-W64)", "gpp"],
  ["clang++8.0 x86_64", "cla"],
  ["cl 19.20(vs2019)", "19"],
  ["cl 19.16(vs2017)", "17"],
]

o = 25.times.each.with_object(Hash.new{ |h,k| h[k]={} }) do |_,o|
  EXES.each do |name,bin|
    p name
    r=%x(#{bin})
    r.scan( /^([^\:\r\n]*)\s*\:\s*([^\:\r\n]*)$/ ){ |k,v|
    o[k][name] ||= []
    o[k][name].push( v.to_f )
      p [ k,v ]
    }
  end
end

File.open( "result.json", "w:utf-8" ) do |f|
  f.puts( o.to_json )
end
