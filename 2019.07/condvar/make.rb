require "fileutils"

ccs = [
  "g++-9 -Wall -O3 -std=c++17",
  "clang++ -Wall -O3 -std=c++17"
]

FileUtils.mkdir_p("bin")

ccs.each do |cc|
  target = "bin/#{cc.split(" ").first}.exe"
  %x( #{cc} main.cpp -o #{target} )
  puts "="*20
  puts target
  puts
  puts %x( #{target} )
end