// consultas horriveis uri
int lazy[500000],tree[500000];
int update(int l,int r, int i, int j, int x, int pos) {
  if(lazy[pos] != 0) {
    tree[pos] += (r-l+1)*lazy[pos];
    if(l != r) {
      lazy[2*pos+1] += lazy[pos];
      lazy[2*pos+2] += lazy[pos];
    }
    lazy[pos] = 0;
  }
  if(r < i || l > j)
    return tree[pos];
  if(i <= l && r <= j) {
    tree[pos] += (r-l+1)*x;
    if(l != r) {
      lazy[2*pos+1] += x;
      lazy[2*pos+2] += x;
    }
    return tree[pos];
  }  
  int mid = (l+r)/2;
  return tree[pos] = update(l,mid,i,j,x,2*pos+1) + update(mid+1,r,i,j,x,2*pos+2);
}

int query(int l, int r, int i, int j, int pos) {
  if(lazy[pos] != 0) {
    tree[pos] += (r-l+1)*lazy[pos];
    if(l != r) {
      lazy[2*pos+1] += lazy[pos];
      lazy[2*pos+2] += lazy[pos];
    }
    lazy[pos] = 0;
  }
  if(r < i || l > j)
    return 0;
  if(i <= l && r <= j) {
    return tree[pos];
  }  
  int mid = (l+r)/2;
  return query(l,mid,i,j,2*pos+1) + query(mid+1,r,i,j,2*pos+2);
}