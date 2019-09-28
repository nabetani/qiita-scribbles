import com.google.gson.Gson;

class Hoge {
  public float foo;
  public double bar;
}

public class Main {
  public static void main(String[] args) {
    Hoge hoge = new Hoge();
    hoge.foo = 0xa0000000L;
    hoge.bar = 0xa0000000L;
    Gson gson = new Gson();
    System.out.println(gson.toJson(hoge));
  }
}
