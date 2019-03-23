using Plots
using JSON

jstxt = open("result.json") do file
  read(file, String)
end

data = JSON.parse(jstxt)

function to_sec(x)
  strm,strs = split(x, "m")
  m=parse(Float64,strm)
  s=parse(Float64,strs[1:length(strs)-1])
  m*60+s
end

envs = [ "2.6.2", "2.6.2/--jit", "jruby-9.2.6.0", "truffleruby-1.0.0-rc14" ]
k = sort(collect(keys(data[envs[1]])))
println(k)
y = map( env->begin
  values = map( x->data[env][x], k )
  return map( to_sec, values )
end, envs )

plot( y,
  legend = :topleft,
  label = envs,
  xlabel = "Argument of fibo",
  ylabel = "result of time (real)",
  xticks = (1:length(k), k),
  yscale=:log10
)

savefig("plot.pdf")
