struct node {
	int pref, suf, tot, best;	
	node () {}
	node(int pref, int suf, int tot, int best) : pref(pref), suf(suf), tot(tot), best(best) {}
};

node tree[500000];
int arr[100000];

node query(int l, int r, int i, int j, int pos) {
	
	node x;
	
	if(l > r || l > j || r < i) {
	return node(-INF, -INF, -INF, -INF);
	}

	if(i <= l && r <= j) {
	return node(tree[pos].pref, tree[pos].suf, tree[pos].tot, tree[pos].best);
	}
	
	int mid = (l + r)/2;
	node left = query(l,mid,i,j,2*pos+1), right = query(mid+1,r,i,j,2*pos+2);
	x.pref = max({left.pref, left.tot, left.tot + right.pref});
	x.suf = max({right.suf, right.tot, right.tot + left.suf});
	x.tot = left.tot + right.tot;
	x.best = max({left.best,right.best, left.suf + right.pref});
	// imprimir.best
	return x;
}

void build(int l, int r, int pos) {
	
	if(l == r) {
	tree[pos] = node(arr[l], arr[l], arr[l], arr[l]);
	return;
	}
	
	int mid = (l + r)/2;
	build(l,mid,2*pos+1); build(mid+1,r,2*pos+2);
	l = 2*pos+1, r = 2*pos+2;
	tree[pos].pref = max({tree[l].pref, tree[l].tot, tree[l].tot + tree[r].pref});
	tree[pos].suf = max({tree[r].suf, tree[r].tot, tree[r].tot + tree[l].suf});
	tree[pos].tot = tree[l].tot + tree[r].tot;
	tree[pos].best = max({tree[l].best,tree[r].best, tree[l].suf + tree[r].pref});
	
}