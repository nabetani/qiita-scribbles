public class UseStringPlus {
  private static int receiver( String s ){
    if ( s.equals("hoge") ){
      return 1;
    } else {
      return 0;
    }
  }
  private static final String foo = "uprjkdowvyvqxlncsjgqzstikgclvgorshfrruifnnuzcfqtgtojfqsakcfvaisaysaxbrlpfczukomfxoebwypmqbkqmeevgivpdxnawthcazjobhhhydlbeiltwbmvwsykslyudqludjqlmkzilhreuxyajqgpiwebbxdnccrfmictdxolowxxnaeoucmtybdnmujrwshdezptpjpmzjdnasikhjztfnuezvipxwvywhgvmzqtrfehkkbrgganygop";
  private static final String bar = "bjsqdbkweettnvympybihyjrkhqtedvpogounxelthhyrtbpzoldujwzmmspacjtxwjwciusocwimihuumzvarvyqorunyinmqlkaefmlghcoxsvqbbazlbgavsffmqnjyaqturfgvwrfsgdcrksdexcipznpovpzilbgpxewclexahkxylffwsjiuiuthtbkrkqimcfcfzkoptzsroljeagdzgacdpgxdqwnjymwnnvqlohvsyxkbnazgedrxdjukfh";
  private static final String baz = "phblfiycdsnaahcskasevmthowdijgvfxdzuiivsubtqdwqzcbjhxvlhclkxnmpikfphceulcypiukpkrwzrnmzabydgmfwulrkjbonpcfgvjfbewdavycsjaqfsgvuqunblbzysezasrlrkeawotzjmdvemcqfditpjuolntiymrwxbgmhupoznjydqxzhghgifwnbkgosarjtuvxgneqorxzjemqtepwldrmqytkygsfetvnclqhyxoprioatxxkwo";
  private static final String qux = "rysvvsftwtolxonofdvkjjepouyayiyszgehjuqmunagaaiacrlpalcyizpwmrscldwpfiggobbsynzczfjhcqoqmlkvobljithjucwxmyzdsbrhkjpnpezxmqegbllwcdtraovdupkhbnsekkszffesmrpigwaeqqdxtnklusiwyljbhkzhktarxcraqvcvdybpunxeqnurmrbhoptgdffcfwwemqxvivxhgdnyttkivxjfzzhbqgujigmwmetnuxod";
  private static final String quux = "aodwvgukhmcwrzxwpmlucjnnwtjviytbtbahyexaefkmmweozifczxnzxafwbyjgoknssrtrdoihwhxmktsykfgapffmzqujlgtovsikgjwjtzcuxkgmequueqlnjratiqrznxpyomvsyiccbiyqrwbelbhpvvpgscqzpdsnqrohphdiomjcwivxddpyqelcdnapzlixbqdsfrehamzhyaavpuxjklllvulfqyostchdrgjgdbugfoeuknbsbrntkevf";
  public static void main( String[] args ){
    int sum=0;
    String[] bars = new String[]{ "baz", "qux" };
    for( int i=0 ; i<Integer.parseInt(args[0]) ; ++i ){
      sum += receiver( 
        "hoge"
        + foo 
        + bar 
        + baz 
        + qux 
        + quux 
       );
    }
    System.out.println(sum);
  }
}
