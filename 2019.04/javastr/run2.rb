%w( UseStringBuilder2 UseStringPlus2 ).each do |name|
  p name
  puts( %x( javac #{name}.java && time java #{name} 10000 a ) )
end
