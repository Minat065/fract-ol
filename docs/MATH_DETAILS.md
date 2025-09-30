# フラクタル数学詳細解説

> **このドキュメントの目的**: fract-olで使われている数学的概念を詳しく理解する

---

## 📚 目次

1. [複素数の基礎](#複素数の基礎)
2. [Mandelbrot集合](#mandelbrot集合)
3. [Julia集合](#julia集合)
4. [Tricorn（Mandelbar）](#tricornmandelbar)
5. [エスケープタイム法](#エスケープタイム法)
6. [スムースカラーリング](#スムースカラーリング)
7. [座標変換とズーム](#座標変換とズーム)

---

## 複素数の基礎

### 定義

複素数は実部と虚部からなる数：

```
c = a + bi
```

- `a`: 実部（Real part）
- `b`: 虚部（Imaginary part）
- `i`: 虚数単位（i² = -1）

### 複素平面

複素数は2次元平面上の点として表現できる：

```
      虚部軸（Imaginary）
           ↑
           |  • c = 2 + 3i
           |
    -------+------→ 実部軸（Real）
           |
           |
```

### プログラムでの表現

```c
// 配列で表現
double z[2];
z[0] = 実部;  // Real part
z[1] = 虚部;  // Imaginary part

// 例: c = 2 + 3i
double c[2];
c[0] = 2.0;  // 実部
c[1] = 3.0;  // 虚部
```

### 複素数の計算

#### 1. 加算
```
(a + bi) + (c + di) = (a+c) + (b+d)i

コード:
result[0] = a[0] + b[0];  // 実部
result[1] = a[1] + b[1];  // 虚部
```

#### 2. 乗算
```
(a + bi) × (c + di) = (ac - bd) + (ad + bc)i

コード:
result[0] = a[0]*b[0] - a[1]*b[1];  // 実部
result[1] = a[0]*b[1] + a[1]*b[0];  // 虚部
```

#### 3. 二乗（特に重要）
```
(a + bi)² = (a² - b²) + (2ab)i

コード:
double a_sq = a[0] * a[0];
double b_sq = a[1] * a[1];
result[0] = a_sq - b_sq;      // 実部
result[1] = 2.0 * a[0] * a[1]; // 虚部
```

#### 4. 絶対値（大きさ）
```
|a + bi| = √(a² + b²)

コード:
double magnitude = sqrt(z[0]*z[0] + z[1]*z[1]);

// 最適化版（平方根を省略）
double magnitude_squared = z[0]*z[0] + z[1]*z[1];
```

#### 5. 共役複素数（Tricornで使用）
```
conj(a + bi) = a - bi （虚部の符号を反転）

コード:
conj[0] = z[0];   // 実部はそのまま
conj[1] = -z[1];  // 虚部を反転
```

---

## Mandelbrot集合

### 定義

Mandelbrot集合は、以下の反復式で定義される：

```
z₀ = 0
zₙ₊₁ = zₙ² + c
```

- `c`: 複素平面上の各点
- 反復しても `|z|` が無限大に発散しない点の集合

### 視覚的理解

```
複素平面上の各点cについて：

1. z = 0 から開始
2. z = z² + c を繰り返す
3. |z| が大きくなり続ける → 集合の「外側」（色をつける）
4. |z| が一定範囲内に留まる → 集合の「内側」（黒）
```

### 実装（fractals.c:25-47）

```c
double mandelbrot_calc_smooth(double real, double imag, int max_iter)
{
    double z[2];      // z = z[0] + z[1]i
    double z_sq[2];   // z²の実部・虚部
    double temp;
    int iter;

    // 初期値 z₀ = 0
    z[0] = 0.0;
    z[1] = 0.0;

    iter = 0;
    while (iter < max_iter)
    {
        // z²を計算して保存（再利用のため）
        z_sq[0] = z[0] * z[0];
        z_sq[1] = z[1] * z[1];

        // エスケープ判定: |z|² > 256（つまり|z| > 16）
        if (z_sq[0] + z_sq[1] > 256.0)
            return calc_smooth_value(z_sq[0] + z_sq[1], iter);

        // z² + c の計算
        // (a+bi)² = (a²-b²) + (2ab)i
        temp = z_sq[0] - z_sq[1] + real;  // 実部
        z[1] = 2.0 * z[0] * z[1] + imag;  // 虚部
        z[0] = temp;

        iter++;
    }

    // max_iterに到達 = 集合の内部
    return iter;
}
```

### なぜ|z| > 16で判定？

数学的には|z| > 2で発散することが証明されているが、プログラムでは：

1. `|z| > 2` → `|z|² > 4`
2. より安全な判定のため `|z|² > 256`（= `|z| > 16`）を使用
3. スムースカラーリングの精度向上

---

## Julia集合

### 定義

Julia集合は、Mandelbrotと同じ式だが、初期値とパラメータが逆：

```
z₀ = c （複素平面上の各点）
zₙ₊₁ = zₙ² + c_fixed （固定パラメータ）
```

### Mandelbrotとの違い

| 項目 | Mandelbrot | Julia |
|------|-----------|-------|
| 初期値 z₀ | 0 | c（座標） |
| パラメータ c | 座標 | 固定値 |
| 形状 | 1つの形 | パラメータで無限の形 |

### 美しいパラメータ例

```bash
# 定番の美しいJulia集合
./fractol julia -0.7 0.27015      # ドラゴン型
./fractol julia -0.8 0.156        # 渦巻き
./fractol julia -0.4 0.6          # 雪の結晶
./fractol julia 0.285 0.01        # 蝶々
./fractol julia -0.70176 -0.3842  # サンゴ
./fractol julia -0.835 -0.2321    # 稲妻
```

### 実装（fractals.c:49-71）

```c
double julia_calc_smooth(double real, double imag, t_data *data)
{
    double z[2];
    double z_sq[2];
    double temp;
    int iter;

    // 初期値 z₀ = c（座標）
    z[0] = real;
    z[1] = imag;

    iter = 0;
    while (iter < data->fractal.max_iter)
    {
        z_sq[0] = z[0] * z[0];
        z_sq[1] = z[1] * z[1];

        if (z_sq[0] + z_sq[1] > 256.0)
            return calc_smooth_value(z_sq[0] + z_sq[1], iter);

        // z² + c_fixed の計算
        temp = z_sq[0] - z_sq[1] + data->fractal.julia_real;
        z[1] = 2.0 * z[0] * z[1] + data->fractal.julia_imag;
        z[0] = temp;

        iter++;
    }

    return iter;
}
```

---

## Tricorn（Mandelbar）

### 定義

Tricornは、複素共役を使ったMandelbrotの変種：

```
z₀ = 0
zₙ₊₁ = conj(zₙ)² + c
```

ここで `conj(a+bi) = a-bi`（共役複素数）

### 特徴

- Mandelbrotより鋭角的で攻撃的な形状
- 上下対称（虚部の符号反転のため）
- 「三角形のコーン」のような見た目（名前の由来）

### 実装（fractals_bonus.c:73-95）

```c
double tricorn_calc_smooth(double real, double imag, int max_iter)
{
    double z[2];
    double z_sq[2];
    double temp;
    int iter;

    z[0] = 0.0;
    z[1] = 0.0;

    iter = 0;
    while (iter < max_iter)
    {
        z_sq[0] = z[0] * z[0];
        z_sq[1] = z[1] * z[1];

        if (z_sq[0] + z_sq[1] > 256.0)
            return calc_smooth_value(z_sq[0] + z_sq[1], iter);

        // conj(z)² + c の計算
        // conj(a+bi) = a-bi なので、虚部を-z[1]として計算
        temp = z_sq[0] - z_sq[1] + real;
        z[1] = -2.0 * z[0] * z[1] + imag;  // ← ここが負の符号！
        z[0] = temp;

        iter++;
    }

    return iter;
}
```

### Mandelbrotとの違い

```c
// Mandelbrot
z[1] = 2.0 * z[0] * z[1] + imag;   // +2.0

// Tricorn
z[1] = -2.0 * z[0] * z[1] + imag;  // -2.0（符号が逆）
```

この符号の違いだけで、全く異なる形状になる！

---

## エスケープタイム法

### 原理

フラクタルを描画するアルゴリズム：

```
各ピクセルについて：
    1. 反復計算を開始
    2. |z| > 16 になるまでカウント
    3. その回数を「エスケープタイム」と呼ぶ
    4. エスケープタイムを色に変換
```

### 色分けの仕組み

```
エスケープタイム（反復回数）
┌────────────────────────────────┐
│ 0-10回: 明るい色（すぐ発散）  │ ← 集合から遠い
│ 10-50回: 中間色               │
│ 50-100回: 暗い色（なかなか発散）│ ← 集合に近い
│ 100回以上: 黒（発散しない）    │ ← 集合の内部
└────────────────────────────────┘
```

### 実装のポイント

```c
// 発散判定
if (z_sq[0] + z_sq[1] > 256.0)
    return calc_smooth_value(z_sq[0] + z_sq[1], iter);

// なぜ256？
// |z|² > 256 は |z| > 16 を意味する
// 平方根計算を省略して高速化
```

---

## スムースカラーリング

### 問題点

整数の反復回数だけだと、色が段階的に変わる（バンディング）：

```
色の変化:
■■■■■ 50回
■■■■■ 49回
■■■■■ 48回
      ↑ 段差が見える
```

### 解決方法

対数を使って、小数点以下の精度を追加：

```
smooth_iter = iter + 1 - log(log(|z|)) / log(2)
```

### 数学的説明

1. `|z|` が大きいほど、次の反復で急激に大きくなる
2. `log(log(|z|))` で、「どれくらい発散に近いか」を測る
3. これを引くことで、滑らかな値を得る

### 実装（fractals.c:15-23）

```c
static double calc_smooth_value(double z_sq_sum, int iter)
{
    double log_zn;
    double smooth;

    // |z| = sqrt(z_sq_sum)
    // log(|z|) = log(sqrt(z_sq_sum))
    log_zn = log(sqrt(z_sq_sum));

    // スムース値の計算
    smooth = iter + 1 - log(log_zn) / log(2.0);

    return smooth;
}
```

### 効果

```
整数版:
50, 49, 48, 47, ...（段差がある）

スムース版:
50.234, 49.876, 48.512, 47.189, ...（滑らか）
```

---

## 座標変換とズーム

### スクリーン座標から複素平面座標へ

#### 基本的な変換

```
スクリーン: (0, 0) ～ (800, 600)
     ↓ 変換
複素平面: 実部 -2 ～ 2, 虚部 -1.5 ～ 1.5
```

#### 実装（utils.c）

```c
double screen_to_complex_x(int x, t_data *data)
{
    // 1. スクリーン座標を0～1に正規化
    double normalized = (double)x / data->width;

    // 2. -0.5～0.5に変換（中心を0に）
    double centered = normalized - 0.5;

    // 3. 適切な範囲にスケーリング（-2～2）
    double scaled = centered * 4.0;

    // 4. ズームとオフセットを適用
    double result = scaled / data->fractal.zoom + data->fractal.offset_x;

    return result;
}
```

#### ステップごとの例

```
入力: x = 400（画面中央）, zoom = 1.0, offset = 0.0

1. normalized = 400/800 = 0.5
2. centered = 0.5 - 0.5 = 0.0
3. scaled = 0.0 * 4.0 = 0.0
4. result = 0.0 / 1.0 + 0.0 = 0.0

→ 画面中央は複素平面の原点(0, 0)
```

### ズームの仕組み

#### 基本ズーム（中心点固定）

```c
// ズームイン
zoom *= 1.1;  // 10%拡大

// ズームアウト
zoom *= 0.9;  // 10%縮小
```

#### マウス位置中心のズーム（ボーナス）

**問題**: 中心点でズームすると、マウス位置がずれる

**解決**: マウス位置を固定点として、その周りでズーム

```c
// マウス位置の複素座標
mouse_real = screen_to_complex_x(mouse_x, data);
mouse_imag = screen_to_complex_y(mouse_y, data);

// ズーム倍率
zoom_factor = 1.1;  // または 0.9

// 新しいオフセット
// 数式: new_offset = mouse_pos + (old_offset - mouse_pos) / zoom_factor
data->fractal.offset_x = mouse_real +
    (data->fractal.offset_x - mouse_real) / zoom_factor;
data->fractal.offset_y = mouse_imag +
    (data->fractal.offset_y - mouse_imag) / zoom_factor;

// ズーム適用
data->fractal.zoom *= zoom_factor;
```

#### 数学的説明

```
マウス位置をM、オフセットをOとする

ズーム前: 画面上の点P = (P - O) / zoom
ズーム後: 画面上の点P' = (P - O') / (zoom * factor)

Mが固定される条件:
M = (M - O) / zoom = (M - O') / (zoom * factor)

これを解くと:
O' = M + (O - M) / factor
```

### 移動の仕組み（ボーナス）

```c
// 矢印キーでの移動
// ズームに応じて移動量を調整
double move_amount = 0.1 / data->fractal.zoom;

// 上
data->fractal.offset_y -= move_amount;

// 下
data->fractal.offset_y += move_amount;

// 左
data->fractal.offset_x -= move_amount;

// 右
data->fractal.offset_x += move_amount;
```

**なぜzoomで割る？**
- ズーム1倍（広範囲）: 0.1単位で大きく移動
- ズーム10倍（拡大）: 0.01単位で細かく移動
- ズーム100倍（大拡大）: 0.001単位でさらに細かく

---

## まとめ

### 重要な数式一覧

```
1. Mandelbrot反復:
   zₙ₊₁ = zₙ² + c, z₀ = 0

2. Julia反復:
   zₙ₊₁ = zₙ² + c_fixed, z₀ = c

3. Tricorn反復:
   zₙ₊₁ = conj(zₙ)² + c, z₀ = 0

4. 複素数の二乗:
   (a+bi)² = (a²-b²) + (2ab)i

5. スムース値:
   smooth = iter + 1 - log(log(|z|)) / log(2)

6. 座標変換:
   complex = (screen/width - 0.5) * range / zoom + offset

7. マウス位置ズーム:
   new_offset = mouse + (old_offset - mouse) / zoom_factor
```

### 実装のコツ

1. **複素数**: 配列`[実部, 虚部]`で表現
2. **最適化**: `|z|²`で判定（平方根を省略）
3. **精度**: スムースカラーリングで美しい色
4. **ユーザビリティ**: ズームに応じた移動量調整

---

**この数学知識があれば、fract-olの実装を完全に理解できます！** 📐✨