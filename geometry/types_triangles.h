class Types_triangles{
public:
	int n;
	vector<int> y, x;//y座標　x座標
	const double EPS = 1e-10;
	long long cnt_chokaku = 0, cnt_donkaku = 0, cnt_eikaku = 0;
	Types_triangles(const vector<int> &ty, const vector<int> &tx, int size):y(ty), x(tx), n(size){//n:=座標の数
		count();
	}
private:
	void count(){
		for (int i = 0; i < n; ++i){
			//-M_PI ~ M_PI(-180 ~ 180)
			vector<double> angle;//(x[i], y[i])を原点とした偏角
			for (int j = 0; j < n; ++j){
				if(j == i) continue;
				angle.push_back(atan2(y[j] - y[i], x[j] - x[i]));
			}
			sort(angle.begin(), angle.end());
			for (int j = 0; j < n - 1; ++j){//2周目を作る
				angle.push_back(angle[j] + M_PI*2);
			}
			for (int j = 0; j < n - 1; ++j){
				cnt_chokaku += upper_bound(angle.begin(), angle.end(), angle[j] + M_PI/2.0 + EPS) - lower_bound(angle.begin(), angle.end(), angle[j] + M_PI/2.0 - EPS);
				cnt_donkaku += lower_bound(angle.begin(), angle.end(), angle[j] + M_PI) - upper_bound(angle.begin(), angle.end(), angle[j] + M_PI/2.0 + EPS);
			}
		}
		cnt_eikaku = (ll)n * (n - 1) * (n - 2) / 6 - cnt_chokaku - cnt_donkaku;
	}
};

/*
座標があたえられて、その中でできる三角形のなかで、
鋭角、鈍角、直角がそれぞれいくつずつできるかを求める。
http://abc033.contest.atcoder.jp/tasks/abc033_d
*/