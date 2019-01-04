struct node {
	
	int menor, maior, lazy;
	node() {}
	node(int menor, int maior, int lazy) : menor(menor), maior(maior), lazy(lazy) {}

	node operator^(const node &x) const {
		return node(min(menor, x.menor), max(maior, x.maior), 0);
	}

};

int arr[1000003];
node tree[4123456];

void propagate(int l, int r, int pos) {

	if(tree[pos].lazy != 0) {
		tree[pos].menor += tree[pos].lazy; 
		tree[pos].maior += tree[pos].lazy; 
		if(l != r) {
			tree[2*pos+1].lazy += tree[pos].lazy;
			tree[2*pos+2].lazy += tree[pos].lazy;
		}
		tree[pos].lazy = 0;
	}

}

node build(int l, int r, int pos) {
	if(l == r)
		return tree[pos] = node(arr[l], arr[l], 0);

	int mid = (l+r) >> 1;
	return tree[pos] = build(l, mid, 2*pos+1)^build(mid + 1, r, 2*pos+2);
}

node query(int l, int r, int i, int j, int pos) {
	
	propagate(l, r, pos);

	if(l > r || l > j || r < i) {
		return node(INF, -INF, 0);
	}

	if(i <= l && r <= j) {
		return tree[pos];
	}

	int mid = (l+r)>>1;
	return query(l, mid, i, j, 2*pos+1)^query(mid+1, r, i, j, 2*pos+2);
}

// range sum update
node update(int l, int r, int i, int j, int v, int pos) {

	propagate(l, r, pos);

	if(l > r || l > j || r < i) {
		return tree[pos];
	}

	if(i <= l && r <= j) {
    tree[pos].lazy += v;
    propagate(l, r, pos);
		return tree[pos] = node(tree[pos].menor, tree[pos].maior, 0);
	}

	int mid = (l+r)>>1;
	return tree[pos] = update(l, mid, i, j, v, 2*pos+1)^update(mid+1, r, i, j, v, 2*pos+2);

}
