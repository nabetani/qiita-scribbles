Dir.glob( "*.cpp" ).each do |cpp|
  out =  File.join("bin", cpp.gsub( /\.cpp$/, "" ) )
  puts "\n*** #{out} ***"
  puts %x( clang++ -std=c++11 -Wall #{cpp} -o #{out} 2>&1 && ./#{out} )
end
