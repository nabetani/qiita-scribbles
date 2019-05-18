class fibo{
  private static long f( int n ){
    if (n<=1){
      return 1;
    }
    return f(n-1) + f(n-2);
  }
  public static void main( String[] args ){
    int n = Integer.parseInt(args[0]);
    System.out.println( f(n) );
  }
}