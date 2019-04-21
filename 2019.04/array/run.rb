Dir.glob( "*.cpp" ).each do |cpp|
  out =  File.join("bin", cpp.gsub( /\.cpp$/, "" ) )
  puts "\n*** #{out} ***"
  std = /_new/.match?(out) ? "c++14" : "c++11"
  puts %x( clang++ -std=#{std} -Wall #{cpp} -o #{out} 2>&1 && ./#{out} )
end
