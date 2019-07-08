class STree
{

public:

    struct Node 
    {
        
        int menor, maior, sum, lazy;

        Node() {}
        // if it's a leaf node
        Node(int menor, int maior, int lazy) : menor(menor), maior(maior), sum(maior), lazy(lazy)
        {
            assert(menor == maior);
        }
        Node(int menor, int maior, int sum, int lazy) : menor(menor), maior(maior), sum(sum), lazy(lazy) {}

        Node operator^(const Node &x) const 
        {
            return Node(min(menor, x.menor), max(maior, x.maior), sum + x.sum, 0);
        }

    };

    STree() 
    {
        this->n = -1;
    }
    STree(vector<int> &arr) 
    {
        this->build(arr);
    }

    void build(vector<int> &arr) 
    {
        this->n = arr.size();
        tree.resize(4*this->n);
        this->st_build(0, this->n - 1, arr, 0);
    }

    // update at a single index
    void update(const int i, int v) 
    {
        assert(n >= 0);
        this->st_update(0, this->n - 1, i, i, v, 0);
    }

    // range update
    void update(const int l, const int r, int v) {
        assert(n >= 0);
        this->st_update(0, this->n - 1, l, r, v, 0);
    }

    Node query(const int l, const int r) 
    {
        assert(n >= 0);
        return this->st_query(0, this->n - 1, l, r, 0);
    }

private:

    void st_propagate(const int l, const int r, const int pos) 
    {

        if(tree[pos].lazy != 0) 
        {
            tree[pos].menor += tree[pos].lazy; 
            tree[pos].maior += tree[pos].lazy;
            tree[pos].sum += (r - l + 1)*tree[pos].lazy;
            if(l != r)
            {
                tree[2*pos+1].lazy += tree[pos].lazy;
                tree[2*pos+2].lazy += tree[pos].lazy;
            }
            tree[pos].lazy = 0;
        }

    }

    Node st_build(int l, int r, vector<int> &arr, const int pos)
    {
        if(l == r)
            return tree[pos] = Node(arr[l], arr[l], 0);

        int mid = (l+r) >> 1;
        return tree[pos] = st_build(l, mid, arr, 2*pos+1)^st_build(mid + 1, r, arr, 2*pos+2);
    }

    Node st_query(int l, int r, const int i, const int j, const int pos)
    { 
        st_propagate(l, r, pos);

        if(l > r || l > j || r < i)
        {
            return Node(INF, -INF, 0, 0);
        }

        if(i <= l && r <= j)
        {
            return tree[pos];
        }

        int mid = (l+r)>>1;
        return st_query(l, mid, i, j, 2*pos+1)^st_query(mid+1, r, i, j, 2*pos+2);
    }

    // it adds a number v to the range from i to j
    Node st_update(int l, int r, const int i, const int j, const int v, const int pos)
    {
        st_propagate(l, r, pos);

        if(l > r || l > j || r < i)
        {
            return tree[pos];
        }

        if(i <= l && r <= j)
        {
            tree[pos].lazy += v;
            st_propagate(l, r, pos);
            return tree[pos] = Node(tree[pos].menor, tree[pos].maior, tree[pos].sum, 0);
        }

        int mid = (l+r)>>1;
        return tree[pos] = st_update(l, mid, i, j, v, 2*pos+1)^st_update(mid+1, r, i, j, v, 2*pos+2);

    }

public:
    int n;
    vector<Node> tree;
};