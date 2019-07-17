class BIT
{

private:

	vector<int> bit;
	int n;

private:

	int low(int i)
	{
		return (i & (-i));
	}

public:

	BIT(const vector<int> &arr)
	{
		// OBS: BIT IS INDEXED FROM 1
		// THE USE OF 1-BASED ARRAY IS RECOMMENDED 

		assert(arr.front() == 0);
		this->bit.resize(arr.size(), 0);
		this->n = (int)arr.size() - 1;

		this->build(arr);
	}

	BIT(int n)
	{
		this->n = n;
		this->bit.resize(n + 1, 0); 
	}

	int build(vector<int> &arr)
	{
		// OBS: BIT IS INDEXED FROM 1
		// THE USE OF 1-BASED ARRAY IS RECOMMENDED

		for(int i = 1; i <= this->n; i++)
		{
			this->update(i, arr[i]);
		}
	}

	void update(int i, const int delta)
	{	
		while(i <= this->n)
		{
			this->bit[i] += delta;
			i += this->low(i);
		}
	}

	int query(int i)
	{
		int sum = 0;
		while(i > 0)
		{
			sum += this->bit[i];
			i -= this->low(i);
		}

		return sum;
	}

}

// int main()
// {

// 	vector<int> input = {1,2,3,4,5,6,7};

// 	BIT ft(input);

// 	assert (1 == ft.getSum(binaryIndexedTree, 0));
// 	assert (3 == ft.getSum(binaryIndexedTree, 1));
// 	assert (6 == ft.getSum(binaryIndexedTree, 2));
// 	assert (10 == ft.getSum(binaryIndexedTree, 3));
// 	assert (15 == ft.getSum(binaryIndexedTree, 4));
// 	assert (21 == ft.getSum(binaryIndexedTree, 5));
// 	assert (28 == ft.getSum(binaryIndexedTree, 6));
// }