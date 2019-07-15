require "fileutils"

FileUtils.mkdir_p("bin")
%w( clang++ g++-9 ).each do |cc|
  %w(1 1a 1b 2 3 3a).each do |target|
    puts "#{target} #{cc}"+"="*40
    bin = "bin/#{target}-#{cc}"
    src="#{target}.cpp"
    opt = File.open(src){ |f| f.gets.strip.gsub( "//", "") }
    puts( %x( #{cc} #{opt} #{src} -o #{bin} 2>&1 ) )
  end
end
