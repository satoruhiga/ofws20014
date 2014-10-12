# openFrameworks with Other Apps

--- 

## intro

### プログラミング vs ツール

プログラムを書く / ツールを使う の違い

- プログラムを書く
	- 100%コントロールできる
	- 新しいこと、チャレンジングなことに挑戦できる
	- 大部分を自分で解決しないといけないので難しい / 時間がかかる
- ツールを使う
	- よく作られたUIでじっくりと試行錯誤しながら制作できる
	- 変更があった時の作業が簡単
	- 完成までの時間が読みやすい
	- ツールの制約でできない事 / 効率の悪い事が多い

**両方のいい所取りをしたい**、というのが趣旨

---

### 制作に対するアプローチの違い

トップダウンとボトムアップ、というのがあると思っています

- ボトムアップ
	- 枠組みから設計して作り上げていく
	- 様々な可能性を取捨しながら、絞り込みながら進める
	- 何ができるのかが最初はわからない
	- **可能性を少しも捨てたくない時はこのやり形**
- トップダウン
	- こういうものが欲しいというイメージが先にある
	- そういう時はどうするんだっけ? というかんじで進んでいく
	- 最初にイメージしたものができる
	- **最短距離で作りたい時はこのやり形**

前述のプログラムを書く / ツールを使うの対比とだいたい同じ。**どちらが正しいというのはない。**

でも、両方のサイドから同時に進められると嬉しいのではないか

---

### 外部アプリとの連携の手段

- 通信 - UDP, TCP, IPC, MIDI
	- リアルタイムでの処理
- ファイル読み込み、書き出し
	- **プリプロセス、ポストプロセス** ←	今回は主にこちら

---

# Adobe illustrator

## ベクタデータを使う

- 画像ファイルと違って頂点データの羅列なのでプログラムから変更しやすい。
- スケールの変更に強い

