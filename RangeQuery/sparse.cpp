class Sparse{
    private:
    int log2_f(unsigned long long i) {
        return i ? __builtin_clzll(1) - __builtin_clzll(i) : -1;
    }
    public:
    vector<vector<int>>table;
    Sparse(const vector<int>&v){
        int n=v.size();
        int k=log2_f(n);
        table.assign(k+1,vector<int>(n));
        copy(v.begin(),v.end(),table[0].begin());
        for(int i=1;i<=k;i++){
            for(int j=0;j+(1<<i)<=n;j++)
            table[i][j]=min(table[i-1][j],table[i-1][j+(1<<(i-1))]);
        }
    }
    int query(int l,int r){
        int val=log2_f(r-l+1);
        return min(table[val][l],table[val][r-(1<<val)+1]);
    }
};