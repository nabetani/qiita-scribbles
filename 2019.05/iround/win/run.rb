OPTS = %w(
  O2 Ob2 Ot Oi GL
  GS- Gy
  EHsc
  arch:AVX512
  fp:precise
  permissive-
  std:c++17
  MT 
).map{ |e| "/"+e }.join(" ")

def run(name)
  puts %x( cl #{OPTS} #{name}.cpp 2>&1 )
  %x( #{name}.exe )
  puts %x( #{name}.exe )
end

run("original")
