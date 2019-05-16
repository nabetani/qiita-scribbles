OPTS = %w(
  O2 Ob2 Ot Oi GL
  GS- Gy
  EHsc
  arch:AVX512
  fp:precise
  permissive-
  std:c++17
  MT
  utf-8
  W4
).map{ |e| "/"+e }.join(" ")

def run(name)
  puts %x( cl #{OPTS} #{name}.cpp 2>&1 ).force_encoding("cp932")
  %x( #{name}.exe ) # 練習
  puts %x( #{name}.exe ) # 本番
end

run("original")
run("modified")
