const int MAX_N = 60;
ll com[MAX_N][MAX_N];
void combination(void){ //com[i][j] := iCj
	com[0][0] = 1;
	for (int i = 1; i <= MAX_N - 1; ++i){
		for (int j = 0; j <= i; ++j){
			//パスカルの３角形
			if(j == 0) com[i][j] = com[i - 1][j];
			else com[i][j] = (com[i - 1][j] + com[i - 1][j - 1]);
		}
	}
}

/*
http://abc057.contest.atcoder.jp/tasks/abc057_d
(http://abc057.contest.atcoder.jp/submissions/1184866)
*/