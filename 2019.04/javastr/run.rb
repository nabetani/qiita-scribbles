%w( UseStringBuilder UseStringPlus ).each do |name|
  p name
  puts( %x( javac #{name}.java && time java #{name} 10000000 ) )
end
