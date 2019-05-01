@kazatsuyu 様
ご指摘ありがとうございます。
確かに「暗黙でextern」は正しくないですね。

### ケースA

|foo.c|bar.c|
|:--|:--|
|`const int apricot;`|`const int apricot;`|

この場合は 仮定義->定義がないので 0 になります。

### ケースB

|foo.c|bar.c|
|:--|:--|
|`const int banana=123;`|`const int banana;`|

bar.c, では「仮定義」ですが、定義がひとつあるので 123 になります。

### ケースC

|foo.c|bar.c|
|:--|:--|
|`const int coconuts;`|`extern const int coconuts;`|

全て extern で、定義がないのでエラーです。

### ケースD

|foo.c|bar.c|
|:--|:--|
|`const int dasmon=123;`|`extern const int dasmon;`|

foo.c の `dasmon` が外部リンケージになります。
bar.c の `dasmon`  `extern` なので、他の定義を必要とします。
定義がひとつだけあるので、`dasmon` は 123 になります。

### というわけで

ケースB と D を比べると、ケースCは暗黙の extern であるようにみえます。
しかし、ケースA と C を比べた場合は extern の有無で違いが出ますね。

というわけで、[@kazatsuyu 様のコメント]( https://qiita.com/sy_/items/09ea1324a10d69b4dfee#comment-cdd01b70fb144b25ef86 )のとおり、C言語では

* C++と異なり、暗黙で static にならない
* static にならないので、外部リンケージになる

が正解でした。
すいません。
