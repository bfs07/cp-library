class BIT
{

private:

	vector<int> bit1;
	vector<int> bit2;
	int n;

private:

	int low(int i)
	{
		return (i & (-i));
	}

	// point update
	void update(int i, const int delta, vector<int> &bit)
	{	
		while(i <= this->n)
		{
			bit[i] += delta;
			i += this->low(i);
		}
	}

	// point query
	int query(int i, const vector<int> &bit)
	{
		int sum = 0;
		while(i > 0)
		{
			sum += bit[i];
			i -= this->low(i);
		}

		return sum;
	}

public:

	BIT(vector<int> &arr)
	{
		this->build(arr);
	}

	BIT(int n)
	{
		// OBS: BIT IS INDEXED FROM 1
		// THE USE OF 1-BASED ARRAY IS RECOMMENDED 
		this->n = n;
		this->bit1.resize(n + 1, 0); 
		this->bit2.resize(n + 1, 0); 
	}

	// build the bit
	int build(vector<int> &arr)
	{
		// OBS: BIT IS INDEXED FROM 1
		// THE USE OF 1-BASED ARRAY IS RECOMMENDED
		assert(arr.front() == 0);
		this->n = (int)arr.size() - 1;
		this->bit1.resize(arr.size(), 0);
		this->bit2.resize(arr.size(), 0);

		for(int i = 1; i <= this->n; i++)
		{
			this->update(i, arr[i]);
		}
	}

	// range update
	void update(int l, int r, const int delta)
	{
		this->update(l, delta, this->bit1);
		this->update(r + 1, -delta, this->bit1);
		this->update(l, delta*(l - 1), this->bit2);
		this->update(r + 1, -delta*r, this->bit2);
	}

	// point update
	void update(int i, const int delta)
	{
		this->update(i, i, delta); 
	}

	// range query
	int query(int l, int r) {
		return this->query(r) - this->query(l - 1);
	}

	// point query
	int query(int i) {
		return (this->query(i, this->bit1)*i) - this->query(i, this->bit2);
	}

};

// TESTS
// signed main()
// {

// 	vector<int> input = {0,1,2,3,4,5,6,7};

// 	BIT ft(input);

// 	assert (1 == ft.query(1));
// 	assert (3 == ft.query(2));
// 	assert (6 == ft.query(3));
// 	assert (10 == ft.query(4));
// 	assert (15 == ft.query(5));
// 	assert (21 == ft.query(6));
// 	assert (28 == ft.query(7));
// 	assert (12 == ft.query(3,5));
// 	assert (21 == ft.query(1,6));
// 	assert (28 == ft.query(1,7));
// }