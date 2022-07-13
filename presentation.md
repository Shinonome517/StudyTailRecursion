---
marp: true
theme: gaia-custom
header: 2022/06/03
footer: © 2022 [@Shinonome517Stu](https://twitter.com/Shinonome517Stu)
paginate: true 
size: 16:9
---
<!--_class: top-->

# C++で末尾再帰を最適化したい

B3 Shinonome

---
<!--_class: normal-->

## 結論

* 末尾再帰とは、関数のreturn処理直前のみで再帰呼び出しを行う再帰である
* C++(GNU GCC)では-O2レベルの最適化を行うことで末尾再帰最適化がなされる

---
<!--_class: normal-->

## 動機

C++でも再帰を書きてぇなぁ・・・

---
<!--_class: normal-->

## 末尾再帰最適化とは

以下三つを理解している必要がある

* 関数呼び出しの仕組み
* 再帰呼び出し
* 末尾関数呼び出し

---
<!--_class: normal-->

## 関数呼び出しの仕組み

サブルーチンを呼ぶ際、次の命令が格納されているアドレスをスタックに積む(PUSH)

メインルーチンに戻る際、次の命令が格納されているアドレスをスタックから読み取る(POP)

**→スタック領域が消費される**

---
<!--_class: normal-->

![height:500](https://user-images.githubusercontent.com/66119716/178664108-51249b9a-7179-4974-b978-35e1a3e65b26.png)

[出典 IPA：セキュアプログラミング講座](https://www.ipa.go.jp/security/awareness/vendor/programmingv2/contents/c006.html#:~:text=%E3%82%84%E3%81%95%E3%82%8C%E3%82%8B%E3%80%82-,%E5%9B%B31%2D12%EF%BC%9A%20%E3%82%B9%E3%82%BF%E3%83%83%E3%82%AF%E3%81%8B%E3%82%89%E5%9B%9E%E5%8F%8E,-%E9%96%A2%E6%95%B0%E5%91%BC%E3%81%B3%E5%87%BA%E3%81%97%E3%81%A8)

---
<!--_class: normal-->

## 再帰呼び出し

関数内部で、自分自身を呼び出す関数呼び出しのこと

ベースケースに到達するまで、関数を呼び出し続ける

**→スタックオーバーフローの危険がある**

---
<!--_class: normal-->

## 再帰呼び出し

```cpp
int fib(int n){
    if(n == 0){
        return 0;
    }
    else{
        return fib(n-1) + fib(n-2);
    }
}
```

---
<!--_class: normal-->

## 末尾関数呼び出し

return処理の直前に関数を呼び出しをしている、関数呼び出しのこと

下の例では特に再帰呼び出しでもあるので、末尾再帰呼び出しになっている

---
<!--_class: normal-->

## 末尾関数呼び出し

```cpp
int sigma(int n, int ans){
    if(n <= 0){
        return ans;
    }
    else{
        return sigma(n - 1, ans + n);
    }
}
```

---
<!--_class: normal-->

## 末尾再帰最適化

通常の再帰呼び出しでは、スタック領域を使い果たしてしまう場合がある

**→末尾再帰の場合に限って、ただのジャンプ命令にすることができる**

**→末尾再帰最適化**

---
<!--_class: normal-->

## C++で末尾再帰を最適化する

和を求める関数を末尾再帰で実装

$$
\sum_{k = 1}^{n}  k
$$

---
<!--_class: normal-->

## ソースコード

```cpp
#include <iostream>
#include <cstdint>
using namespace std;

int64_t sigma(int64_t n, int64_t ans){
    if(n <= 0) return ans;
    else return sigma(n - 1, ans + n);
}
int main(){
    cout << "sigma(100): " << sigma(100, 0) << endl;
    cout << "sigma(10000000): " << (int64_t)sigma(10000000, 0) << endl;
}
```

---
<!--_class: normal-->

## コンパイル

gdbを用いるので-gオプションをつける

以下3パターンのコンパイルを試す

---
<!--_class: normal-->

#### 最適化オプションなし

`g++ -g -Wall sigma-rec.cpp -o no-opt.out`

#### O1最適化オプション

`g++ -g -Wall -O1 sigma-rec.cpp -o opt.out`

#### O2最適化オプション

`g++ -g -Wall -O2 sigma-rec.cpp -o opt2.out`

---
<!--_class: normal-->

### 実行結果

上から順に「最適化オプションなし」,「O1最適化オプション」,「O2最適化オプション」の実行結果

→O2最適化オプションを付した実行ファイルのみ、正しく実行できている

---
<!--_class: normal-->

### 実行結果

![height:480px](https://user-images.githubusercontent.com/66119716/178676989-dc98b52a-5c49-49f8-9038-eb2eede4c080.png)

---
<!--_class: normal-->

## gdb解析結果

ターミナルで

```shell
gdb ./"file name"
(gdb) disass sigma
```

でsigma関数を逆アセンブルした

---
<!--_class: normal-->

#### 最適化オプションなし

![height:480px](https://user-images.githubusercontent.com/66119716/178677842-412aeceb-f145-408b-b074-021f0d4aef8a.png)

---
<!--_class: normal-->

#### O1最適化オプション

余分な処理は消されているようだが、call命令（関数呼び出し）は行われている

![height:350px](https://user-images.githubusercontent.com/66119716/178677978-d355b8f6-4a31-4400-b256-1b0c17802834.png)

---
<!--_class: normal-->

#### O2最適化オプション

call命令（関数呼び出し命令）が消えている

![height:400px](https://user-images.githubusercontent.com/66119716/178678063-38108a94-0876-4be5-bb9c-52d261658fc5.png)

---
<!--_class: normal-->

## 感想

* 最適化処理すげー

* 末尾再帰最適化を行える環境では、積極的に末尾再帰を利用したい

---
<!--_class: normal-->

## 参考資料

[関数呼び出しの仕組み IPA　セキュア・プログラミング講座](https://www.ipa.go.jp/security/awareness/vendor/programmingv2/contents/c006.html)

[CodeZine インラインアセンブラで学ぶアセンブリ言語 第3回](https://codezine.jp/article/detail/485)

[GNU g++ 最適化オプション](https://kaworu.jpn.org/cpp/g++_%E6%9C%80%E9%81%A9%E5%8C%96%E3%82%AA%E3%83%97%E3%82%B7%E3%83%A7%E3%83%B3)

---
<!--_class: final-->

## ご清聴ありがとうございました

---
<!--_class: normal-->

## おまけ

処理系が違えば、最適化の方法も異なる

以下はClang(Apple)でコンパイルされたsigma関数を逆アセンブルした結果

---
<!--_class: normal-->

#### 最適化オプションなし

![height:450px](https://user-images.githubusercontent.com/66119716/178689197-f4369029-5d1a-497a-a704-7444b7a9c9f9.png)

---
<!--_class: normal-->

#### O1最適化オプション

![height:450px](https://user-images.githubusercontent.com/66119716/178689336-47455ce7-7869-4d3a-93a1-7b564359eccf.png)

---
<!--_class: normal-->

#### O2最適化オプション

![height:450px](https://user-images.githubusercontent.com/66119716/178689394-83101931-2125-48f2-af2c-946ce24fedf7.png)