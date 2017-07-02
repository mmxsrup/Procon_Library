/*
 * 二次元累積和(長方形内の値の合計を出す問題)
 */

// O(hw)
void sum2D(int h, int w) { // a の縦と横の長さ
	rep(y, h + 1)rep(x, w + 1) sum[y][x] = 0;
	rep(y, h)rep(x, w) sum[y + 1][x + 1] = a[y][x]; // まずは埋め込む
	rep(y, h + 1)rep(x, w) sum[y][x + 1] += sum[y][x]; // 横
	rep(y, h)rep(x, w + 1) sum[y + 1][x] += sum[y][x]; // 縦
}
// O(1)
int calcSum(int y1, int x1, int y2, int x2) { // 求めたい長方形の左上, 右下の座標
	return sum[y2 + 1][x2 + 1] - sum[y2 + 1][x1] - sum[y1][x2 + 1] + sum[y1][x1];
}

/*
"まずは埋め込む" の部分のaは書き換える
aoj 1176

*/