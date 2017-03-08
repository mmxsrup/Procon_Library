/*
 呼びだし方
 segtree<int> seg(n); // int型の要素で nは要素の数
*/

template <class T> //T : dat[]の中身の型
class segtree{
public:
	int n;
	vector<T> dat;
	segtree(int n_): n(n_){ //n_要素数
		n = 1;
		while(n < n_) n *= 2;
		dat.resize(n * 2, INF); //(1) 初期値を最大に
	}
	void update(int k, T val){ // k番目の値(0-indexed)を val に変更
		for (dat[k += n] = val; k > 0; k >>= 1){ // kを含む区間のインデックスを下から順に列挙
			dat[k>>1] = min(dat[k], dat[k ^ 1]); // (2) 区間の最大値で更新
		}
	}
	T query(int l, int r){
		T ret = INF; //(3) 最小値に関係ない値
		for (l += n, r += n; l < r; l >>= 1, r >>= 1){
			if(l & 1) ret = min(ret, dat[l++]); //(4) 区間の最小値で更新
			if(r & 1) ret = min(ret, dat[--r]); //(4) 区間の最小値で更新
		}
		return ret;
	}
};


/*
segtree すこし高速化
更新: 1 点
クエリ: 区間の最小値
note: (1)~(4)を変えることで対応可能
http://arc045.contest.atcoder.jp/tasks/arc045_b
(http://arc045.contest.atcoder.jp/submissions/1151765)
*/
