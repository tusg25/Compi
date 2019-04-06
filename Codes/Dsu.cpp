struct dsu{
    v32 par,rk;
    void reset(int n){
        rk.assign(n,0);
        par.resize(n);
        iota(all(par),0);
    }
    int getpar(int i){
        return (par[i]==i)? i:(par[i]=getpar(par[i]));
    }
    bool con(int i,int j){
        return getpar(i)==getpar(j);
    }
    bool join(int i,int j){
        i=getpar(i),j=getpar(j);
        if(i==j) return 0;
        if(rk[i]>rk[j]) par[j]=i;
        else{
            par[i]=j;
            if(rk[i]==rk[j]) rk[j]++;
        }
        return 1;
    }
} d;
