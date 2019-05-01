//Binary Search
// Range = {l, l + 1, ..., r - 1, r} & monotonically inc predicate P,
// find the smallest for which P(x) holds true. return r if fail
while(l<r){
	int mid=(l+r)>>1;
	if(P(mid)) r=mid;
	else l=mid+1;
} // after the loop, l = r = x

// if monotonically decreasing predicate P, for largest x. l if fail
while(l<r){
	int mid=(l+r+1)>>1;
	if(P(mid)) l=mid;
	else r=mid-1;
} // after the loop, l = r = x

// search in sorted array
bool search(int x[], int n, int k) {
	int l=0,r=n-1;
	while(l<r){
		int mid=(l+r)>>1;
		if (x[mid]>=k) r=mid; 
		else l=mid+1;
	}
	return x[l] == k;
}


// Parallel Binary Search
int sz,mn,mx;  // number of values,min range, max range
vector<int> lf(sz,mn),rt(sz,mx);
vector<vector<int> > check;
for(int loop=0;loop<20;++loop){
	// Clear stuff
	check.assign(sz,vector<int>(0));
	for(int i=0;i<sz;++i){
		if(lf[i]!=rt[i]){
			int mid=(lf[i]+rt[i])>>1;
			check[mid].push_back(i);
		}
	}
	for(int i=0;i<sz;++i){
		add(i) // add element i
		for(auto &it: check[i]){
			if(conditions()) rt[it]=i; // check for conditions
			else lf[it]=i+1;
		}
	}
}
