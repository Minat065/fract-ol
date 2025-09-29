# fract-ol ユニットテスト手順書

このドキュメントでは、fract-olプロジェクトの機能を体系的にテストする手順を説明します。

## 1. 事前準備

### 1.1 プロジェクトのビルド
```bash
# プロジェクトをクリーンビルド
make fclean
make

# ビルド成功を確認
ls -la fractol
```

### 1.2 テスト環境の確認
```bash
# X11環境が利用可能か確認
echo $DISPLAY

# 必要に応じてX11転送を有効化（WSL等の場合）
export DISPLAY=:0.0
```

## 2. 基礎機能テスト

### 2.1 引数処理テスト

#### 無効な引数の処理
```bash
# 引数なし
./fractol
# 期待結果: 使用方法を表示して終了（戻り値1）

# 無効な引数
./fractol invalid_fractal
# 期待結果: 使用方法を表示して終了（戻り値1）

# Julia集合で引数不足
./fractol julia
# 期待結果: 使用方法を表示して終了（戻り値1）

./fractol julia -0.7
# 期待結果: 使用方法を表示して終了（戻り値1）

# Julia集合で無効な数値
./fractol julia abc def
# 期待結果: エラーメッセージを表示して終了（戻り値1）

./fractol julia 1.2.3 0.5
# 期待結果: エラーメッセージを表示して終了（戻り値1）
```

#### 有効な引数の処理
```bash
# Mandelbrot集合
./fractol mandelbrot
# 期待結果: ウィンドウが開いてMandelbrot集合が表示

# Julia集合（基本パラメータ）
./fractol julia -0.7 0.27015
# 期待結果: ウィンドウが開いてJulia集合が表示

# Julia集合（様々なパラメータ）
./fractol julia -0.4 0.6
./fractol julia 0.285 0.01
./fractol julia -0.8 0.156
./fractol julia -0.123 -0.745
```

### 2.2 描画機能テスト

各テストケースで以下を確認：
- ウィンドウが正常に開く
- フラクタルが描画される
- 色が適切に表示される
- ウィンドウの操作（最小化、復元等）がスムーズ

## 3. インタラクション機能テスト

### 3.1 キーボード操作テスト

任意のフラクタルを表示した状態で以下をテスト：

```bash
# 基本操作テスト用コマンド
./fractol mandelbrot
```

#### 必須キー操作
- **ESC**: ウィンドウが閉じ、プログラムが正常終了
- **ウィンドウ×ボタン**: ウィンドウが閉じ、プログラムが正常終了

#### ボーナス機能（実装されている場合）
- **↑キー**: 画面が上方向に移動
- **↓キー**: 画面が下方向に移動
- **←キー**: 画面が左方向に移動
- **→キー**: 画面が右方向に移動
- **+キー**: イテレーション数が増加（より詳細な描画）
- **-キー**: イテレーション数が減少（より粗い描画）
- **Rキー**: ビューがリセット（初期位置・ズーム）
- **Cキー**: カラースキームが変化

### 3.2 マウス操作テスト

#### 基本ズーム機能
- **マウスホイール上回転**: ズームイン
- **マウスホイール下回転**: ズームアウト

#### 高度なズーム機能（ボーナス）
1. マウスカーソルを画面の特定の点に置く
2. マウスホイールでズームイン
3. **期待結果**: カーソル位置を中心としてズーム
4. 異なる位置で同様にテスト

## 4. 数学的正確性テスト

### 4.1 Mandelbrot集合の検証

```bash
./fractol mandelbrot
```

**確認ポイント:**
- 中心部に黒い領域（集合内部）が存在
- 境界部分に色のグラデーションが存在
- 典型的なMandelbrot集合の形状（カーディオイド、円形のバルブ等）
- ズームイン時に自己相似性が確認できる

### 4.2 Julia集合の検証

```bash
# 有名なパラメータでテスト
./fractol julia -0.7 0.27015    # ドラゴン型
./fractol julia -0.4 0.6        # スパイラル型
./fractol julia 0.285 0.01      # フラクタル樹
./fractol julia -0.123 -0.745   # 複雑な形状
```

**確認ポイント:**
- パラメータに応じて異なる形状が表示される
- 各パラメータで期待される形状パターン
- 接続性（連結/非連結）が適切

## 5. パフォーマンステスト

### 5.1 極端なズームテスト

```bash
./fractol mandelbrot
```

