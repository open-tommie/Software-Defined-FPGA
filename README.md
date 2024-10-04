# Software-Defined-FPGA
Raspberry Pi Pico 2などのマイコンボード上で動作するロジックシミュレータです。

## 概要

- マイコンボード上で実行することにより、ロジックシミュレーション結果をピン電圧として出力します。
- 実際のピン電圧がLow, Highに変化することがPC上のシミュレーションと異なる点です。
- 本物のFPGAではVerilogやVHDLなどの言語を使用しますが、Software-Defined-FPGAでは回路図情報を入力とします。（予定）
  - 現在は結線情報をソースコードに埋め込みます。
- 現在はUbuntu20上でPoC（概念実証）できた段階です。

## インストール方法

以下の手順でプロジェクトをローカル環境にインストールしてください。
Ubuntu20でのみテストしていますが、ほとんどのLinuxで動くと思います。

```bash
# リポジトリをクローン
$ git clone https://github.com/open-tommie/Software-Defined-FPGA.git

# ディレクトリに移動
$ cd Software-Defined-FPGA

# ビルドディレクトリを作成して移動
$ mkdir build
$ cd build

# ビルド
$ cmake ..
$ cmake --build .

```

## 使い方

```
# 実行方法の例
$ ./sd-fpga
```
・実行するとログを出力します。

## ログ解説
(TBD)
```
log
```

## シーケンス図へ変換する手順

PlantUMLを使ってsd-fpgaの出力をシーケンス図へ変換します。

### sd-fpgaの出力をPlantUMLのシーケンス図形式に変換する

```bash
$ ./sd-fpga |grep UML|sed -E 's/^.*UML://'
```
#### 変換後の出力例

```text
@0
ic00.pin00 is low
ic00.pin01 is low
ic00.pin02 is low
ic01.pin00 is low
ic01.pin01 is low
ic01.pin02 is low
ic02.pin00 is low
ic02.pin01 is low
ic02.pin02 is low
@1
ic00.pin00 is high
ic00.pin01 is high
ic00.pin02 is low
ic01.pin00 is low
ic01.pin01 is high
ic01.pin02 is low
ic02.pin00 is low
ic02.pin01 is low
ic02.pin02 is low
@2
ic00.pin00 is high
ic00.pin01 is high
ic00.pin02 is high
ic01.pin00 is high
ic01.pin01 is high
ic01.pin02 is low
ic02.pin00 is low
ic02.pin01 is low
ic02.pin02 is low
@3
ic00.pin00 is high
ic00.pin01 is high
ic00.pin02 is high
ic01.pin00 is high
ic01.pin01 is high
ic01.pin02 is high
ic02.pin00 is high
ic02.pin01 is low
ic02.pin02 is low
@4
ic00.pin00 is high
ic00.pin01 is high
ic00.pin02 is high
ic01.pin00 is high
ic01.pin01 is high
ic01.pin02 is high
ic02.pin00 is high
ic02.pin01 is low
ic02.pin02 is low
@5
ic00.pin00 is high
ic00.pin01 is high
ic00.pin02 is high
ic01.pin00 is high
ic01.pin01 is high
ic01.pin02 is high
ic02.pin00 is high
ic02.pin01 is low
ic02.pin02 is low
```


### PlantUMLのWebサイトでシーケンス図を描画

・PlantUMLのサイトをWebブラウザで開きます。

[PlantUML Web Server](https://www.plantuml.com/plantuml/uml/SyfFKj2rKt3CoKnELR1Io4ZDoSa70000)

・以下を先頭にコピーします。
```text
@startuml
binary "AND0.pin0" as ic00.pin00
binary "AND0.pin1" as ic00.pin01
binary "AND0.pin2" as ic00.pin02
binary "AND1.pin0" as ic01.pin00
binary "AND1.pin1" as ic01.pin01
binary "AND1.pin2" as ic01.pin02
binary "LED1.pin0" as ic02.pin00
binary "N/A" as ic02.pin01
binary "N/A" as ic02.pin02
```

・sd-fpgaの出力をコピーします。
・シーケンス図は自動更新されます。

#### PlantUMLシーケンス図の例




## ライセンス

このプロジェクトはMITライセンスのもとで公開されています。

## 貢献

貢献方法は以下の通りです。

1. スポンサーになる。
1. ★Star する
1. Fork する。
1. 新しいブランチを作成する。(git checkout -b feature/YourFeature)
1. コードをコミットする。(git commit -m 'Add some feature')
1. プッシュする。(git push origin feature/YourFeature)
1. プルリクエストを作成する。

## クレジット
(使用したライブラリや貢献者の名前を記す予定です)
