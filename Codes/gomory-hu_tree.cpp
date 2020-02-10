//Push-Relabel Algorithm for Flows - Gap Heuristic, Complexity: O(V^3)
//To obtain the actual flow values, look at all edges with capacity > 0
//Zero capacity edges are residual edges
struct edge{
	int from, to, cap, flow, index;
	edge(int from, int to, int cap, int flow, int index):
		from(from), to(to), cap(cap), flow(flow), index(index) {}
};
struct PushRelabel{
	int n;
	vector<vector<edge> > g;
	vector<long long> excess;
	vector<int> height, active, count;
	queue<int> Q;
	PushRelabel(int n):
		n(n), g(n), excess(n), height(n), active(n), count(2*n) {}
	void addEdge(int from, int to, int cap){
		g[from].push_back(edge(from, to, cap, 0, g[to].size()));
		if(from==to)
			g[from].back().index++;
		g[to].push_back(edge(to, from, 0, 0, g[from].size()-1));
	}
	void enqueue(int v){
		if(!active[v] && excess[v] > 0)
		{
			active[v]=true;
			Q.push(v);
		}
	}
	void push(edge &e){
		int amt=(int)min(excess[e.from], (long long)e.cap - e.flow);
		if(height[e.from]<=height[e.to] || amt==0)
			return;
		e.flow += amt;
		g[e.to][e.index].flow -= amt;
		excess[e.to] += amt;
		excess[e.from] -= amt;
		enqueue(e.to);
	}
	void relabel(int v){
		count[height[v]]--;
		int d=2*n;
		for(auto &it:g[v]){
			if(it.cap-it.flow>0)
				d=min(d, height[it.to]+1);
		}
		height[v]=d;
		count[height[v]]++;
		enqueue(v);
	}
	void gap(int k){
		for(int v=0;v<n;v++){
			if(height[v]<k)
				continue;
			count[height[v]]--;
			height[v]=max(height[v], n+1);
			count[height[v]]++;
			enqueue(v);
		}
	}
	void discharge(int v){
		for(int i=0; excess[v]>0 && i<g[v].size(); i++)
			push(g[v][i]);
		if(excess[v]>0){
			if(count[height[v]]==1)
				gap(height[v]);
			else
				relabel(v);
		}
	}
	long long max_flow(int source, int dest){
		count[0] = n-1;
		count[n] = 1;
		height[source] = n;
		active[source] = active[dest] = 1;
		for(auto &it:g[source]){
			excess[source]+=it.cap;
			push(it);
		}
		while(!Q.empty()){
			int v=Q.front();
			Q.pop();
			active[v]=false;
			discharge(v);
		}
		long long max_flow=0;
		for(auto &e:g[source])
			max_flow+=e.flow;

		return max_flow;
	}
};
const int maxn = 505,INF = 1e9+10;
struct GomoryHu{
	int vs[maxn],w[maxn][maxn],ans[maxn][maxn],par[maxn],n;
	PushRelabel flow;
	GomoryHu(int n):n(n),flow(n){
		memset(vs,0,sizeof(vs));
		memset(par,0,sizeof(par));
		forn(i,n) forn(j,n) w[i][j]=0,ans[i][j]=INF;
	}
	void addEdge(int u,int v,int c){ w[u][v] += c;}
	void bfs(int s){
		memset(vs,0,sizeof(vs));
		queue<int> q; q.push(s);
		while (!q.empty()){
			int u = q.front(); q.pop();
			forstl(it,flow.g[u]) if(!vs[it.to] && it.flow<it.cap) vs[it.to]=1,q.push(it.to);
		}
	}
	void compute(){
		memset(par,0,sizeof(par));
		forn(i,n) forn(j,n) ans[i][j] = 2e9+30;
		for(int i=1; i<=n-1; ++i){
			flow = PushRelabel(n);
			forn(u,n) forn(v,n) if(w[u][v]) flow.addEdge(u,v,w[u][v]);
			int f = flow.max_flow(i,par[i]);
			bfs(i);
			forsn(j,i+1,n) if (vs[j] && par[j]==par[i]) par[j]=i;
			ans[i][par[i]] = ans[par[i]][i] = f;
			forn(j,i) ans[i][j]=ans[j][i]=min(f,ans[par[i]][j]);
		}
	}
};
