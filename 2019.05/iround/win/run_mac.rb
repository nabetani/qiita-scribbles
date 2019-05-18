OPTS = %w(
  Wall
  O2
  flto
  std=c++17
  march=native
  mtune=native
).map{ |e| "-"+e }.join(" ")

def run(cc, name)
  puts %x( #{cc} #{OPTS} #{name}.cpp -o #{name} 2>&1 )
  %x( ./#{name} ) # 練習
  puts %x( ./#{name} ) # 本番
end

run("clang++", "original")
#run("g++-8", "original")
run("clang++","modified")
#run("g++-8","modified")
