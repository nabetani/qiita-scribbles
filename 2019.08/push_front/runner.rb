CCs = %w( clang++ g++-9 )

def compile
  CCs.each do |cc|
    out = "#{cc}.out"
    if !File.exist?(out) || File.ctime( out ) < File.ctime( "src.cpp" )
      puts %x( #{cc} -std=c++17 -Wall -O3 src.cpp -o #{out} 2>&1 )
    end
  end
end

def run
  [4,256].each do |s|
    [1,2,3,4,5,7,9,11,14,17,21,26,32,39,47,57,69,83,100,121,146,176,212,255].each do |i|
      %w( v V d l ).each do |t|
        CCs.each do |cc|
          v=Array.new(3){ 
            %x( ./#{cc}.out #{s} #{i} #{t} ).strip.to_i
          }.min
          puts( [s,t,cc,v].join(",") )
        end
      end
    end
  end
end

compile
run
