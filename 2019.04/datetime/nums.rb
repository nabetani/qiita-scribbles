require "pp"
require "date"

def nums
  (1..100).each do |len|
    s="%0*d" % [len,1]
    begin
      r = Date.parse(s).strftime( "%Y.%m.%d" )
      puts "len = #{len}"
      puts %Q!Date.parse(#{s.inspect}).strftime( "%Y.%m.%d" )!
      puts "#=> #{r.inspect}"
    rescue =>e
      # kill exception
    end
  end
end

def double_digit_y
  deltas={}
  100.times do |y|
    s="%02d001" % y
    r = Date.parse(s).strftime("%Y").to_i
    deltas[r-y] ||= [y,r]
  end

  pp deltas
end

def len5samples
  %w( 68001 69001 12345 19000 19001 19365 19366 ).each do |s|
    r = begin
      Date.parse(s).strftime( "%Y.%m.%d" ).inspect
    rescue =>e
      e.inspect.gsub( /[\#\<\>]/, "" )
    end
    puts %Q!Date.parse(#{s.inspect}).strftime( "%Y.%m.%d" )!
    puts "#=> #{r}"
  end
end

def four_digits_y
  deltas={}
  3000.times do |d|
    s = "%04d001" % d
    r = Date.parse(s).strftime("%Y").to_i
    delta = r - d
    deltas[delta] ||= [ s, r ]
  end

  pp deltas
end

def len7samples
  %w(
    0000001 0068365
    0069001 0099365
    0100001 9999365
  ).each do |s|
    r = begin
      Date.parse(s).strftime( "%Y.%m.%d" ).inspect
    rescue =>e
      e.inspect.gsub( /[\#\<\>]/, "" )
    end
    puts %Q!Date.parse(#{s.inspect}).strftime( "%Y.%m.%d" )!
    puts "#=> #{r}"
    puts
  end
end

def era_prefix
  (?A..?Z).each do |x|
    s = "#{x}1.12.31"
    r = Date.parse(s).strftime( "%Y.%m.%d" ).inspect
    unless r=='"2001.12.31"'
      puts %Q!Date.parse(#{s.inspect}).strftime( "%Y.%m.%d" )!
      puts "#=> #{r}"
      puts
    end
  end
end

def era_samples
  %w(
    M45.1.1 M45.8.1 M46.1.1 M999.1.1 M0.1.1
    T12.3.4
    S56.7.8
    H31.4.20
    R1.5.1
    ㍻31.4.20
    平31.4.20
    平成31.4.20
    ).each do |s|
    r = begin
      Date.parse(s).strftime( "%Y.%m.%d" ).inspect
    rescue =>e
      e.inspect.gsub( /[\#\<\>]/, "" )
    end
    puts %Q!Date.parse(#{s.inspect}).strftime( "%Y.%m.%d" )!
    puts "#=> #{r}"
    puts
  end
end

def main
  nums
  double_digit_y
  len5samples
  four_digits_y
  len7samples
  era_prefix
  era_samples
end

main