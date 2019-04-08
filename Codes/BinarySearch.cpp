// Range = {l, l + 1, ..., r - 1, r} & monotonically inc predicate P,
// find the smallest for which P(x) holds true. return r if fail
while(l<r){
	int mid=(l+r)/2;
	if(P(mid)) r=mid;
	else l=mid+1;
} // after the loop, l = r = x

// if monotonically decreasing predicate P, for largest x. l if fail
while(l<r){
	int mid=(l+r+1)/2;
	if(P(mid)) l=mid;
	else r=mid-1;
} // after the loop, l = r = x

// search in sorted array
bool search(int x[], int n, int k) {
	int l=0,r=n-1;
	while(l<r){
		int mid=(l+r)/2;
		if (x[mid]>=k) r=mid; 
		else l=mid+1;
	}
	return x[l] == k;
}
