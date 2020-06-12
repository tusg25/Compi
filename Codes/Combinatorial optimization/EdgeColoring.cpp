// O(n*m) bipartite min edge coloring
// Ans = max degree , n x n graph 
// Works on multiedges
const int MAXN = 5005,MAXD=200+5 ,MAXM = 1e5+5;
struct edge_color{ // Use 1-based vertices
	int deg[2][MAXN];
	p32 has[2][MAXN][MAXD];
	int color[MAXD];
	int c[2];
	void clear(int n){
		for(int t=0; t<2; t++) for(int i=0; i<=n; i++){
			deg[t][i] = 0;
			for(int j=0; j<=n; j++) has[t][i][j] = mp(0,0);
		}
	}
	void dfs(int x, int p) {
		auto i = has[p][x][c[!p]];
		if (has[!p][i.first][c[p]].second) dfs(i.first,!p);
		else has[!p][i.first][c[!p]] = mp(0,0);
		has[p][x][c[p]] = i;
		has[!p][i.first][c[p]] = mp(x,i.second);
		color[i.second] = c[p];
	}
	int solve(const vector<p32> &v,vector<int> &cv){ // v is edge set and cv is colors
		int m = int(v.size());
		int ans = 0;
		for (int i=1;i<=m;i++) {
			int x[2];
			x[0] = v[i-1].first;
			x[1] = v[i-1].second;
			for (int d=0;d<2;d++) {
				deg[d][x[d]]+=1;
				ans = max(ans,deg[d][x[d]]);
				for (c[d]=1;has[d][x[d]][c[d]].second;c[d]++);
			}
			if (c[0]!=c[1]) dfs(x[1],1);
			for (int d=0;d<2;d++) has[d][x[d]][c[0]] = mp(x[!d],i);
			color[i] = c[0];
		}
		cv.resize(m);
		for(int i=1; i<=m; i++){
			cv[i-1] = color[i];
			color[i] = 0;
		}
		return ans;
	}
} ec;
void example(int n,int m,int t,vp32 &e){
	// n x m with k edges divide almost equally edges for each vertex in t parts
	// make each node into ceil(deg/t) nodes so that max deg <= t then edge color 
	k = e.size();
	int deg1[n+1]={0},deg2[m+1]={0};
	int till1[n+1]={0},till2[m+1]={0};
	vp32 e,re;
	forn(i,k) deg1[x]++,deg2[y]++;
	till1[0] = till2[0] = 1;
	forn(i,n){
		int f = deg1[i+1]/t;
		if(deg1[i+1]%t) f++;
		till1[i+1] = f+till1[i];
		deg1[i+1] = 0;
	}
	forn(i,m){
		int f = deg2[i+1]/t;
		if(deg2[i+1]%t) f++;
		till2[i+1] = f+till2[i];
		deg2[i+1] = 0;
	}
	forstl(it,e){
		int id1 = till1[it.fi-1] + (deg1[it.fi]/t);
		deg1[it.fi]++;
		int id2 = till2[it.se-1] + (deg2[it.se]/t);
		deg2[it.se]++;
		re.pb({id1,id2});
	}
	ec.clear(max(till1[n],till2[m]));
	v32 clr;
	ec.solve(re,clr);
	forstl(it,clr) cout<<it<<" ";
	cout<<ln;
}