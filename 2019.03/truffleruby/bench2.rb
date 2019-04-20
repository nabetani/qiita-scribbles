
T=[
  [ "go1.12.1", "./fibogo" ],
  [ "java12", "java fibo" ],
  [ "GNU Fortran 8.3", "./fibof95" ],
  [ "C++03 / clang", "./fibo03clang"],
  [ "C++03 / g++-8", "./fibo03gcc"],
  [ "C++17 / clang", "./fibo17clang"],
  [ "C++17 / g++-8", "./fibo17gcc"],
]

[42, 45].each do |f|
  T.map do |name,cmd|
    r = %x(time (#{cmd} #{f}) 2>&1)
    tick = /real.*s/.match(r)[0]
    "%17s %s" % [name,tick]
  end.tap{ |e| 
    puts
    puts( f )
    puts e.join("\n")
  }
end