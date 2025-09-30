# Fract-ol プロジェクト概要ガイド

> **このドキュメントの目的**: fract-olプロジェクトの全体像をざっくり理解するための入門ガイド

---

## 📚 目次

1. [10秒で理解するfract-ol](#10秒で理解するfract-ol)
2. [5分で理解する全体アーキテクチャ](#5分で理解する全体アーキテクチャ)
3. [主要コンポーネント解説](#主要コンポーネント解説)
4. [データフロー図](#データフロー図)
5. [重要な概念](#重要な概念)
6. [実装の工夫ポイント](#実装の工夫ポイント)

---

## 10秒で理解するfract-ol

**fract-olは何？**
→ **フラクタル図形を美しく描画して、マウスでズームしたり移動したりできるインタラクティブなプログラム**

**どんな技術？**
→ **複素数の反復計算 + リアルタイムグラフィックス + イベント駆動プログラミング**

**何が難しい？**
→ **数学（複素数・対数）+ グラフィックス（座標変換）+ イベント処理（キー・マウス）の3つ全部**

---

## 5分で理解する全体アーキテクチャ

### プログラムの流れ

```
起動
 ↓
コマンドライン引数チェック
 ↓
初期化（MLX、ウィンドウ、画像バッファ）
 ↓
初回フラクタル描画
 ↓
イベントループ（無限ループ）
 ├─ キーボードイベント → 再描画
 ├─ マウスイベント → 再描画
 └─ ウィンドウイベント → 再描画
```

### ディレクトリ構造

```
fract-ol/
├── includes/           # ヘッダーファイル
│   ├── fractol.h       # 必須版の定義
│   └── fractol_bonus.h # ボーナス版の定義（Tricorn追加）
├── srcs/               # ソースコード
│   ├── main.c          # エントリーポイント（必須）
│   ├── main_bonus.c    # エントリーポイント（ボーナス）
│   ├── init.c          # 初期化処理
│   ├── draw.c          # 描画メイン
│   ├── events.c        # イベント処理（必須）
│   ├── events_bonus.c  # イベント処理（ボーナス）
│   ├── fractals.c      # フラクタル計算
│   ├── fractals_draw.c # フラクタル描画
│   ├── colors.c        # 配色処理
│   ├── utils.c         # ユーティリティ
│   ├── validation.c    # 入力検証
│   └── cleanup.c       # クリーンアップ
├── libft/              # カスタムC標準ライブラリ
├── mlx/                # MiniLibX グラフィックスライブラリ
└── docs/               # ドキュメント
```

### 主要データ構造

```c
// プログラム全体のデータ
t_data
├── mlx_ptr           // MiniLibXのポインタ
├── win_ptr           // ウィンドウポインタ
├── img               // 画像バッファ（t_img型）
├── fractal           // フラクタルパラメータ（t_fractal型）
├── width/height      // ウィンドウサイズ（800x600）

// 画像バッファ
t_img
├── img_ptr           // 画像メモリポインタ
├── addr              // ピクセルデータアドレス
├── bits_per_pixel    // ピクセルあたりのビット数
├── line_length       // 1行のバイト数
└── endian            // エンディアン

// フラクタルパラメータ
t_fractal
├── type              // フラクタルの種類（MANDELBROT / JULIA / TRICORN）
├── zoom              // ズーム倍率（初期値1.0）
├── offset_x/y        // 表示位置オフセット
├── julia_real/imag   // Juliaセットの複素数パラメータ
├── max_iter          // 最大反復回数（初期値100）
└── color_scheme      // 配色パターン（0-2）
```

---

## 主要コンポーネント解説

### 1. 初期化フェーズ（init.c）

**やること:**
1. MiniLibXの初期化（`mlx_init`）
2. ウィンドウ作成（800x600）
3. 画像バッファ作成（描画用メモリ確保）
4. フラクタルパラメータの初期設定

**重要な関数:**
- `init_data()` - すべての初期化を行う
- `cleanup_init_error()` - 初期化失敗時のメモリ解放

### 2. フラクタル計算エンジン（fractals.c）

**やること:**
複素数の反復計算を行い、各ピクセルが「集合の内部」か「外部」かを判定

**Mandelbrot集合の計算:**
```
z = 0（初期値）
繰り返し（最大100回）：
  z = z² + c
  |z| > 16 なら脱出（外部）
すべての反復を終えたら内部
```

**重要な関数:**
- `mandelbrot_calc_smooth()` - Mandelbrot計算
- `julia_calc_smooth()` - Julia計算
- `tricorn_calc_smooth()` - Tricorn計算（ボーナス）
- `calc_smooth_value()` - スムースカラーリング用の値計算

### 3. 描画システム（draw.c, fractals_draw.c）

**やること:**
1. 画面の各ピクセルをループ
2. ピクセル座標→複素平面座標に変換
3. フラクタル計算
4. 反復回数→色に変換
5. ピクセルに色を設定

**座標変換の仕組み:**
```
スクリーン座標 (0～800, 0～600)
      ↓
複素平面座標 (実部: -2～2, 虚部: -1.5～1.5)
```

**重要な関数:**
- `render_fractal()` - 描画のメイン制御
- `draw_mandelbrot()` / `draw_julia()` - 各フラクタルの描画
- `screen_to_complex_x/y()` - 座標変換

### 4. 配色システム（colors.c, colors_utils.c）

**やること:**
反復回数（0～100）を色（RGB値）に変換

**3つの配色パターン:**
1. **Psychedelic** - サイン波による虹色
2. **Sunset** - 夕焼け風グラデーション
3. **Ocean** - 深海ブルー

**重要な関数:**
- `get_color_smooth()` - 反復回数から色を計算
- `get_psychedelic_color()` / `get_sunset_color()` / `get_ocean_color()`

### 5. イベント処理（events.c, events_bonus.c）

**やること:**
ユーザーの操作（キー、マウス）に反応

**イベントの種類:**
- **キーボード**: ESC、矢印キー、+/-、C、R
- **マウス**: ホイールスクロール（ズーム）
- **ウィンドウ**: 閉じるボタン、最小化、復元

**重要な関数:**
- `key_hook()` - キーボードイベント処理
- `mouse_hook()` - マウスイベント処理
- `expose_hook()` - ウィンドウ再描画イベント
- `close_hook()` - 終了処理

---

## データフロー図

### 起動時のフロー

```
main()
  ↓
コマンドライン解析
  ↓
init_data()
  ├─ mlx_init()
  ├─ mlx_new_window()
  ├─ mlx_new_image()
  └─ mlx_get_data_addr()
  ↓
render_fractal()
  ├─ clear_image() - 画面クリア
  ├─ draw_mandelbrot/julia() - フラクタル描画
  │   └─ 各ピクセルごとに：
  │       ├─ screen_to_complex() - 座標変換
  │       ├─ mandelbrot_calc_smooth() - 計算
  │       ├─ get_color_smooth() - 色変換
  │       └─ my_mlx_pixel_put() - ピクセル描画
  └─ mlx_put_image_to_window() - 画面に転送
  ↓
イベントフック登録
  ├─ mlx_hook(12) - Expose
  ├─ mlx_key_hook() - キー
  ├─ mlx_mouse_hook() - マウス
  └─ mlx_hook(17) - 閉じる
  ↓
mlx_loop() - 無限ループ開始
```

### ズーム時のフロー

```
マウスホイール回転
  ↓
mouse_hook()
  ↓
マウス座標を複素平面座標に変換
  ↓
ズーム倍率を計算（1.1 or 0.9）
  ↓
新しいoffset計算
  offset = mouse_pos + (old_offset - mouse_pos) / zoom_factor
  ↓
render_fractal() - 再描画
  ↓
画面更新
```

---

## 重要な概念

### 1. 複素数とは

```
複素数 c = a + bi
  a: 実部（Real part）
  b: 虚部（Imaginary part）
  i: 虚数単位（i² = -1）

プログラム内では配列で表現：
  z[0] = 実部
  z[1] = 虚部
```

### 2. フラクタルとは

**定義**: どんなに拡大しても同じような複雑なパターンが現れる図形

**Mandelbrot集合**:
- 式: z = z² + c （z初期値0、cは座標）
- 「反復しても発散しない点の集合」

**Julia集合**:
- 式: z = z² + c （z初期値は座標、cは固定パラメータ）
- Mandelbrotと式は同じだが、初期値とパラメータが逆

**Tricorn（ボーナス）**:
- 式: z = conj(z)² + c （共役複素数を使用）
- Mandelbrotの変種

### 3. エスケープタイム法

**原理**:
「何回反復したら|z| > 4になるか」を数える

```c
iter = 0
while (iter < max_iter && |z|² < 16) {
    z = z² + c
    iter++
}
return iter  // この値を色に変換
```

### 4. スムースカラーリング

**問題**: 整数の反復回数だと色に段差ができる（バンディング）

**解決**: 対数を使って小数点以下の精度を追加

```c
smooth = iter + 1 - log(log(|z|)) / log(2)
```

これで色が滑らかに変化する

### 5. 座標変換

**スクリーン座標 → 複素平面座標**

```c
// x: 0～800 → real: -2～2
real = (x / width - 0.5) * 4.0 / zoom + offset_x

// y: 0～600 → imag: -1.5～1.5
imag = (y / height - 0.5) * 3.0 / zoom + offset_y
```

ズームとオフセットで表示範囲を調整

---

## 実装の工夫ポイント

### 1. パフォーマンス最適化

**計算の工夫:**
```c
// 遅い書き方
if (sqrt(z_real² + z_imag²) > 4)

// 速い書き方（平方根計算を省略）
if (z_real² + z_imag² > 16)  // 4² = 16
```

**変数の再利用:**
```c
z_sq[0] = z[0] * z[0];  // 一度計算
z_sq[1] = z[1] * z[1];
// z_sq[0]とz_sq[1]を複数回使う
```

### 2. メモリ管理

**画像バッファの直接操作:**
```c
// 遅い: mlx_pixel_put()を毎回呼ぶ
mlx_pixel_put(mlx, win, x, y, color);

// 速い: バッファに直接書き込んで最後に一括転送
dst = img.addr + (y * line_length + x * bytes_per_pixel);
*(int *)dst = color;
mlx_put_image_to_window(mlx, win, img, 0, 0);
```

**エラー時のクリーンアップ:**
```c
// 初期化に失敗したら、それまで確保したメモリを全部解放
cleanup_init_error(data);
```

### 3. ユーザビリティ

**ズーム位置の調整:**
```c
// マウス位置を固定点としてズーム
new_offset = mouse_pos + (old_offset - mouse_pos) / zoom_factor
```

**移動量の調整:**
```c
// ズームに応じて移動量を変化
move_amount = 0.1 / zoom  // 拡大時は細かく、縮小時は大きく
```

### 4. コード品質

**関数の責任分離:**
- `main.c` - エントリーポイントのみ
- `fractals.c` - 計算のみ
- `draw.c` - 描画のみ
- `events.c` - イベント処理のみ

**Norm準拠:**
- 1関数25行以内
- 1関数5変数以内
- 1ファイル5関数以内

**エラーハンドリング:**
- すべてのmalloc/MLX関数の戻り値をチェック
- エラー時は適切なメッセージを表示して終了

---

## 次に読むべきドキュメント

1. **基本を理解したら** → `CODE_GUIDE.md`（詳細なコード解説）
2. **数学を深掘りしたい** → `MATH_DETAILS.md`（複素数・フラクタル理論）
3. **実装方法を知りたい** → `implementation_plan.md`（実装手順）
4. **テストしたい** → `TESTING.md`（テスト方法）

---

**このドキュメントで全体像を掴んでから、各詳細ドキュメントに進むことをおすすめします！** 🚀