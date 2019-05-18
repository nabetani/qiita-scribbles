CC = %w( clang++ g++-8 )
STD = %w( 03 11 14 17 2a )

%x( mkdir -p bin )

CC.each do |cc|
  STD.each do |std|
    puts %x( #{cc} const.cpp -std=c++#{std} -Wall -o bin/#{cc}_#{std} )
  end
end
