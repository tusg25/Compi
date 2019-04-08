typedef int FLOW;
const FLOW FINF=10000;
const int DINF=10000;
struct Dinic{
	struct Edge{
		int u,v,rind;
		FLOW cap,flow;
	};
	int N;
	vector<int> dist,ptr;
	vector<vector<Edge> > v;
	Dinic(int n): N(n),dist(n),ptr(n),v(n){}
	void AddEdge(int from,int to,int cap){
		if(to==from) return;
		int i1=v[from].size(),i2=v[to].size();
		v[from].push_back({from,to,i2,cap,0});
		v[to].push_back({to,from,i1,0,0});
	}
	bool BFS(int s,int t){
		fill(dist.begin(),dist.end(),DINF);
		dist[s]=0;
		queue<int> q;
		q.push(s);
		bool ok=0;
		int curr=0;
		while(!q.empty()){
			int fr=q.front();
			curr=dist[fr]+1;
			q.pop();
			if(fr==t) ok=1;
			for(auto &e: v[fr]){
				if(dist[e.v]>curr && e.flow<e.cap){
					dist[e.v]=curr;
					q.push(e.v);
				}
			}
		}
		return ok;
	}
	FLOW DFS(int s,int t,FLOW res=FINF){
		if(s==t || res==0) return res;
		while(ptr[s]<v[s].size()){
			auto &e=v[s][ptr[s]];
			if(dist[e.v]!=dist[s]+1){
				ptr[s]++;
				continue;
			}
			FLOW f=DFS(e.v,t,min(res,e.cap-e.flow));
			if(f>0){
				e.flow+=f;
				v[e.v][e.rind].flow-=f;
				return f;
			}
			ptr[s]++;
		}
		return 0;
	}
	FLOW maxflow(int s,int t){
		FLOW res=0,curr;
		if(s==t) return 0;
		while(BFS(s,t)){
			fill(ptr.begin(),ptr.end(),0);
			curr=DFS(s,t);
			if(curr==0) break;
			res+=curr;
		}
		return res;
	}
};
