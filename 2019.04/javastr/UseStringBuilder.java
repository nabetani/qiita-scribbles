public class UseStringBuilder {
  private static int receiver(String s) {
    if (s.equals("hoge")) {
      return 1;
    } else {
      return 0;
    }
  }

  private static String makestr(int len){
    StringBuilder b = new StringBuilder();
    for( int i=0 ; i<len*1024 ; ++i ){
      b.append((char)i);
    }
    return b.toString();
  }
  private static final String foo = makestr(1);
  private static final String bar = makestr(2);
  private static final String baz = makestr(4);
  private static final String qux = makestr(8);
  private static final String quux = makestr(16);
  private static final String corge = makestr(32);

  public static void main(String[] args) {
    int sum = 0;
    String[] bars = new String[] { "baz", "qux" };
    for (int i = 0; i < Integer.parseInt(args[0]); ++i) {
      sum += receiver(new StringBuilder()
      .append("hoge")
      .append( foo )
      .append( bar )
      .append( baz )
      .append( qux )
      .append( quux )
      .append( corge )
      .toString() );
    }
    System.out.println(sum);
  }
}
