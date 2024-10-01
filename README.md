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

## ログ解説

```
log
```

## シーケンス図へ変換する手順

PlantUMLを使ってsd-fpgaの出力をシーケンス図へ変換します。


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