1. 連続して深くズームイン（20-30回程度）
2. **確認事項:**
   - プログラムがクラッシュしない
   - レスポンシブな操作が維持される
   - メモリ使用量が異常に増加しない

### 5.2 高イテレーション数テスト

1. +キーを連続押下してイテレーション数を大幅に増加
2. **確認事項:**
   - 描画時間が適切な範囲内
   - プログラムが応答不能にならない

## 6. メモリリークテスト

### 6.1 Valgrindによるテスト

```bash
# 基本的なメモリリークチェック
valgrind --leak-check=full ./fractol mandelbrot

# 詳細なメモリ分析
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./fractol julia -0.7 0.27015
```

### 6.2 繰り返し実行テスト

```bash
#!/bin/bash
# 繰り返し実行テスト用スクリプト
for i in {1..10}; do
    timeout 5 ./fractol mandelbrot &
    PID=$!
    sleep 2
    kill $PID 2>/dev/null
    wait $PID 2>/dev/null
    echo "Test $i completed"
done
```

## 7. エラー処理テスト

### 7.1 システムリソース不足シミュレーション

```bash
# メモリ制限下での実行
ulimit -v 100000  # 仮想メモリを制限
./fractol mandelbrot

# ファイルディスクリプタ制限
ulimit -n 10      # ファイル数を制限
./fractol julia -0.4 0.6
```

### 7.2 不正な環境でのテスト

```bash
# DISPLAYが設定されていない場合
unset DISPLAY
./fractol mandelbrot
# 期待結果: 適切なエラーメッセージで終了

# X11が利用できない場合の動作確認
```

## 8. 統合テストスクリプト

以下のスクリプトで主要機能を自動テスト：

```bash
#!/bin/bash
# test_fractol.sh - fract-ol自動テストスクリプト

echo "=== fract-ol 自動テストスクリプト ==="

# ビルドテスト
echo "1. ビルドテスト"
make fclean && make
if [ $? -eq 0 ]; then
    echo "✅ ビルド成功"
else
    echo "❌ ビルド失敗"
    exit 1
fi

# 引数処理テスト
echo "2. 引数処理テスト"
test_cases=(
    "./fractol:1"
    "./fractol invalid:1"
    "./fractol julia:1"
    "./fractol julia abc def:1"
)

for case in "${test_cases[@]}"; do
    IFS=':' read -r cmd expected <<< "$case"
    $cmd > /dev/null 2>&1
    result=$?
    if [ $result -eq $expected ]; then
        echo "✅ $cmd"
    else
        echo "❌ $cmd (expected: $expected, got: $result)"
    fi
done

# メモリリークテスト（Valgrind利用可能な場合）
if command -v valgrind &> /dev/null; then
    echo "3. メモリリークテスト"
    timeout 10 valgrind --leak-check=summary --error-exitcode=1 ./fractol mandelbrot > /dev/null 2>&1 &
    PID=$!
    sleep 3
    kill $PID 2>/dev/null
    wait $PID 2>/dev/null
    if [ $? -eq 0 ]; then
        echo "✅ メモリリークなし"
    else
        echo "⚠️  メモリリーク検出の可能性"
    fi
fi

echo "=== テスト完了 ==="
```

## 9. テスト結果記録テンプレート

```markdown
# fract-ol テスト結果

**テスト実施日**: YYYY/MM/DD
**テスト実施者**: [名前]
**環境**: [OS/ディストリビューション]

## 基礎機能テスト結果

| テストケース | 結果 | 備考 |
|-------------|------|------|
| 引数なし | ✅/❌ | |
| 無効引数 | ✅/❌ | |
| Mandelbrot表示 | ✅/❌ | |
| Julia表示 | ✅/❌ | |
| ESC終了 | ✅/❌ | |
| ×ボタン終了 | ✅/❌ | |

## ボーナス機能テスト結果

| 機能 | 結果 | 備考 |
|------|------|------|
| 矢印キー移動 | ✅/❌ | |
| マウス中心ズーム | ✅/❌ | |
| カラースキーム変更 | ✅/❌ | |
| イテレーション調整 | ✅/❌ | |

## パフォーマンステスト結果

- **極端ズーム**: ✅/❌
- **メモリリーク**: ✅/❌
- **レスポンシブ性**: ✅/❌

## 総合評価

**推定点数**: ___点 / 125点
**主な問題点**: [記録]
**改善提案**: [記録]
```

この手順書に従ってテストを実行することで、fract-olプロジェクトの品質を体系的に評価できます。