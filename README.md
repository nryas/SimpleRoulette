# SimpleRoulette

## 寮でのお楽しみ抽選会で使うルーレット
XCode 7.2 と openFrameworks v0.90 を用いて開発しました．
簡単操作で抽選が行えます．
名簿は外部のCSVファイルで読み込むだけなので様々な場面で使い回しできます．

### 手順
* oF v0.90に以下のaddonを追加(projectGeneratorを使うと便利)
* ofxTrueTypeFontUC / ofxGui
* oF v0.90/app/myAppディレクトリなどにSimpleRouletteディレクトリを配置
* dataディレクトリに名簿データであるCSVファイル（フォーマットは後述）を追加
* dataディレクトリに任意のTrueTypeフォントのファイル（ファイル名"hiragino.ttc"）を追加
* XCodeでビルド

### 使い方
* アプリケーションとdataディレクトリを必要に応じて任意の場所に移動して実行
* アプリとdataディレクトリは同一ディレクトリ内に存在する必要があります

### CSVファイルについて
* 以下のフォーマットで保存してください．エンコーディングはUTF-8，BOM無しです．
* [学年], [学科], [名前]
* 例 => 5, I, John Smith
