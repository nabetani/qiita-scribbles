# frozen_string_literal: true

def fibo(n)
  if n<=1
    1
  else
    fibo(n-1)+fibo(n-2)
  end
end

p fibo(ARGV[0].to_i)
