clang rasp sin
====
# これはなに？

https://qiita.com/Nabetani/items/102aac1b447099098724
のためのソースコード

# 結果


## clang on Raspberry Pi

```
$ clang++ -Wall clangsin.cpp && ./a.out
f=-9.32929e-17  d=2.11371e-314
f=3.45  d=6.20896e-312
f=cd cc 5c 40 
d=9a 99 99 99 24 01 00 00
```

## g++ on Raspberry Pi

```
$ g++-8 -Wall clangsin.cpp && ./a.out
f=-0.952818  d=-0.952818
f=-0.952818  d=-0.952818
f=e5 eb 73 bf 
d=98 e6 d6 9f 7c 7d ee bf 
```
