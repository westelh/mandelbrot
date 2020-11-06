# Mandelbrot Set
マンデルブロ集合をbitmapに描く。  
~~コンパイルには[GNU MPFR](https://www.mpfr.org/)と、[MPFR C++](http://www.holoborodko.com/pavel/mpfr/)が必要。~~ 複素数の無限大の計算がうまくいってないっぽいのでとりあえずdoubleにしている。  
画像データを生成する関数の引数は以下
```cpp
std::vector<std::vector<pixel>> mandelbrot_bmp_multithread(
	const complex_t center /*画像領域の中心座標を表す複素数*/,
	const complex_t range /*画像領域の広さ(実部、虚部の変域)を表す複素数*/,
	const std::vector<pixel> gradation_waypoint /*グラデーションのための色集合*/,
	const unsigned width /*画像の幅*/,
	const unsigned height /*画像の高さ*/,
	const int num_of_threads /*実行スレッド数*/
);
```
コマンドライン引数からファイル名を指定する。  
```
$ ./a.out mandelbrot.bmp
```
