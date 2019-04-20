import Foundation

func fibo(n: Int) -> Int{
  if ( n<=1 ){
    return 1
  } else {
    return fibo(n:n-1)+fibo(n:n-2)
  }
}

let argv = ProcessInfo.processInfo.arguments
let f = fibo(n:Int(argv[1])!)
print("\(argv[1]) -> \(f)")
