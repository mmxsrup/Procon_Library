vector<int> imos_one(vector<int> baseimos){
    int basesize = baseimos.size();
    vector<int> imos(basesize, 0); 
    imos[0] = baseimos[0];
    for(int i = 1; i < basesize; ++i){
        imos[i] = imos[i - 1] + baseimos[i];
    }
    return imos;
}