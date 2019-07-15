require "fileutils"

ccs = case RUBY_PLATFORM
when /linux/
  [
    "g++-8 -Wall -O3 -std=c++17 -lpthread",
    "clang++ -Wall -O3 -std=c++17 -lpthread"
  ]
when /darwin/
  [
    "g++-9 -Wall -O3 -std=c++17",
    "clang++ -Wall -O3 -std=c++17"
  ]
end

FileUtils.mkdir_p("bin")

ccs.each do |cc|
  target = "bin/#{cc.split(" ").first}.exe"
  %x( #{cc} main.cpp -o #{target} )
  puts "="*20
  puts target
  puts
  puts %x( #{target} )
end