program fibonacci_main
  implicit none
  integer :: i
  integer(8) :: hoge
  character :: arg*10

  
  if(iargc()>0)then !実行ファイル名以外の引数がある時
    call getarg( 1, arg ) !文字列として取得
    read(arg,*) i !整数に変換
  else
    i=7 !無ければ適当な値
  end if

  hoge = fibo(i) 
  print *, hoge
contains
  recursive function fibo(n) result(res)
    integer :: n
    integer(8) :: res
    if ( n<=1 ) then
      res= 1
    else
      res = fibo(n-1) + fibo(n-2)
    end if
  end
end

