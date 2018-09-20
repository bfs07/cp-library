#include <bits/stdc++.h>

#define int long long
using namespace std;

string arr;

struct node {
	int menor, maior;
	node() {}
	node(int menor, int maior) : menor(menor), maior(maior) {}
	node operator^(const node &x) const {
		return node(min(menor, x.menor), max(maior, x.maior));
	}
};

node tree[312345];
node build(int l, int r, int pos) {
	if(l == r)
		return tree[i] = node(arr[l], arr[l]);

	int mid = (l+r) >> 1;
	return tree[pos] = build(l, mid, 2*pos+1)^build(mid + 1, r, 2*pos+2);
}

node query(int l, int r, int i, int j, int pos) {
	if(l > r || l > j || r < i) {
		return node(INF, -INF);
	}

	if(i <= l && r <= j) {
		return tree[pos];
	}

	int mid = (l+r)>>1;
	return query(l, mid, i, j, 2*pos+1)^query(mid+1, r, i, j, 2*pos+2);
}

node update(int l, int r, int ind, int v, int pos) {
	if(l > r || l > j || r < i) {
		return tree[pos];
	}

	if(l == r && l == ind) {
		return node(v, v);
	}

	int mid = (l+r)>>1;
	return tree[pos] = update(l, mid, ind, v, 2*pos+1)^update(mid+1, r, ind, v, 2*pos+2);

}

signed main() {

	string x;

	int n;
	cin >> n;
	cin >> arr;

	
	for(int i = 1; i < x.size(); i++) {
		if(x[i] < x[0]) {
			cout << "No" << endl;
			return 0;
		} else if(x[i] == x[0]) {
			node l = query(0, n-1, 1, i-1, 0);
			node r = query(0, n-1, i+1, n-1, 0);
			if(query(0, n-1, ))
		} else {
			greateR = true;
		}
	}

	
	cout << "Yes" << endl;
}