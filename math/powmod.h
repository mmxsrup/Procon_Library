//x^k mod
long long powmod(long long x, long long k, long long m){ // 繰り返し二乗法(logk)
	if(k == 0) return 1;
	if(k % 2 == 0) return powmod(x * x % m, k / 2, m);
	else return x * powmod(x, k - 1, m) % m;
}

/*
 http://arc044.contest.atcoder.jp/tasks/arc044_b
 (http://arc044.contest.atcoder.jp/submissions/1151541)
*/
