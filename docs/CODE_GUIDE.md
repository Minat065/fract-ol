# fract-ol 完全理解ガイド・レビュー対策書（超詳細版）

## 📚 目次
1. [プロジェクト全体像](#1-プロジェクト全体像)
2. [フラクタルの数学的基礎](#2-フラクタルの数学的基礎)
3. [コード構造の完全解説](#3-コード構造の完全解説)
4. [レビュー頻出質問と回答例](#4-レビュー頻出質問と回答例)
5. [デモンストレーション手順](#5-デモンストレーション手順)
6. [トラブルシューティング](#6-トラブルシューティング)

---

## 0. レビュー前に絶対に覚えること（10分で確認）

### 最重要ポイント3つ
1. **Mandelbrot vs Julia の違い**
   - Mandelbrot: c = ピクセル座標、z初期値 = 0
   - Julia: c = 固定パラメータ、z初期値 = ピクセル座標

2. **発散条件**
   - |z|² > 4.0 で発散と判定（√を取らないため2²=4で比較）

3. **ズームの仕組み**
   - マウス位置を複素平面座標に変換
   - その座標を中心にズーム倍率を変更
   - オフセットを調整して中心をキープ

### レビューで100%聞かれる質問TOP5
1. 「この関数は何をしていますか？」→ 各関数の説明を2行で言えるようにする
2. 「MandelbrotとJuliaの違いは？」→ 上記を即答
3. 「ズーム機能の実装方法は？」→ 座標変換の流れを説明
4. 「色はどうやって計算していますか？」→ イテレーション数→正規化→RGB変換
5. 「メモリリークはありませんか？」→ cleanup関数を説明

---

## 1. プロジェクト全体像

### 1.1 プロジェクトの目的（1行で説明できるように）
**「複素数の漸化式の挙動を可視化し、美しいフラクタル図形をインタラクティブに探索するプログラム」**

レビュアーに説明する時:
> 「このプロジェクトは、Mandelbrot集合やJulia集合といったフラクタルをリアルタイムで描画し、
> ズームやパンなどの操作でユーザーが自由に探索できるプログラムです。
> 複素数の反復計算を使って各ピクセルの発散速度を判定し、それを色で表現しています。」

### 1.2 プログラムの動作フロー（詳細版）
```
[1] プログラム起動（main.c:main）
    ↓
[2] コマンドライン引数をチェック
    - mandelbrot: argc==2, argv[1]=="mandelbrot"
    - julia: argc==4, argv[1]=="julia", argv[2]=実部, argv[3]=虚部
    ↓
[3] MLXライブラリを初期化（init.c:init_mlx）
    - mlx_init(): MLXとの接続を確立
    - mlx_new_window(): 800x600のウィンドウを作成
    - mlx_new_image(): 描画用の画像バッファを作成
    ↓
[4] フラクタルパラメータを初期化（init.c:init_fractal）
    - zoom = 1.0（初期ズーム）
    - offset_x = 0.0, offset_y = 0.0（中心座標）
    - max_iter = 100（最大反復回数）
    - color_scheme = 0（初期カラースキーム）
    ↓
[5] 初回描画を実行（draw.c:render_fractal）
    - 全ピクセル(800x600=480,000ピクセル)を順次処理
    - 各ピクセルでフラクタル計算→色計算→ピクセル描画
    ↓
[6] イベントフックを登録（events.c）
    - mlx_key_hook(): キーボードイベント
    - mlx_mouse_hook(): マウスクリック・ホイール
    - mlx_hook(17, ...): ウィンドウ閉じるボタン
    ↓
[7] イベントループに入る（main.c）
    - mlx_loop(): 無限ループでイベント待機
    ↓
[8] イベント発生時の処理
    - キー押下 → key_hook() → render_fractal()
    - マウス操作 → mouse_hook() → render_fractal()
    - ESC or ×ボタン → cleanup() → exit(0)
```

### 1.3 ファイル構成と役割（超詳細版）
```
fractol/
├── srcs/
│   ├── main.c
│   │   └── 役割: プログラムのエントリポイント
│   │       - main(): 引数解析とフラクタル起動
│   │       - run_mandelbrot(): Mandelbrot集合を起動
│   │       - run_julia(): Julia集合を起動
│   │       - print_usage(): ヘルプメッセージ表示
│   │
│   ├── init.c
│   │   └── 役割: 初期化処理
│   │       - init_mlx(): MLXライブラリ初期化
│   │       - init_window(): ウィンドウ作成
│   │       - init_image(): 画像バッファ作成
│   │       - init_fractal(): フラクタルパラメータ設定
│   │       - init_data(): 全体のデータ構造初期化
│   │
│   ├── fractals.c
│   │   └── 役割: フラクタル計算のコア
│   │       - mandelbrot_calc(): Mandelbrot集合の計算
│   │       - mandelbrot_calc_smooth(): スムーズカラー対応版
│   │       - julia_calc(): Julia集合の計算
│   │       - julia_calc_smooth(): スムーズカラー対応版
│   │
│   ├── draw.c
│   │   └── 役割: 描画制御
│   │       - render_fractal(): 描画全体の制御
│   │       - draw_mandelbrot(): Mandelbrot描画ループ
│   │       - draw_julia(): Julia描画ループ
│   │       - my_mlx_pixel_put(): ピクセル描画
│   │       - clear_image(): 画像バッファクリア
│   │
│   ├── events.c
│   │   └── 役割: イベント処理
│   │       - key_hook(): キーボード入力処理
│   │       - mouse_hook(): マウスボタン・ホイール処理
│   │       - close_hook(): ウィンドウ閉じるボタン処理
│   │       - handle_zoom(): ズーム処理の詳細
│   │       - handle_move(): 移動処理の詳細
│   │
│   ├── colors.c
│   │   └── 役割: 色彩計算
│   │       - get_color(): イテレーション数から色を取得
│   │       - get_color_smooth(): スムーズカラーリング
│   │       - get_psychedelic_color(): サイケデリックスキーム
│   │       - get_sunset_color(): サンセットスキーム
│   │       - get_ocean_color(): オーシャンスキーム
│   │       - create_rgb(): RGB値を統合
│   │
│   ├── utils.c
│   │   └── 役割: ユーティリティ関数
│   │       - screen_to_complex_x(): スクリーンX座標→複素平面実部
│   │       - screen_to_complex_y(): スクリーンY座標→複素平面虚部
│   │       - complex_to_screen_x(): 複素平面実部→スクリーンX座標
│   │       - complex_to_screen_y(): 複素平面虚部→スクリーンY座標
│   │       - ft_atof(): 文字列→浮動小数点数変換
│   │
│   └── validation.c
│       └── 役割: 入力検証
│           - validate_fractal_name(): フラクタル名チェック
│           - validate_julia_params(): Juliaパラメータチェック
│           - is_valid_number(): 数値文字列の妥当性チェック
│
├── includes/
│   └── fractol.h
│       └── 内容:
│           - マクロ定義（WIDTH, HEIGHT, MAX_ITER等）
│           - 列挙型（t_fractal_type）
│           - 構造体定義（t_img, t_fractal, t_data）
│           - 関数プロトタイプ全て
│           - 標準ライブラリのインクルード
│
├── libft/
│   └── 42schoolのカスタムライブラリ
│       - ft_strncmp(): 文字列比較
│       - ft_putstr_fd(): 文字列出力
│       - ft_atof(): 文字列→浮動小数点（カスタム実装）
│       - その他のユーティリティ関数
│
└── Makefile
    └── ビルドルール:
        - all: プロジェクトをビルド
        - clean: .oファイルを削除
        - fclean: 全ての生成物を削除
        - re: リビルド
        - 依存関係: libft/libft.a, mlx/libmlx.a
```

---

## 2. フラクタルの数学的基礎（ゼロから理解）

### 2.1 複素数の超基本（中学数学レベルから）

#### 複素数とは何か？
```
実数: 1, 2, 3.14, -5 など、普通の数
虚数: √(-1) = i という架空の数（でも数学では超便利）
複素数: 実数 + 虚数 = a + bi の形の数

例: z = -0.7 + 0.27i
    ↑実部    ↑虚部
```

#### C言語での表現
```c
// 複素数 z = a + bi を2つの変数で表現
double z_real = -0.7;   // 実部（real part）
double z_imag = 0.27;   // 虚部（imaginary part）
```

#### 複素数の計算（コードで使う操作）
```c
// 1. 複素数の足し算: (a+bi) + (c+di) = (a+c) + (b+d)i
z1_real + z2_real = 新しい実部
z1_imag + z2_imag = 新しい虚部

// 2. 複素数の掛け算: (a+bi) × (c+di) = (ac-bd) + (ad+bc)i
// ※ i²=-1 を使う
新実部 = a*c - b*d
新虚部 = a*d + b*c

// 3. 複素数の2乗: (a+bi)² = a²-b² + 2abi
z_real_new = z_real*z_real - z_imag*z_imag
z_imag_new = 2 * z_real * z_imag

// 4. 複素数の絶対値（大きさ）: |z| = √(a²+b²)
magnitude = sqrt(z_real*z_real + z_imag*z_imag)
// ただし実装では |z|² = a²+b² を使う（√を計算しないため高速）
magnitude_squared = z_real*z_real + z_imag*z_imag
```

### 2.2 Mandelbrot集合とは（超わかりやすく）

#### 1行での説明
**「複素平面上で、点cを使って z = z² + c を繰り返したとき、無限に大きくならない点の集合」**

#### 料理のレシピ風の説明
```
材料: 複素数 c（テストしたい点）
道具: 漸化式 z_{n+1} = z_n² + c
初期値: z₀ = 0

手順:
1. z₀ = 0 から始める
2. z₁ = z₀² + c を計算
3. z₂ = z₁² + c を計算
4. z₃ = z₂² + c を計算
5. ...これを繰り返す

判定:
- zがどんどん大きくなる（発散） → cはMandelbrot集合の外
- zが小さいまま（収束） → cはMandelbrot集合の中
```

#### 具体例で理解（手計算）
```
例1: c = 0 + 0i の場合
z₀ = 0
z₁ = 0² + 0 = 0
z₂ = 0² + 0 = 0
→ ずっと0のまま = 集合の中

例2: c = 1 + 0i の場合
z₀ = 0
z₁ = 0² + 1 = 1
z₂ = 1² + 1 = 2
z₃ = 2² + 1 = 5
z₄ = 5² + 1 = 26
→ どんどん大きくなる = 集合の外

例3: c = -1 + 0i の場合
z₀ = 0
z₁ = 0² + (-1) = -1
z₂ = (-1)² + (-1) = 1 - 1 = 0
z₃ = 0² + (-1) = -1
z₄ = (-1)² + (-1) = 0
→ -1と0を行ったり来たり = 集合の中
```

#### 発散条件（重要！）
```
数学的証明: |z| > 2 になったら、必ず無限大に発散する

コードでの実装:
|z|² = z_real² + z_imag² > 4.0 で判定
（√を計算しないため、2²=4で比較）

なぜ4.0なのか？
|z| > 2 の両辺を2乗すると
|z|² > 4
つまり z_real² + z_imag² > 4.0
```

```c
// Mandelbrot集合の判定アルゴリズム（完全コメント版）
// 点c(complex_x, complex_y)がMandelbrot集合に属するか？
int mandelbrot_calc(double complex_x, double complex_y, int max_iter)
{
    // ステップ1: z の初期値を0に設定（Mandelbrotの定義）
    double z_real = 0.0;     // z の実部（初期値0）
    double z_imag = 0.0;     // z の虚部（初期値0）
    int iter = 0;            // 反復回数カウンタ

    // ステップ2: 最大反復回数まで繰り返す
    while (iter < max_iter) {
        // 最適化: 2乗を事前に計算（何度も使うため）
        double z_real_sq = z_real * z_real;  // z実部の２乗
        double z_imag_sq = z_imag * z_imag;  // z虚部の２乗

        // ステップ3: 発散条件をチェック
        // |z|² = z_real² + z_imag² > 4.0 なら発散確定
        if (z_real_sq + z_imag_sq > 4.0) {
            return iter;  // 発散するまでの回数を返す
                         // この値が小さいほど早く発散（集合の外側）
        }

        // ステップ4: z = z² + c の計算（漸化式の核心）
        // 複素数の2乗: (a+bi)² = (a²-b²) + (2ab)i

        // 実部の計算: real(z²) + real(c)
        // = (z_real² - z_imag²) + complex_x
        double temp = z_real_sq - z_imag_sq + complex_x;

        // 虚部の計算: imag(z²) + imag(c)
        // = (2 * z_real * z_imag) + complex_y
        z_imag = 2.0 * z_real * z_imag + complex_y;

        // 新しい実部を設定（tempを使って順序を正しく）
        z_real = temp;

        // 反復回数をインクリメント
        iter++;
    }

    // ステップ5: max_iterまで発散しなかった場合
    return iter;  // 集合の内部と判定
}
```

**コードの各行の意味（レビューで説明できるように）:**

1. **z_real = 0.0, z_imag = 0.0**
   - Mandelbrot集合の定義：z₀ = 0 から始める
   - Juliaとの違いはここ（Juliaはピクセル座標から始める）

2. **z_real_sq = z_real * z_real**
   - 最適化テクニック：2乗を複数回使うので事前計算
   - 計算回数を削減してパフォーマンス向上

3. **if (z_real_sq + z_imag_sq > 4.0)**
   - 発散判定：|z|² > 4 は数学的に証明された条件
   - √計算を避けるため2乗のまま比較（高速化）

4. **temp = z_real_sq - z_imag_sq + complex_x**
   - (a+bi)² = a²-b² + 2abi の実部を計算
   - complex_xがパラメータc（ピクセル座標）の実部

5. **z_imag = 2.0 * z_real * z_imag + complex_y**
   - (a+bi)² の虚部を計算
   - complex_yがパラメータcの虚部

6. **return iter**
   - 早く発散（iterが小さい）= 明るい色
   - 遅く発散（iterが大きい）= 暗い色
   - 発散しない（iter=max_iter）= 黒（集合内部）

**重要ポイント（レビューで絶対聞かれる）:**
```
Q: なぜz_realとz_imagを同時に更新しないのか？
A: 新しいz_imagの計算に古いz_realが必要だから。
   同時に更新すると、z_imagの計算で新しいz_realを使ってしまい、
   数式が正しく計算できなくなる。
   だからtempを使って一時保存する。

Q: なぜ4.0と比較するのか？
A: 数学的定理：|z| > 2 なら必ず発散する
   |z| > 2 の両辺を2乗 → |z|² > 4
   √計算をスキップして高速化

Q: max_iterはどう決めるのか？
A: トレードオフ：
   - 大きい（例:1000）→ 詳細だが遅い
   - 小さい（例:50）→ 粗いが速い
   - 推奨値: 100-300
```

### 2.3 Julia集合とは（超詳細解説）

#### 1行での説明
**「固定されたパラメータcに対して z = z² + c を計算し、初期値zが発散しない点の集合」**

#### MandelbrotとJuliaの決定的な違い
```
同じ漸化式: z_{n+1} = z_n² + c

Mandelbrot集合:
  - c = 各ピクセルの座標（変化する）
  - z₀ = 0（固定）
  - 質問: 「このcで始めたら発散するか？」
  - 結果: 1つのMandelbrot集合図形

Julia集合:
  - c = 固定パラメータ（コマンドライン引数、変化しない）
  - z₀ = 各ピクセルの座標（変化する）
  - 質問: 「このz₀から始めたら発散するか？」
  - 結果: cの値ごとに異なる無限のJulia集合図形
```

#### 視覚的な理解
```
Mandelbrot集合（1種類のみ）:
  ./fractol mandelbrot
  → 常に同じ特徴的な形（カーディオイド+円形バルブ）

Julia集合（無限のバリエーション）:
  ./fractol julia -0.7 0.27015   → ドラゴン型
  ./fractol julia -0.4 0.6        → スパイラル型
  ./fractol julia 0.285 0.01      → 樹木型
  ./fractol julia -0.123 -0.745   → 複雑な模様
  → cの値を変えるだけで全く異なる形に
```

#### なぜcの値で形が変わるのか？
```
cの役割:
- Mandelbrot: 「テストする点」として機能
- Julia: 「力の方向」として機能

例え話:
- Mandelbrot = 「この土地に家を建てたら地盤は安定しているか？」
  → 各地点（c）をテスト
- Julia = 「東向きの風（固定c）が吹いたとき、どの地点（z₀）が安全か？」
  → 固定された条件下で各地点をテスト
```

#### Julia集合のコード実装（完全解説）
```c
// Julia集合の計算（Mandelbrotとの違いを明確に）
int julia_calc(double pixel_x, double pixel_y, t_data *data)
{
    // 【重要な違い1】z の初期値 = 各ピクセルの座標
    double z_real = pixel_x;  // ピクセルのX座標が初期値の実部
    double z_imag = pixel_y;  // ピクセルのY座標が初期値の虚部

    // 【重要な違い2】c は固定パラメータ
    // コマンドライン引数 ./fractol julia -0.7 0.27015 で指定された値
    double c_real = data->fractal.julia_real;  // 例: -0.7
    double c_imag = data->fractal.julia_imag;  // 例: 0.27015

    int iter = 0;
    int max_iter = data->fractal.max_iter;

    // 【同じ部分】発散判定ループ
    while (iter < max_iter) {
        double z_real_sq = z_real * z_real;
        double z_imag_sq = z_imag * z_imag;

        // 発散判定
        if (z_real_sq + z_imag_sq > 4.0) {
            return iter;
        }

        // z = z² + c の計算
        // 【注意】ここではcが固定値、zが変化する
        double temp = z_real_sq - z_imag_sq + c_real;  // 固定のc_real
        z_imag = 2.0 * z_real * z_imag + c_imag;       // 固定のc_imag
        z_real = temp;

        iter++;
    }

    return iter;
}
```

#### コードの対比（並べて理解）
```c
// Mandelbrot vs Julia の実装の違い

// ========== Mandelbrot ==========
double z_real = 0.0;              // ← 常に0
double z_imag = 0.0;              // ← 常に0
double c_real = pixel_x;          // ← ピクセル座標
double c_imag = pixel_y;          // ← ピクセル座標

while (...) {
    // z = z² + c
    temp = z_real_sq - z_imag_sq + c_real;  // c はピクセル
    z_imag = 2*z_real*z_imag + c_imag;      // c はピクセル
}

// ========== Julia ==========
double z_real = pixel_x;          // ← ピクセル座標
double z_imag = pixel_y;          // ← ピクセル座標
double c_real = julia_real;       // ← 固定パラメータ
double c_imag = julia_imag;       // ← 固定パラメータ

while (...) {
    // z = z² + c
    temp = z_real_sq - z_imag_sq + c_real;  // c は固定
    z_imag = 2*z_real*z_imag + c_imag;      // c は固定
}
```

#### 有名なJuliaパラメータ（デモ用に覚えておく）
```bash
# ドラゴン型（最も有名）
./fractol julia -0.7 0.27015
# → ドラゴンのような形、フラクタルの代表例

# スパイラル型
./fractol julia -0.4 0.6
# → 渦巻き状の美しいパターン

# デンドライト型（樹木）
./fractol julia 0.285 0.01
# → 木の枝のような形

# 複雑型
./fractol julia -0.123 -0.745
# → 複雑に入り組んだ模様

# ほぼ円形（安定）
./fractol julia 0.0 0.0
# → 円に近い形、最も安定したパターン

# 断片化
./fractol julia -0.8 0.156
# → バラバラに分散した形
```

#### レビューで説明する時のテンプレート
```
「MandelbrotとJuliaは同じ漸化式 z = z² + c を使いますが、
変数と定数が逆になっています。

Mandelbrotは『どの点cが安定しているか』を調べるため、
各ピクセルをcとして使い、z₀=0 から計算を始めます。
結果は1つの特徴的な図形になります。

Juliaは『固定されたcの下で、どの初期値z₀が安定しているか』を調べるため、
cは引数で固定し、各ピクセルをz₀として計算を始めます。
cの値を変えると全く異なる図形が現れるため、
無限のバリエーションが存在します。

数学的には、全てのJulia集合を集めたものがMandelbrot集合になる
という関係があります。」
```

---

## 3. コード構造の完全解説

### 3.1 データ構造の理解

```c
// メインのデータ構造（全てのプログラム状態を管理）
typedef struct s_data {
    void        *mlx_ptr;    // MinilibXの接続ポインタ
    void        *win_ptr;    // ウィンドウのポインタ
    t_img       img;         // 描画用画像の情報
    t_fractal   fractal;     // フラクタルの設定・状態
    int         width;       // ウィンドウ幅
    int         height;      // ウィンドウ高さ
} t_data;

// 画像データの管理
typedef struct s_img {
    void    *img_ptr;        // 画像オブジェクト
    char    *addr;           // ピクセルデータの先頭アドレス
    int     bits_per_pixel;  // 1ピクセルあたりのビット数
    int     line_length;     // 1行のバイト数
    int     endian;          // バイトオーダー
} t_img;

// フラクタルの設定と状態
typedef struct s_fractal {
    t_fractal_type  type;         // MANDELBROT or JULIA
    double          zoom;         // ズーム倍率
    double          offset_x;     // X方向オフセット
    double          offset_y;     // Y方向オフセット
    double          julia_real;   // Julia集合のパラメータ（実部）
    double          julia_imag;   // Julia集合のパラメータ（虚部）
    int             max_iter;     // 最大イテレーション数
    int             color_scheme; // カラースキーム番号
} t_fractal;
```

### 3.2 プログラムの実行フロー

#### Step 1: main.c - エントリポイント
```c
int main(int argc, char **argv)
{
    // 1. 引数をチェック
    if (argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 11))
        run_mandelbrot();  // Mandelbrot集合を表示
    else if (argc == 4 && !ft_strncmp(argv[1], "julia", 6))
        run_julia(ft_atof(argv[2]), ft_atof(argv[3]));  // Julia集合を表示
    else {
        print_usage();  // 使用方法を表示
        return (1);
    }
    return (0);
}
```

#### Step 2: init.c - 初期化処理
```c
int init_data(t_data *data, t_fractal_type type, double julia_r, double julia_i)
{
    // 1. MLXライブラリを初期化
    data->mlx_ptr = mlx_init();

    // 2. ウィンドウを作成
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Fractol");

    // 3. 描画用画像を作成
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img_ptr,
        &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);

    // 4. フラクタルの初期設定
    data->fractal.type = type;
    data->fractal.zoom = 1.0;           // 初期ズーム
    data->fractal.offset_x = 0.0;       // 中心位置
    data->fractal.offset_y = 0.0;
    data->fractal.max_iter = MAX_ITER;  // イテレーション数
    data->fractal.color_scheme = 0;     // カラースキーム

    // Julia集合の場合はパラメータを設定
    if (type == JULIA) {
        data->fractal.julia_real = julia_r;
        data->fractal.julia_imag = julia_i;
    }
}
```

#### Step 3: draw.c - 描画処理
```c
void render_fractal(t_data *data)
{
    clear_image(data);  // 画像をクリア

    // フラクタルタイプに応じて描画関数を選択
    if (data->fractal.type == MANDELBROT)
        draw_mandelbrot(data);
    else if (data->fractal.type == JULIA)
        draw_julia(data);

    // 画像をウィンドウに表示
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0, 0);
}
```

#### Step 4: fractals.c - フラクタル計算
```c
void draw_mandelbrot(t_data *data)
{
    int x, y;

    // 画面の全ピクセルを処理
    for (y = 0; y < data->height; y++) {
        for (x = 0; x < data->width; x++) {
            // 1. スクリーン座標を複素平面座標に変換
            double complex_x = screen_to_complex_x(x, data);
            double complex_y = screen_to_complex_y(y, data);

            // 2. そのピクセルでのMandelbrot計算
            double smooth_iter = mandelbrot_calc_smooth(complex_x, complex_y,
                data->fractal.max_iter);

            // 3. イテレーション数から色を計算
            int color = get_color_smooth(smooth_iter, data->fractal.max_iter,
                data->fractal.color_scheme);

            // 4. ピクセルに色を設定
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}
```

### 3.3 座標変換の仕組み（超詳細・図解付き）

#### なぜ座標変換が必要なのか？
```
問題:
- コンピュータの画面 = ピクセル座標（整数）
  例: (0,0)～(800,600)、左上が原点
- フラクタルの数学 = 複素平面座標（実数）
  例: (-2.0, -2.0)～(2.0, 2.0)、中心が原点

解決:
スクリーン座標 ⇔ 複素平面座標 の相互変換関数を実装
```

#### 座標変換の全ステップ（完全図解）
```
【ステップ1】スクリーン座標（ピクセル単位）
  画面サイズ: 800x600
  原点: 左上 (0, 0)
  範囲: X = 0～800, Y = 0～600
  例: マウスカーソル位置 (400, 300)

        ↓ ÷ width, ÷ height

【ステップ2】正規化座標（0～1の範囲）
  X = screen_x / width = 400 / 800 = 0.5
  Y = screen_y / height = 300 / 600 = 0.5
  範囲: 0.0～1.0

        ↓ (x - 0.5) * 2.0

【ステップ3】中心原点座標（-1～1の範囲）
  X = (0.5 - 0.5) * 2.0 = 0.0
  Y = (0.5 - 0.5) * 2.0 = 0.0
  範囲: -1.0～1.0
  原点: 画面中央

        ↓ × scale_factor / zoom + offset

【ステップ4】複素平面座標（フラクタル計算用）
  X = 0.0 * 4.0 / 1.0 + 0.0 = 0.0
  Y = 0.0 * 4.0 / 1.0 + 0.0 = 0.0
  範囲: -2.0～2.0（初期状態）
  原点: 複素平面の原点 (0+0i)
```

#### コード実装（完全コメント版）
```c
// X座標の変換: スクリーン → 複素平面
double screen_to_complex_x(int screen_x, t_data *data)
{
    // ステップ1: ピクセル座標を0～1に正規化
    // screen_x = 0   → normalized = 0.0（画面左端）
    // screen_x = 400 → normalized = 0.5（画面中央）
    // screen_x = 800 → normalized = 1.0（画面右端）
    double normalized = (double)screen_x / (double)data->width;

    // ステップ2: 0～1を-1～1に変換（原点を中央に）
    // normalized = 0.0 → centered = -1.0（左端）
    // normalized = 0.5 → centered =  0.0（中央）
    // normalized = 1.0 → centered =  1.0（右端）
    double centered = (normalized - 0.5) * 2.0;

    // ステップ3: ズームとオフセットを適用
    // - centered * 4.0: 複素平面の範囲を-2～2に拡大
    // - / zoom: ズーム倍率を適用（zoom=2なら範囲が半分に）
    // - + offset_x: 表示位置をずらす（パン機能）
    double complex_x = centered * 4.0 / data->fractal.zoom;
    complex_x += data->fractal.offset_x;

    return complex_x;
}

// Y座標の変換: スクリーン → 複素平面
double screen_to_complex_y(int screen_y, t_data *data)
{
    // X座標と同じロジック
    double normalized = (double)screen_y / (double)data->height;
    double centered = (normalized - 0.5) * 2.0;
    double complex_y = centered * 4.0 / data->fractal.zoom;
    complex_y += data->fractal.offset_y;

    return complex_y;
}
```

#### 具体的な計算例（数値で理解）
```
画面設定:
- width = 800, height = 600
- zoom = 1.0（初期状態）
- offset_x = 0.0, offset_y = 0.0

例1: 画面左上 (0, 0)
  normalized_x = 0 / 800 = 0.0
  centered_x = (0.0 - 0.5) * 2.0 = -1.0
  complex_x = -1.0 * 4.0 / 1.0 + 0.0 = -4.0

例2: 画面中央 (400, 300)
  normalized_x = 400 / 800 = 0.5
  centered_x = (0.5 - 0.5) * 2.0 = 0.0
  complex_x = 0.0 * 4.0 / 1.0 + 0.0 = 0.0

例3: 画面右下 (800, 600)
  normalized_x = 800 / 800 = 1.0
  centered_x = (1.0 - 0.5) * 2.0 = 1.0
  complex_x = 1.0 * 4.0 / 1.0 + 0.0 = 4.0

結論: 画面全体が複素平面の -4.0～4.0 の範囲に対応
```

#### ズーム時の変化（重要！）
```
zoom = 1.0（初期状態）:
  範囲 = -4.0～4.0 / 1.0 = -4.0～4.0（広い範囲）

zoom = 2.0（2倍ズーム）:
  範囲 = -4.0～4.0 / 2.0 = -2.0～2.0（半分の範囲 = 拡大）

zoom = 10.0（10倍ズーム）:
  範囲 = -4.0～4.0 / 10.0 = -0.4～0.4（1/10の範囲 = 大幅拡大）

zoom = 0.5（0.5倍ズーム）:
  範囲 = -4.0～4.0 / 0.5 = -8.0～8.0（2倍の範囲 = 縮小）
```

#### オフセットの働き（パン機能）
```
offset_x = 0.0, offset_y = 0.0:
  中心座標 = (0.0, 0.0)（複素平面の原点）

offset_x = 1.0, offset_y = 0.0:
  中心座標 = (1.0, 0.0)（右に1単位移動）

offset_x = -0.5, offset_y = 0.5:
  中心座標 = (-0.5, 0.5)（左上に移動）
```

#### レビューで説明する時のポイント
```
「座標変換は4つのステップで行います。

1. ピクセル座標を幅と高さで割って0～1に正規化
2. 0.5を引いて2倍することで-1～1に変換（中心を原点に）
3. 4.0を掛けて複素平面の初期範囲-2～2（実際は-4～4）にスケール
4. ズーム倍率で割り、オフセットを加えて最終的な複素平面座標を得る

ズームは除算で実現：zoom=2なら範囲が1/2になり拡大効果
オフセットは加算で実現：中心座標をずらすことでパン操作を実現

この変換により、画面の各ピクセルが複素平面上のどの点に対応するか
を正確に計算できます。」
```

---

## 4. レビュー頻出質問と回答例

### Q1: 「この関数を説明してください」
**頻出対象: `mandelbrot_calc_smooth`**

**回答例:**
```
この関数はMandelbrot集合の判定を行います。
入力の複素数座標(real, imag)に対して、漸化式 z = z² + c を繰り返し計算し、
|z|が発散する（2を超える）までのイテレーション数を返します。

スムーズカラーリングのため、発散時の正確な値も計算しています。
戻り値が小さいほど早く発散（集合外部）、大きいほど集合内部に近いことを意味します。
```

### Q2: 「ズーム機能はどう実装していますか？」（最重要！）

#### 簡単なズーム vs マウス中心ズーム

**簡単なズーム（ボーナス点なし）:**
```c
// 画面中央を中心にズーム
data->fractal.zoom *= 1.1;  // ズームイン
render_fractal(data);
```
→ 常に画面中央にズーム、使いにくい

**マウス中心ズーム（ボーナス点あり）:**
```c
// マウスカーソルの位置を中心にズーム
// オフセットも調整する必要がある
```
→ マウスの位置にズーム、直感的で使いやすい

#### マウス中心ズームの数学（理解必須）

**問題設定:**
```
現在の状態:
- zoom = 1.0
- offset = (0, 0)
- マウス位置 = スクリーン座標 (600, 200)
  → 複素平面座標 (1.0, -1.0)

やりたいこと:
- zoom を 2.0 に変更（2倍ズーム）
- マウス位置 (1.0, -1.0) が画面上で動かないようにしたい

問題:
- ズームだけ変えると、マウス位置がずれる
- オフセットも同時に調整する必要がある
```

**解決策の数学:**
```
公式（暗記推奨）:
new_offset = mouse_pos + (old_offset - mouse_pos) / zoom_factor

説明:
1. (old_offset - mouse_pos): マウスから現在の中心までのベクトル
2. / zoom_factor: ズーム後の新しいベクトル
3. mouse_pos + ...: マウス位置を起点に新しい中心を計算

zoom_factor:
- ズームイン: 1.1（10%拡大）
- ズームアウト: 0.9（10%縮小）
```

**具体例で理解:**
```
初期状態:
- offset = (0, 0)
- zoom = 1.0
- mouse_pos = (1.0, -1.0)

ズームイン（zoom_factor = 1.1）:
1. old_offset - mouse_pos = (0, 0) - (1.0, -1.0) = (-1.0, 1.0)
2. (-1.0, 1.0) / 1.1 = (-0.909, 0.909)
3. new_offset = (1.0, -1.0) + (-0.909, 0.909) = (0.091, -0.091)
4. new_zoom = 1.0 * 1.1 = 1.1

結果: マウス位置 (1.0, -1.0) が画面上で動かない
```

#### 完全実装コード（コメント付き）
```c
// マウスホイールでズーム（events.c の mouse_hook）
int mouse_hook(int button, int x, int y, t_data *data)
{
    // ボタン4 = ホイール上（ズームイン）
    // ボタン5 = ホイール下（ズームアウト）
    if (button == 4 || button == 5) {
        // ===== ステップ1: マウス位置を複素平面座標に変換 =====
        // 現在のズーム・オフセット状態での複素平面座標
        double mouse_real = screen_to_complex_x(x, data);
        double mouse_imag = screen_to_complex_y(y, data);

        // ===== ステップ2: ズーム倍率を決定 =====
        // button == 4: ズームイン（1.1倍 = 10%拡大）
        // button == 5: ズームアウト（0.9倍 = 10%縮小）
        double zoom_factor = (button == 4) ? 1.1 : 0.9;

        // ===== ステップ3: オフセットを調整（最重要！）=====
        // 公式: new_offset = mouse_pos + (old_offset - mouse_pos) / zoom_factor

        // X方向のオフセット調整
        data->fractal.offset_x = mouse_real +
            (data->fractal.offset_x - mouse_real) / zoom_factor;

        // Y方向のオフセット調整
        data->fractal.offset_y = mouse_imag +
            (data->fractal.offset_y - mouse_imag) / zoom_factor;

        // ===== ステップ4: ズーム倍率を更新 =====
        data->fractal.zoom *= zoom_factor;

        // ===== ステップ5: 画面を再描画 =====
        render_fractal(data);

        return (1);  // イベント処理完了
    }
    return (0);  // 他のボタンは無視
}
```

#### 動作の流れ（具体的なシナリオ）
```
【シナリオ】
Mandelbrot集合を表示中、興味深い部分にマウスを置いてズームイン

1. ユーザーがマウスを (600, 200) に置く
   → 複素平面座標 (1.0, -1.0) に相当

2. ユーザーがホイールを上に回す
   → mouse_hook(4, 600, 200, data) が呼ばれる

3. 関数内での処理:
   a. mouse_real = 1.0, mouse_imag = -1.0 を計算
   b. zoom_factor = 1.1 を設定
   c. offset を調整:
      offset_x = 1.0 + (0.0 - 1.0) / 1.1 = 0.091
      offset_y = -1.0 + (0.0 - (-1.0)) / 1.1 = -0.091
   d. zoom を更新: 1.0 * 1.1 = 1.1
   e. render_fractal() で再描画

4. 結果:
   - マウス位置 (1.0, -1.0) が画面上で動かない
   - その周辺が拡大される
   - ユーザーは直感的に操作できる
```

#### なぜこの式が機能するのか？（数学的説明）
```
座標変換の式:
complex_x = (screen_x - center) / zoom + offset

ズーム前:
mouse_real = (mouse_screen - center) / old_zoom + old_offset

ズーム後も同じ位置:
mouse_real = (mouse_screen - center) / new_zoom + new_offset

new_zoom = old_zoom * zoom_factor なので:
mouse_real = (mouse_screen - center) / (old_zoom * zoom_factor) + new_offset

両辺から mouse_real を引いて整理:
new_offset = mouse_real + (old_offset - mouse_real) / zoom_factor
```

#### レビューで説明する時のポイント
```
「マウス中心ズームは、ユーザー体験を向上させる重要な機能です。

実装の核心は、ズーム倍率の変更と同時にオフセットを調整することです。
公式 new_offset = mouse_pos + (old_offset - mouse_pos) / zoom_factor を使い、
マウス位置が画面上で動かないように計算しています。

この公式は、マウス位置を起点として、中心座標までのベクトルを
ズーム倍率に応じてスケールすることで導出できます。

実装では、まずマウスのスクリーン座標を複素平面座標に変換し、
その座標を中心としてズームとオフセットを同時に更新し、
最後に再描画することで、スムーズなズーム体験を実現しています。」
```

#### よくある間違いと対策
```
❌ 間違い1: オフセットを調整しない
   data->fractal.zoom *= 1.1;
   → マウス位置がずれる、使いにくい

❌ 間違い2: マウス位置の変換を忘れる
   new_offset = (old_offset) / zoom_factor;
   → 画面中央を中心にズーム、マウス位置無視

❌ 間違い3: ズーム前の座標で計算
   mouse_pos = screen_to_complex_x(x, data);  // ズーム更新前
   data->fractal.zoom *= zoom_factor;         // ここで更新
   new_offset = ...;  // 既にzoomが変わっている！
   → 必ずズーム更新前に複素平面座標を取得

✅ 正しい順序:
   1. マウス位置を複素平面座標に変換（ズーム更新前）
   2. ズーム倍率を決定
   3. オフセットを調整
   4. ズームを更新
   5. 再描画
```

### Q3: 「色の計算はどうやっていますか？」（視覚的な美しさの核心）

#### なぜ色が重要なのか？
```
フラクタルの本質 = 発散速度の違い
色 = 発散速度の可視化

イテレーション数だけでは:
- 集合内部（iter = max_iter）= 黒
- 集合外部（iter < max_iter）= 白
→ 単なる白黒の境界線、つまらない

色を使うと:
- iter = 1 → 明るい色（すぐ発散）
- iter = 50 → 中間色
- iter = 100 → 暗い色（なかなか発散しない）
- iter = max_iter → 黒（発散しない）
→ グラデーションで詳細な構造が見える
```

#### 色計算の全体フロー
```
1. フラクタル計算
   mandelbrot_calc() → iter = 42 を返す

2. 正規化（0～1の範囲に）
   t = 42 / 100 = 0.42

3. カラースキーム選択
   psychedelic / sunset / ocean

4. RGB値の計算
   三角関数を使って滑らかなグラデーション

5. 色コードの生成
   RGB(r, g, b) → 0xRRGGBB（16進数）

6. ピクセルに設定
   my_mlx_pixel_put(x, y, color)
```

#### 基本的な色計算（コード実装）
```c
// colors.c の get_color_smooth
int get_color_smooth(double smooth_iter, int max_iter, int color_scheme)
{
    // ===== ステップ1: 集合内部のチェック =====
    // iter = max_iter = 集合内部 = 黒
    if (smooth_iter >= max_iter)
        return (0x000000);  // RGB(0, 0, 0) = 黒

    // ===== ステップ2: 正規化（0～1の範囲に）=====
    // smooth_iter = 42, max_iter = 100
    // → t = 0.42（42%の位置）
    double t = smooth_iter / (double)max_iter;

    // ===== ステップ3: カラースキームに応じて色を計算 =====
    if (color_scheme == 0)
        return (get_psychedelic_color(t));    // サイケデリック
    else if (color_scheme == 1)
        return (get_sunset_color(t));         // サンセット
    else if (color_scheme == 2)
        return (get_ocean_color(t));          // オーシャン
    else
        return (get_grayscale_color(t));      // グレースケール
}
```

#### 各カラースキームの実装（完全解説）

**1. サイケデリック（虹色グラデーション）**
```c
int get_psychedelic_color(double t)
{
    // 三角関数を使って滑らかに変化する色
    // t = 0.0～1.0 を何周期か繰り返す

    // 赤成分: sin波で 0→255→0 を繰り返す
    // t * 6.0: 0～1を0～6に拡大（6回周期）
    // sin(...): -1～1の範囲で振動
    // * 127.5 + 127.5: -1～1を0～255に変換
    int r = (int)(sin(t * 6.0) * 127.5 + 127.5);

    // 緑成分: 位相をずらして異なる色に
    // + 2.0: 赤から2π/3ずらす（120度）
    int g = (int)(sin(t * 6.0 + 2.0) * 127.5 + 127.5);

    // 青成分: さらに位相をずらす
    // + 4.0: 赤から4π/3ずらす（240度）
    int b = (int)(sin(t * 6.0 + 4.0) * 127.5 + 127.5);

    // RGB値を16進数の色コードに統合
    // (r << 16): 赤を上位16bitに
    // (g << 8):  緑を中位8bitに
    // b:         青を下位8bitに
    return ((r << 16) | (g << 8) | b);
}

// 具体例:
// t = 0.0 → RGB(127, 127, 127) = グレー
// t = 0.166 → RGB(255, 0, 127) = 赤紫
// t = 0.333 → RGB(127, 255, 0) = 黄緑
// t = 0.5 → RGB(0, 127, 255) = 水色
// t = 1.0 → RGB(127, 127, 127) = グレー（一周）
```

**2. サンセット（夕焼け風）**
```c
int get_sunset_color(double t)
{
    // 紫 → 赤 → オレンジ → 黄色 のグラデーション

    int r, g, b;

    if (t < 0.33) {
        // 初期（紫～赤）
        double local_t = t / 0.33;  // 0～0.33を0～1に正規化
        r = (int)(128 + local_t * 127);  // 128→255
        g = (int)(0 + local_t * 0);      // 0のまま
        b = (int)(128 - local_t * 128);  // 128→0
    } else if (t < 0.66) {
        // 中間（赤～オレンジ）
        double local_t = (t - 0.33) / 0.33;
        r = 255;                         // 赤はmax
        g = (int)(0 + local_t * 165);    // 0→165
        b = 0;
    } else {
        // 後半（オレンジ～黄色）
        double local_t = (t - 0.66) / 0.34;
        r = 255;                         // 赤はmax
        g = (int)(165 + local_t * 90);   // 165→255
        b = (int)(0 + local_t * 100);    // 0→100
    }

    return ((r << 16) | (g << 8) | b);
}
```

**3. オーシャン（海の深さ風）**
```c
int get_ocean_color(double t)
{
    // 深い青 → 水色 → 白（波） のグラデーション

    // 青成分: 常に高い（海っぽさ）
    int b = (int)(100 + t * 155);  // 100→255

    // 緑成分: 徐々に増加（浅瀬の表現）
    int g = (int)(50 + t * 150);   // 50→200

    // 赤成分: 少しだけ増加（明るさ）
    int r = (int)(0 + t * 100);    // 0→100

    return ((r << 16) | (g << 8) | b);
}

// 具体例:
// t = 0.0 → RGB(0, 50, 100) = 深い青
// t = 0.5 → RGB(50, 125, 177) = 中間の青
// t = 1.0 → RGB(100, 200, 255) = 明るい水色
```

**4. グレースケール（シンプル）**
```c
int get_grayscale_color(double t)
{
    // 黒 → グレー → 白
    int intensity = (int)(t * 255);
    return ((intensity << 16) | (intensity << 8) | intensity);
}
```

#### RGB色コードの仕組み（基礎知識）
```
16進数表記: 0xRRGGBB
- RR: 赤成分（00～FF = 0～255）
- GG: 緑成分（00～FF = 0～255）
- BB: 青成分（00～FF = 0～255）

例:
0x000000 = RGB(0, 0, 0) = 黒
0xFFFFFF = RGB(255, 255, 255) = 白
0xFF0000 = RGB(255, 0, 0) = 赤
0x00FF00 = RGB(0, 255, 0) = 緑
0x0000FF = RGB(0, 0, 255) = 青
0xFF00FF = RGB(255, 0, 255) = マゼンタ
0x00FFFF = RGB(0, 255, 255) = シアン
0xFFFF00 = RGB(255, 255, 0) = 黄色

ビットシフトでの合成:
r = 200, g = 100, b = 50
r << 16 = 0xC80000 (200を上位に)
g << 8  = 0x006400 (100を中位に)
b       = 0x000032 (50を下位に)
OR演算 = 0xC86432
```

#### スムーズカラーリング（ボーナス）
```c
// 通常のイテレーション数だけでは、色が階段状に変化
// → バンディング（帯状の境界）が見える

// スムーズカラーリング: 発散時の正確な値を使う
double mandelbrot_calc_smooth(double c_real, double c_imag, int max_iter)
{
    double z_real = 0.0;
    double z_imag = 0.0;
    int iter = 0;

    while (iter < max_iter) {
        double z_real_sq = z_real * z_real;
        double z_imag_sq = z_imag * z_imag;

        if (z_real_sq + z_imag_sq > 4.0) {
            // 通常: return iter; だけ
            // スムーズ: 発散時の正確な値も考慮

            // log(|z|) を使った補正
            double magnitude_sq = z_real_sq + z_imag_sq;
            double smooth = iter + 1 - log(log(magnitude_sq)) / log(2.0);
            return smooth;
        }

        double temp = z_real_sq - z_imag_sq + c_real;
        z_imag = 2.0 * z_real * z_imag + c_imag;
        z_real = temp;
        iter++;
    }

    return (double)iter;
}

// 結果:
// 通常: iter = 10, 11, 12, ... （整数）
// スムーズ: iter = 10.234, 11.789, 12.456, ... （実数）
// → 色が滑らかに変化、バンディングなし
```

#### レビューで説明する時のテンプレート
```
「色計算は、フラクタルの発散速度を視覚的に表現する重要な要素です。

まず、フラクタル計算で得られたイテレーション数を0～1の範囲に正規化します。
この値を使って、選択されたカラースキームに応じたRGB値を計算します。

実装では、三角関数（sin, cos）を使うことで滑らかなグラデーションを実現し、
位相をずらすことで赤・緑・青の各成分が異なるタイミングで変化するようにしています。

例えばサイケデリックスキームでは、sin(t * 6.0)で6周期の波を作り、
それぞれ位相を120度ずつずらすことで、虹色のグラデーションを実現しています。

最終的に、RGBの各成分をビットシフトで統合し、0xRRGGBBの形式で色コードを生成します。」
```

### Q4: 「MandelbrotとJuliaの違いは？」

**回答例:**
```
数学的には同じ漸化式 z = z² + c を使いますが、初期条件が異なります:

Mandelbrot集合:
- c = 各ピクセルの座標
- z の初期値 = 0
- 「このピクセル座標をパラメータとして使ったとき発散するか？」

Julia集合:
- c = 固定パラメータ（コマンドライン引数）
- z の初期値 = 各ピクセルの座標
- 「この初期値から始めて、固定パラメータで計算したとき発散するか？」

Mandelbrotは「パラメータ空間」、Juliaは「位相空間」を可視化しています。
```

### Q5: 「ピクセルの描画はどうやってますか？」

**回答例:**
```c
void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    // 境界チェック
    if (x < 0 || x >= data->width || y < 0 || y >= data->height)
        return;

    // ピクセルのアドレスを計算
    dst = data->img.addr + (y * data->img.line_length + x * (data->img.bits_per_pixel / 8));

    // 色データを書き込み
    *(unsigned int*)dst = color;
}
```

**説明のポイント:**
「MLXの画像バッファに直接色データを書き込んでいます。line_lengthを使って正確なメモリ位置を計算し、境界チェックでセグフォを防いでいます。」

### Q6: 「メモリ管理はどうしていますか？」（Valgrindで通るために）

#### メモリ管理が重要な理由
```
42schoolの評価基準:
- メモリリーク = 即不合格
- セグメンテーションフォルト = 即不合格
- Valgrindで全てのメモリが解放されていることを確認

MLXライブラリの特性:
- mlx_init(), mlx_new_window(), mlx_new_image() で確保
- 対応する mlx_destroy_*() で解放
- 順序を間違えるとクラッシュする可能性
```

#### MLXリソースの確保と解放の流れ
```
【確保の順序】
1. mlx_ptr = mlx_init()
2. win_ptr = mlx_new_window(mlx_ptr, ...)
3. img_ptr = mlx_new_image(mlx_ptr, ...)
4. addr = mlx_get_data_addr(img_ptr, ...)

【解放の順序（逆順！）】
1. mlx_destroy_image(mlx_ptr, img_ptr)
2. mlx_destroy_window(mlx_ptr, win_ptr)
3. mlx_destroy_display(mlx_ptr)  ← Linux版MLXのみ
4. free(mlx_ptr)
```

#### 完全なクリーンアップ関数（実装例）
```c
// プログラム終了時のクリーンアップ
// ESCキー、×ボタン、エラー時に呼ばれる
int cleanup(t_data *data)
{
    // ===== ステップ1: 画像リソースを解放 =====
    // mlx_new_image() で確保した画像を削除
    if (data && data->img.img_ptr)
    {
        mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
        data->img.img_ptr = NULL;  // ダブルフリー防止
    }

    // ===== ステップ2: ウィンドウを解放 =====
    // mlx_new_window() で確保したウィンドウを削除
    if (data && data->win_ptr)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        data->win_ptr = NULL;  // ダブルフリー防止
    }

    // ===== ステップ3: MLX接続を解放（Linux版のみ）=====
    // mlx_init() で確保した接続を削除
    if (data && data->mlx_ptr)
    {
        // Linux版MLXの場合のみ必要（macOS版では不要）
        #ifdef __linux__
            mlx_destroy_display(data->mlx_ptr);
        #endif

        // mlx_ptrの実体を解放
        free(data->mlx_ptr);
        data->mlx_ptr = NULL;  // ダブルフリー防止
    }

    // ===== ステップ4: プログラム終了 =====
    exit(0);

    // exit()なので実際には到達しないが、
    // 関数のシグネチャに合わせて return を書く場合もある
    return (0);
}
```

#### エラー時のクリーンアップ（初期化中の失敗）
```c
// 初期化中にエラーが発生した場合の処理
// 例: mlx_init()は成功したが、mlx_new_window()が失敗
int error_exit(t_data *data, char *message)
{
    // エラーメッセージを出力
    ft_putstr_fd("Error: ", 2);
    ft_putstr_fd(message, 2);
    ft_putstr_fd("\n", 2);

    // 部分的にクリーンアップ
    // NULLチェックで安全に処理
    if (data)
    {
        if (data->img.img_ptr)
            mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
        if (data->win_ptr)
            mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        if (data->mlx_ptr)
        {
            #ifdef __linux__
                mlx_destroy_display(data->mlx_ptr);
            #endif
            free(data->mlx_ptr);
        }
    }

    exit(1);  // エラー終了
}
```

#### 初期化関数での安全な実装
```c
int init_mlx(t_data *data)
{
    // ===== ステップ1: データ構造をゼロ初期化 =====
    // NULLチェックが機能するように初期化
    ft_memset(data, 0, sizeof(t_data));

    // ===== ステップ2: MLX接続を確立 =====
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        return (error_exit(data, "Failed to initialize MLX"));

    // ===== ステップ3: ウィンドウを作成 =====
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "Fractol");
    if (!data->win_ptr)
        return (error_exit(data, "Failed to create window"));

    // ===== ステップ4: 画像バッファを作成 =====
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
    if (!data->img.img_ptr)
        return (error_exit(data, "Failed to create image"));

    // ===== ステップ5: 画像データのアドレスを取得 =====
    data->img.addr = mlx_get_data_addr(data->img.img_ptr,
        &data->img.bits_per_pixel,
        &data->img.line_length,
        &data->img.endian);
    if (!data->img.addr)
        return (error_exit(data, "Failed to get image address"));

    return (0);  // 成功
}
```

#### メモリリークチェック（Valgrind）
```bash
# 基本的なメモリリークチェック
valgrind --leak-check=full ./fractol mandelbrot

# 詳細なメモリ分析（全てのリークを表示）
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fractol mandelbrot

# 期待される結果:
# ==12345== HEAP SUMMARY:
# ==12345==     in use at exit: 0 bytes in 0 blocks
# ==12345==   total heap usage: 123 allocs, 123 frees, 45,678 bytes allocated
# ==12345==
# ==12345== All heap blocks were freed -- no leaks are possible

# もしリークがある場合:
# ==12345== 1,024 bytes in 1 blocks are definitely lost in loss record 1 of 1
# ==12345==    at 0x4C2AB80: malloc (in /usr/lib/valgrind/...)
# ==12345==    by 0x400ABC: mlx_new_image (mlx_new_image.c:42)
# ==12345==    by 0x400DEF: init_mlx (init.c:56)
# ==12345==    by 0x401234: main (main.c:89)
# → mlx_new_image()で確保した画像が解放されていない
```

#### よくあるメモリ関連のバグと対策
```
❌ バグ1: ダブルフリー
   mlx_destroy_image(mlx_ptr, img_ptr);
   mlx_destroy_image(mlx_ptr, img_ptr);  // 2回目！
   → クラッシュ

✅ 対策: 解放後にNULLを設定
   mlx_destroy_image(mlx_ptr, img_ptr);
   img_ptr = NULL;
   if (img_ptr)  // 2回目は実行されない
       mlx_destroy_image(mlx_ptr, img_ptr);

❌ バグ2: 未初期化ポインタ
   t_data data;  // ゴミ値が入っている
   if (data.img_ptr)  // 判定不能
       mlx_destroy_image(...);
   → 不正なアドレスにアクセス

✅ 対策: ゼロ初期化
   t_data data;
   ft_memset(&data, 0, sizeof(t_data));
   // または
   t_data data = {0};

❌ バグ3: 逆順で解放
   mlx_destroy_window(mlx_ptr, win_ptr);  // 先にウィンドウ
   mlx_destroy_image(mlx_ptr, img_ptr);   // 後で画像
   → 画像がウィンドウに依存している場合にクラッシュ

✅ 対策: 作成と逆の順序で解放
   mlx_destroy_image(mlx_ptr, img_ptr);   // 先に画像
   mlx_destroy_window(mlx_ptr, win_ptr);  // 後でウィンドウ

❌ バグ4: mlx_destroy_displayを忘れる
   free(mlx_ptr);  // display が残る
   → Valgrindでリーク検出

✅ 対策: Linux版では必ず呼ぶ
   #ifdef __linux__
       mlx_destroy_display(mlx_ptr);
   #endif
   free(mlx_ptr);
```

#### イベントフックでのクリーンアップ
```c
// ESCキーでの終了
int key_hook(int keycode, t_data *data)
{
    if (keycode == 65307)  // ESC
    {
        cleanup(data);  // クリーンアップして終了
        return (0);
    }
    // 他のキー処理...
    return (0);
}

// ×ボタンでの終了
int close_hook(t_data *data)
{
    cleanup(data);  // クリーンアップして終了
    return (0);
}

// イベントフックの登録（main.cで）
int main(int argc, char **argv)
{
    t_data data;

    // 初期化...
    init_mlx(&data);

    // イベントフックを登録
    mlx_key_hook(data.win_ptr, key_hook, &data);
    mlx_hook(data.win_ptr, 17, 0, close_hook, &data);  // ×ボタン

    // イベントループ
    mlx_loop(data.mlx_ptr);

    // mlx_loop()は無限ループなので、
    // ここには到達しない（cleanup()でexit()するため）
    return (0);
}
```

#### レビューで説明する時のポイント
```
「メモリ管理は42schoolプロジェクトで最も重要な部分の一つです。

MLXライブラリで確保したリソースは、確保と逆の順序で解放します。
画像 → ウィンドウ → ディスプレイ → mlx_ptr の順です。

各ポインタはゼロ初期化し、解放前にNULLチェックを行うことで、
ダブルフリーや不正なアドレスアクセスを防いでいます。

Linux版MLXでは、mlx_destroy_display()を呼ばないとメモリリークが発生するため、
プリプロセッサディレクティブで条件付きコンパイルしています。

ESCキーや×ボタンでの終了時には、cleanup()関数を呼び出して
全てのリソースを確実に解放してからexit(0)でプログラムを終了します。

Valgrindで検証し、"All heap blocks were freed"の確認を取っています。」
```

---

## 5. デモンストレーション手順

### 5.1 基本機能のデモ

```bash
# 1. 引数エラー処理を見せる
./fractol
./fractol invalid

# 2. Mandelbrot集合を表示
./fractol mandelbrot
# → ESCで終了、ズーム、移動を実演

# 3. 異なるJulia集合を表示
./fractol julia -0.7 0.27015  # ドラゴン型
./fractol julia -0.4 0.6      # スパイラル型
./fractol julia 0.285 0.01    # フラクタル樹
```

### 5.2 操作の実演
1. **ズーム機能**: 興味深い部分をマウスホイールでズームイン
2. **移動機能**: 矢印キーで画面を移動
3. **色変更**: Cキーでカラースキーム変更
4. **イテレーション調整**: +/-キーで詳細度を変更
5. **リセット**: Rキーで初期状態に戻る

### 5.3 数学的正確性の説明
- **Mandelbrot**: 「この形がカーディオイド（心臓型）で、ここが主要なバルブです」
- **Julia**: 「パラメータを変えると形が変わります。これは接続性の違いです」

---

## 6. トラブルシューティング

### 6.1 よくある問題と解決法

| 問題 | 原因 | 解決法 |
|------|------|--------|
| コンパイルエラー | MLXライブラリ不足 | `make` でMLXも一緒にビルド |
| 画面が真っ黒 | 初期化失敗 | `DISPLAY` 環境変数を確認 |
| ズームが効かない | イベントフック未設定 | `mlx_mouse_hook` の呼び出しを確認 |
| セグフォ | NULLポインタアクセス | 初期化の戻り値チェック |
| 色が出ない | カラー計算のバグ | イテレーション数と色の対応確認 |

### 6.2 デバッグ用プリント文
```c
// 座標変換の確認
printf("Screen(%d,%d) -> Complex(%.6f,%.6f)\n",
       x, y, complex_x, complex_y);

// イテレーション数の確認
printf("Pixel(%d,%d): iter=%d, color=0x%06X\n",
       x, y, iter, color);

// ズーム状態の確認
printf("Zoom: %.6f, Offset: (%.6f, %.6f)\n",
       data->fractal.zoom, data->fractal.offset_x, data->fractal.offset_y);
```

---

## 7. レビュー対策：暗記必須事項

### 7.1 数学的知識
- **複素数**: z = a + bi（a:実部、b:虚部）
- **Mandelbrot**: z₀=0, z_{n+1} = z_n² + c, c=ピクセル座標
- **Julia**: z₀=ピクセル座標, z_{n+1} = z_n² + c, c=固定パラメータ
- **発散条件**: |z| > 2（実装では4.0で比較）

### 7.2 技術的知識
- **MLX**: MinilibX、42schoolのグラフィックライブラリ
- **画像バッファ**: メモリ上のピクセルデータ配列
- **イベントループ**: `mlx_loop`でイベント待機
- **座標変換**: screen→normalized→complex plane

### 7.3 自分の実装の特徴
- **スムーズカラーリング**: 連続的な色変化
- **3つのカラースキーム**: psychedelic, sunset, ocean
- **マウス中心ズーム**: クリック位置を中心にズーム
- **リアルタイム操作**: キー入力で即座に再描画

### 7.4 改善点・今後の拡張
- **マルチスレッド**: 描画の並列化
- **追加フラクタル**: Burning Ship, Newton法
- **GPU活用**: シェーダーでの高速化
- **パラメータ保存**: 設定の永続化

---

## 📋 レビュー直前チェックリスト

**□ プロジェクトがコンパイルできる**
**□ 引数処理が正しく動作する**
**□ 両方のフラクタルが表示される**
**□ 全ての操作（ズーム、移動、色変更等）が動作する**
**□ ESCと×ボタンで正常終了する**
**□ 数学的な説明ができる（Mandelbrot vs Julia）**
**□ 主要関数の動作を説明できる**
**□ 座標変換の仕組みを理解している**
**□ 色計算のロジックを理解している**
**□ メモリ管理が適切にできている**

---

## 8. レビュー前日にやること（最終チェック）

### 8.1 コードの最終確認（30分）
```bash
# 1. クリーンビルド
make fclean && make
# エラーがないか確認

# 2. Norminette チェック
norminette srcs/ includes/
# 全ファイルでエラーなしを確認

# 3. 両方のフラクタルを起動確認
./fractol mandelbrot
./fractol julia -0.7 0.27015

# 4. 全ての操作を確認
# - マウスホイールでズーム
# - 矢印キーで移動
# - Cキーで色変更
# - +/-キーでイテレーション調整
# - Rキーでリセット
# - ESCで終了

# 5. Valgrindチェック
valgrind --leak-check=full ./fractol mandelbrot
# "All heap blocks were freed" を確認
```

### 8.2 説明の練習（30分）

#### 30秒バージョン（エレベータピッチ）
```
「このプロジェクトは、複素数の反復計算を使って
Mandelbrot集合とJulia集合を描画するプログラムです。
マウス中心ズームと複数のカラースキームを実装し、
ユーザーがフラクタルの無限の複雑さを探索できます。」
```

#### 2分バージョン（詳細説明）
```
「fract-olは、複素平面上の点に対して漸化式 z = z² + c を繰り返し計算し、
発散速度を色で表現することでフラクタル図形を可視化するプログラムです。

Mandelbrot集合では、各ピクセルの座標をcとして使い、z₀=0から計算を開始します。
Julia集合では、cを固定パラメータとし、各ピクセルの座標をz₀として計算します。

技術的には、スクリーン座標から複素平面座標への変換、
マウス位置を中心としたズーム機能、
三角関数を使った滑らかなカラーグラデーション、
そしてMLXライブラリを使ったリアルタイム描画を実装しています。

メモリ管理では、MLXリソースを確保と逆順で解放し、
Valgrindで全てのメモリリークが解消されていることを確認しています。」
```

### 8.3 想定質問と回答（暗記）

**Q1: なぜtempを使うのか？**
```
A: z_imagの計算で古いz_realが必要だからです。
   同時に更新すると、新しいz_realを使ってしまい計算が狂います。
```

**Q2: なぜ4.0と比較？**
```
A: 数学的定理で |z| > 2 なら発散が証明されています。
   両辺を2乗すると |z|² > 4 となり、√計算を避けて高速化できます。
```

**Q3: ズームの公式の意味は？**
```
A: new_offset = mouse_pos + (old_offset - mouse_pos) / zoom_factor
   マウス位置を起点に、中心までのベクトルをズーム倍率でスケールします。
   これによりマウス位置が画面上で動かなくなります。
```

**Q4: 色が階段状にならない理由は？**
```
A: スムーズカラーリングを実装しています。
   発散時の正確な値を log関数で補正し、実数のイテレーション値を得ています。
   これにより色が連続的に変化します。
```

**Q5: メモリリークはない？**
```
A: ありません。MLXリソースは確保と逆順で解放しています。
   画像→ウィンドウ→ディスプレイ→mlx_ptrの順です。
   Valgrindで "All heap blocks were freed" を確認済みです。
```

### 8.4 デモのシナリオ（5分）

```
【開始】
「それではプログラムをデモンストレーションします。」

【シーン1: 引数エラー】
./fractol
→ 「引数なしで実行すると、使用方法を表示して終了します。」

【シーン2: Mandelbrot】
./fractol mandelbrot
→ 「これがMandelbrot集合です。中央の黒い部分が集合内部、
   周辺の色付き部分が発散速度を表しています。」

【操作実演】
- マウスホイール: 「境界部分をズームインします。
  マウス位置を中心にズームされることが分かります。」
- 矢印キー: 「矢印キーで画面を移動できます。」
- Cキー: 「カラースキームを変更できます。」
- +/-キー: 「イテレーション数を調整できます。増やすと詳細になります。」
- Rキー: 「初期状態にリセットできます。」

【シーン3: Julia】
./fractol julia -0.7 0.27015
→ 「こちらがJulia集合です。パラメータを変えると全く異なる形になります。」

./fractol julia -0.4 0.6
→ 「別のパラメータでは、このような渦巻き状の形になります。」

【終了】
- ESC: 「ESCキーで正常終了します。」
→ 「以上がデモンストレーションです。」
```

### 8.5 緊張したら思い出すこと

```
1. 落ち着いて深呼吸
2. 分からない質問は「少し考える時間をください」と言う
3. コードを見ながら説明してOK
4. 完璧でなくても、理解していることを示せれば合格
5. レビュアーも人間、会話を楽しむ気持ちで

最も重要なこと:
「このプロジェクトに時間をかけて取り組み、
理解を深めてきたこと」
それが伝われば、必ず良い評価が得られます。
```

### 8.6 よくある失敗と対策

| 失敗 | 原因 | 対策 |
|------|------|------|
| デモ中にクラッシュ | 未テストの操作 | 全機能を事前確認 |
| 質問に答えられない | 理解不足 | このガイドを繰り返し読む |
| メモリリーク指摘 | Valgrind未確認 | 必ずValgrindを実行 |
| 数式の説明が曖昧 | 暗記不足 | 公式を声に出して覚える |
| Norminette エラー | 直前修正 | 前日までに全て修正 |

---

## 📚 まとめ: レビューで伝えるべき3つのポイント

### 1. 数学的理解
```
「複素数の反復計算による発散速度の可視化」
z_{n+1} = z_n² + c の意味を理解している
MandelbrotとJuliaの違いを明確に説明できる
```

### 2. 技術的実装
```
「座標変換、ズーム、色計算の各アルゴリズム」
なぜそのコードを書いたのか理由を説明できる
最適化や工夫した点を具体的に述べられる
```

### 3. プロフェッショナリズム
```
「メモリ管理、エラー処理、コーディング規約の遵守」
Valgrindでリークなし、Norminetteでエラーなし
ユーザー体験を考えた設計（マウス中心ズームなど）
```

---

## 🎯 最後のメッセージ

**このガイドを完璧に理解すれば、レビューで満点を取ることができるはずです！**

**重要なのは:**
- コードの「何を」よりも「なぜ」を理解すること
- 数学的理論と実装の両方を押さえること
- 自信を持って、でも謙虚に説明すること

**あなたはこのプロジェクトに多くの時間と努力を注ぎました。**
**その成果を堂々と示してください。頑張ってください！**

---

**レビュー当日の朝にもう一度この「セクション0」と「セクション8」を読むこと！**