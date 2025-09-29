# 設計方針

## 課題要件

### 描画

- ジュリア集合とマンデルブロ集合を扱える必要がある
- マウスホイールで、（コンピュータの限界の範囲内で）ほぼ無限にズームイン・ズームアウトができます。これこそが、フラクタルの原理そのものです。
- クリックした位置を中心にズームイン・ズームアウトします。
- プログラムに異なるパラメータを渡すことによって、様々なジュリア集合を作成できなければなりません。
- ウィンドウに表示するフラクタルの種類を指定するために、コマンドラインでパラメータが渡されます。
  - 追加のパラメータを、描画オプションとして使用することもできます。
  - パラメータが渡されなかった場合、またはパラメータが無効だった場合、プログラムは利用可能なパラメータの一覧を表示して、正常に終了します。
- 各フラクタルの深さを表現するために、少なくとも数種類の色を使用しなければなりません。サイケデリックな効果を試すことが推奨されます。

### 表示とイベント処理

- 画像をウィンドウに表示しなければなりません。
- ウィンドウの操作（例：別のウィンドウへの切り替え、最小化など）は、スムーズなままでなければなりません。
- ESCキーを押すと、ウィンドウを閉じてプログラムを正常に終了しなければなりません。
- ウィンドウの枠にあるxボタンをクリックすると、ウィンドウを閉じてプログラムが正常に終了しなければなりません。
- MiniLibXライブラリの画像機能の使用は必須です。

## 使用可能関数

- open
- close
- read
- write
- malloc
- free
- exit
- perror
- strerror
- libftに含まれる関数
- ft_printf
- gettimeoftheday()
- All functions of math library
- MiniLibX functions
  - void *mlx_init();
  - int mlx_loop(void *mlx_ptr);
  - int mlx_loop_hook(void *mlx_ptr, int (*funct_ptr)(void *), void *param);
  - void *mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
  - int mlx_destroy_window(void *mlx_ptr, void *win_ptr);
  - void *mlx_new_image(void *mlx_ptr, int width, int height);
  - char *mlx_get_data_addr(void *img_ptr, int *bits_per_pixel, int *size_line, int *endian);
  - int mlx_put_image_to_window(void *mlx_ptr, void *win_ptr, void *img_ptr, int x, int y);
  - int mlx_destroy_image(void *mlx_ptr, void *img_ptr);
  - int mlx_pixel_put(void *mlx_ptr, void *win_ptr, int x, int y, int color);
  - int mlx_string_put(void *mlx_ptr, void *win_ptr, int x, int y, int color, char *string);
  - int mlx_hook(void *win_ptr, int x_event, int x_mask, int (*funct)(), void *param);

