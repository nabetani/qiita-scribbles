public class UseStringPlus2 {
  private static int receiver( String s ){
    if ( s.equals("hoge") ){
      return 1;
    } else {
      return 0;
    }
  }
  private static String makestr(int len, char c0){
    StringBuilder b = new StringBuilder();
    for( int i=0 ; i<len*1024 ; ++i ){
      b.append(c0+(char)i);
    }
    return b.toString();
  }
  public static void main( String[] args ){
    String foo = makestr(1, args[1].charAt(0));
    String bar = makestr(2, args[1].charAt(0));
    String baz = makestr(4, args[1].charAt(0));
    String qux = makestr(8, args[1].charAt(0));
    String quux = makestr(16, args[1].charAt(0));
    String corge = makestr(32, args[1].charAt(0));
    int sum=0;
    for( int i=0 ; i<Integer.parseInt(args[0]) ; ++i ){
      sum += receiver( 
        "hoge"
        + foo 
        + bar 
        + baz 
        + qux 
        + quux 
        + corge
       );
    }
    System.out.println(sum);
  }
}
