//By Tushar Gautam
#pragma GCC optimize ("-O2")
#include <bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define all(x) x.begin(),x.end()
#define memreset(a) memset(a,0,sizeof(a))
#define testcase(t) int t;cin>>t;while(t--)
#define forstl(i,v) for(auto &i: v)
#define forn(i,e) for(int i = 0; i < e;++i)
#define forsn(i,s,e) for(int i = s; i < e;++i)
#define rforn(i,s) for(int i = s; i >= 0;--i)
#define rforsn(i,s,e) for(int i = s; i >= e;--i)
#define bitcount(a) __builtin_popcount(a) // set bits (add ll)
#define ln '\n'
#define getcurrtime ((double)clock()/CLOCKS_PER_SEC)
#define dbgarr(v,s,e) cerr<<#v<<" = "; forsn(i,s,e) cerr<<v[i]<<", "; cerr<<endl
#define inputfile freopen("input.txt", "r", stdin)
#define outputfile freopen("output.txt", "w", stdout)
#define dbg(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); \
stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) { cerr<<endl; }
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << "\t"; err(++it, args...);
}
template<typename T1,typename T2>
ostream& operator <<(ostream& c,pair<T1,T2> &v){
	c<<"("<<v.fi<<","<<v.se<<")"; return c;
}
template <template <class...> class TT, class ...T>
ostream& operator<<(ostream& out,TT<T...>& c){
    out<<"{ ";
    forstl(x,c) out<<x<<" ";
    out<<"}"; return out;
}
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef pair<ll,ll> p64;
typedef pair<int,int> p32;
typedef pair<int,p32> p96;
typedef vector<ll> v64;
typedef vector<int> v32; 
typedef vector<v32> vv32;
typedef vector<v64> vv64;
typedef vector<p32> vp32;
typedef vector<p64> vp64;
typedef vector<vp32> vvp32;
typedef map<int,int> m32;
const int LIM=3e5+5,MOD=1e9+7;
int t,n,m,k,x,y,w;
v32 v[LIM];
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
int ctm=0,in[LIM],low[LIM];
vp32 bridge;
void dfs(int u=0,int p=0){
	in[u]=low[u]=++ctm;
	forstl(it,v[u]){
		if(it==p) continue;
		if(in[it]) low[u]=min(low[it],low[u]);
		else{
			dfs(it,u);
			low[u]=min(low[u],low[it]);
			if(low[it]>in[u]) bridge.pb({u,it});
			else d.join(u,it);
		}
	}
}
v32 g[LIM];
int h[LIM],mx=0;
void dfs1(int u,int p){
	h[u]=h[p]+1;
	forstl(it,g[u]) if(it!=p) dfs1(it,u);
	if(h[u]>h[mx]) mx=u;
}
signed main(){
	fastio;
	cin>>n>>m;
	d.reset(n);
	forn(i,m){
		cin>>x>>y; --x,--y;
		v[x].pb(y);
		v[y].pb(x);
	}
	dfs();
	int start=0;
	forstl(it,bridge){
		it.fi=d.getpar(it.fi),it.se=d.getpar(it.se);
		g[it.fi].pb(it.se);
		g[it.se].pb(it.fi);
		start=it.fi;
	}
	h[start]=0;
	dfs1(start,start);
	h[mx]=0;
	dfs1(mx,mx);
	cout<< h[mx]-1 <<ln;
	return 0;
}

// Problem https://codeforces.com/contest/1000/problem/E
// dfs find all brideges and g contain bridge tree rest is diameter calculation
