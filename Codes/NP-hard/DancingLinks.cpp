const int N=75,M=N*N;
struct DLX{
    int U[M],D[M],R[M],L[M],Row[M],Col[M];
    int H[N],S[N],ans,n,m,vis[N],size;
    void init(int _n,int _m){
        n = _n;
        m = _m;
        for(int i = 0;i <= m;i++){
            S[i] = 0;
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
        }
        R[m] = 0; L[0] = m;
        size = m;ans=0;
        for(int i = 1;i <= n;i++)H[i] = -1;
    }
    void Link(int r,int c){
        ++S[Col[++size]=c];
        Row[size] = r;
        D[size] = D[c];
        U[D[c]] = size;
        U[size] = c;
        D[c] = size;
        if(H[r] < 0)H[r] = L[size] = R[size] = size;
        else{
            R[size] = R[H[r]];
            L[R[H[r]]] = size;
            L[size] = H[r];
            R[H[r]] = size;
        }
    }
	void remove(int c){
		vis[Col[c]]++;
		for(int i=U[c];i!=c;i=U[i])
			L[R[i]]=L[i],R[L[i]]=R[i];
	} 
	void resume(int c){
		vis[Col[c]]--;
		for(int i=U[c];i!=c;i=U[i])
			L[R[i]]=R[L[i]]=i;
	}
	void Dance(int d){
		ans=max(ans,d);
		if(L[0]==0)return;
		int c=L[0];
		for(int i=L[0];i!=0;i=L[i])
			if(S[i]<S[c])
				c=i;
		for(int i=U[c];i!=c;i=U[i])if(!vis[Row[i]]){
			remove(i);
			for(int j=L[i];j!=i;j=L[j])remove(j);
			Dance(d+1);
			for(int j=R[i];j!=i;j=R[j])resume(j);
			resume(i);
		}
	}
}g;
