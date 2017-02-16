class primelib{
public:
	vector<int> prime; //prime[i] := iが素数の場合には0, 以外のときはiを割りる最大の素数
	vector<int> memo; 
	primelib(int size):prime(size + 10, 0), memo(size + 10, 0){
		prime_factorization(size + 1);
	}
	//[left,right]までのlcmがmemo[x]:=xの次数 として表される
	void getlcm(int left, int right){
		// fill(memo.begin(), memo.end(), 0); //0で初期化
		for (int i = max(2, left); i <= right; ++i){
			map<int, int> degree; //<x, k> := x^k
			int tmp = i;
			while(prime[tmp]){
				degree[prime[tmp]]++;
				tmp /= prime[tmp]; //最大の素数で割る
			}
			degree[tmp]++; //残った素数をカウント
			//memo[x] := [left, right]までを素因数分解した最大のxの次数を更新
			for(auto u : degree){
				memo[u.first] = max(memo[u.first], u.second);
			}
		}
	}
private:
	//prime[i] := iが素数の場合には0, 以外のときはiを割りる最大の素数
	//これを使えばO(logn)で素因数分解可能
	void prime_factorization(int n){
    	for (int i = 2; i <= n; i++) {
    		if (prime[i] == 0) {
        		for (int j = 2; j * i <= n; j++) {
            		prime[i * j] = i;
        		}
    		}
    	}
    }
};