### SVG or PDF
- svg → ofxSvg → buildin
- pdf → ofxPDF → [satoruhiga/ofxPDF](https://github.com/satoruhiga/ofxPDF)

svgはデフォルトで入っているので楽

**PDFのほうがロードが早い** → Text vs Binary

---

## 例

### pdfの読み込み→表示

```cpp
#include "ofxPDF.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxPDF pdf;
	
	void setup() {
		pdf.load("test.pdf");
	}
	
	void draw() {
		pdf.draw();
	}
};
```

**アウトライン化されていないテキストは表示されないので注意**

**あと画像は読めない**

---

## ただ表示するだけでなくどう使えるか考える

### oFをプロダクションツールとして使う

* プログラマだけでなくその他の人と仕事を分担できる
* 外部ファイルを使っていると後から変更が簡単
* 細かい調整がツール側でできる
* **なんかよくわからないうちに思いがけない効果が出ることもある**

---

#TIPS

- 外部ファイルを途中でリロードできるようにプログラムを組んでおくと効率がいい
- 1つのパスに一筆書き的に複数の情報を詰めるか、パスごとに違う役割を持たせるかは設計による
- `ofBeginSaveScreenAsPDF(string filename)` / `ofEndSaveScreenAsPDF()` の中で`of***`系の関数を使って描画したものはpdf形式で保存できる → `example/graphics/pdfExample` を参照

---

# 自習&質問

何かわからない事があれば質問ください

---

# Adobe After Effects

## 映像とフレーム

時間をどれぐらいの粒度に分割してアニメーションさせるか。

- TVは大体秒間30コマ
- 映画は24コマ
- PCのディスプレイは60コマ

各フレームに対して値が変わるデータはアニメーションする要素として使える

画像をアニメーションの1コマとして捉えると、画像のシーケンス(配列)は映像として扱える

---

## キーフレームを読めるようにする

### ofxAfterEffectsKeyframeParser

1. AEからキーフレームの内容をテキストデータとしてコピー
2. 適当なテキストファイルに保存
3. oFで読み込み

[satoruhiga/ofxAfterEffectsKeyframeParser](https://github.com/satoruhiga/ofxAfterEffectsKeyframeParser)

```cpp
#include "ofxAfterEffectsKeyframeParser.h"

class ofApp : public ofBaseApp
{
public:
	ofxAfterEffectsKeyframeParser key;
	
	void setup() {
		key.open("test.txt");
		key.dumpTrackName();
	}
	
	void draw() {
		float app_time = ofGetElapsedTimef();
		float animation_time = fmodf(app_time, 3);
		
		const ofxAfterEffectsKeyframeParser::Track& track
			= key.getTrack("Transform/Position");
		
		int F = animation_time * 30;
		float x = track.getParam(F, "X pixels");
		float y = track.getParam(F, "Y pixels");
		
		ofRect(x, y, 100, 100);
	}
	
};
```

---

### 注意点

- アニメーションしたキーフレームを焼き込んでからコピペする
- リアルタイム用途の時や、なめらかさが必要な時は60フレにしておいたほうがいいかも

### キーフレームのベイク(焼き込み)

- タイムラインのストップウォッチボタンをoption+クリック
- アニメーション → キーフレーム補助 → エクスプレッションをキーフレームに変換

---

## AfterEffectsのトラッキング機能

[http://ae-style.net/tutorials/t03.html](http://ae-style.net/tutorials/t03.html)

特徴点となるポイントを指定すると適当に追従してくれる

手動で色々やるよりは絶対に早い

---

## 映像の書き出し

1. ムービーに直接書き出し
	- [neilmendoza/ofxMovieExporter](https://github.com/neilmendoza/ofxMovieExporter)
	- [heisters/ofxVideoPipe](https://github.com/heisters/ofxVideoPipe)
	
	ハマり要素が強いので普段は使わない...
2. 連番画像書き出し
	- [satoruhiga/ofxExportImageSequence](https://github.com/satoruhiga/ofxExportImageSequence)
	
ムービーに直接書き出せたほうが楽は楽だが、絵が荒れてしまったりするので可逆圧縮形式の連番画像のほうがベター

*可逆圧縮はpng, bmp, tgaなど色々なフォーマットがあるがtifが好きです*
	
---

## ofxExportImageSequence 簡単な使い方

```cpp
#include "ofxExportImageSequence.h"

ofxExportImageSequence seq_out;

void setup() {
	// 初期化: スクリーンサイズ、フレームレート等を設定する
	seq_out.setup(1280, 720, 30);
	
	seq_out.startExport(); // 書き出しスタート
}

void update() {
	// begin/endで囲んだ所を画像連番ファイルに書き出し
	seq_out.begin();
	ofClear(0);
	ofDrawBitmapString(ofToString(i), 0, 0);
	seq_out.end();
}

void draw() {
	// プレビュー
	ofSetColor(255);
	seq_out.draw(0 ,0);
}
```

書き出しができたらAfterEffectsに読み込み → エフェクトかけほうだい

---

## TIPS

- 毎回同じアニメーションになるように気をつける
	- 時間をキーにしてアニメーションを作るようにする
	- その場合、`ofGetElapsedTimef()`を使うとかかる処理時間のばらつきが出てしまうので注意
- ランダムを使う場合、`ofSeedRandom(int val)`を適当な値で明示的に呼んで初期化する

*今回は紹介のみにしておきますが [nariakiiwatani/ofxAE](https://github.com/nariakiiwatani/ofxAE) もカッコイイのでオススメ*

---

# 自習&質問

何かわからない事があれば質問ください

---

# MAXON Cinema 4D

## Alembicファイルフォーマット

### 概要

> SPIとILMが共同開発したシーンファイル共有フォーマットである。簡単に説明すると、異なる3Dアプリケーション間でシーンファイルをやり取りするための、互換性のある新しいファイルの規格  
[SPIとILMがシーンファイル共有フォーマット「Alembic」を共同開発](http://cgworld.jp/feature/report/alembic.html)

### ofxAlembic

[perfume-dev/ofxAlembic](https://github.com/perfume-dev/ofxAlembic)

- メッシュアニメーション
- パーティクル
- polyline
- カメラワーク

などが読み書きできる

*[あの人](https://twitter.com/zachlieberman/status/515407860776185856)も使っています*

---

## アニメーションの読み込み

とりあえず表示するだけなら何も考えなくていい

```cpp
#include "ofxAlembic.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxAlembic::Reader abc;
	
	void setup()
	{
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		ofBackground(0);
		
		abc.open("sample.abc");
		
		abc.dumpNames();
	}
	
	void update()
	{
		float abc_range = (abc.getMaxTime() - abc.getMinTime());
		float t = fmodf(ofGetElapsedTimef(), abc_range)
			+ abc.getMinTime();
		abc.setTime(t);
	}
	
	ofEasyCam cam;
	void draw()
	{
		cam.begin();
		ofNoFill();
		abc.draw();
		cam.end();
	}
};
```

---

## アニメーションの書き出し

Transform(Xform), Polymesh, Point(Particle), Polylineに対応。カメラはPRきてるけどまだ組み込んでないです

```cpp
#include "ofxAlembic.h"

class ofApp : public ofBaseApp {
public:
	ofxAlembic::Writer abc_out;
	ofMesh mesh;
	
	void setup() {
		float export_fps = 30;
		
		ofSetFrameRate(export_fps);
		ofSetVerticalSync(true);
		ofBackground(0);
		
		abc_out.open("out.abc", export_fps);
	}
	
	void update() {
		mesh.clear();
		
		for (int i = 0; i < 90; i++) {
			ofVec3f v(ofRandom(-100, 100), 
				ofRandom(-100, 100), 
				ofRandom(-100, 100));
			mesh.addVertex(v);
		}
		
		// export to abc
		abc_out.addPolyMesh("/mesh", mesh);
	}
	
	ofEasyCam cam;
	void draw() {
		cam.begin();
		mesh.drawWireframe();
		cam.end();
	}
};
```

---

