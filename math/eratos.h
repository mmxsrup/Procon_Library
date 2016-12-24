bool isprime[20010];
//エラトステネス
void eratos(int m){
    for (int i = 0; i <= m; ++i) isprime[i] = true;
    isprime[0] = isprime[1] = false;
    //iを残してiの倍数を消していく
    for (int i = 2; i <= m; ++i){
        if(isprime[i]){
            for (int j = 2 * i; j <= m; j += i){
                isprime[j] = false;
            }
        }
    }
}