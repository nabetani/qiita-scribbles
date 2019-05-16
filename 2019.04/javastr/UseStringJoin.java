public class UseStringJoin {
  private static int receiver( String s ){
    if ( s.equals("hoge") ){
      return 1;
    } else {
      return 0;
    }
  }
  private static final String hoge = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz";
  public static void main( String[] args ){
    int sum=0;
    String[] bars = new String[]{ "baz", "qux" };
    for( int i=0 ; i<Integer.parseInt(args[0]) ; ++i ){
      sum += receiver( 
        String.join("",new String[]{
        hoge,
        "foo",
        bars[i%2],
        "quux",
        hoge,
        "foo",
        bars[1-i%2],
        "quux",
        hoge,
        "foo",
        bars[i%2],
        "quux",
        hoge,
        "foo",
        bars[1-i%2],
        "quux",
        hoge,
        "foo",
        bars[i%2],
        "quux",
        hoge})
      );
    }
    System.out.println(sum);
  }
}
