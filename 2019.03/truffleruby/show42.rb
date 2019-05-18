# frozen_string_literal: true

require "json"

d = JSON.parse( File.open( "result.json", &:read ) )
len = d.keys.map(&:size).max
d.keys.sort.each do |key|
  r = d[key]["42"]
  min, sec = r.split("m")
  puts "%<key>#{len}s  %<min>sm%7<sec>s" % {key:key, min:min, sec:sec}
end
