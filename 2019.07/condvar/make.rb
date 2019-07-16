require "fileutils"

ccs = case RUBY_PLATFORM
when /linux/
  [
    [ "g++-8 -Wall -O3 -std=c++17 -lpthread", "-o" ],
    [ "clang++ -Wall -O3 -std=c++17 -lpthread", "-o" ]
  ]
when /darwin/
  [
    [ "g++-9 -Wall -O3 -std=c++17", "-o" ],
    [ "clang++ -Wall -O3 -std=c++17", "-o" ]
  ]
when /mingw/
  [
    [ "cl /O2 /Ot /Wall /EHsc /std:c++17", "/Fe" ]
  ]
end

FileUtils.mkdir_p("bin")

ccs.each do |cc, o|
  target = "bin/#{cc.split(" ").first}.exe"
  puts %x( #{cc} main.cpp #{o}#{target} 2>&1 )
  puts "="*20
  puts target
  puts
  puts %x( #{target} #{ARGV.join(" ")})
end