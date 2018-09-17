# include<iostream>
# include<vector>
# include<string>

using namespace std;

// The input array contains four numbers, and we want to check if they can be combined to get 24
bool judge24(vector<int>& nums)
{
	return try_pattern_one(nums) || try_pattern_two(nums);
}


vector<double> try_pair(double x, double y, string operators = "+-*/")
{
	vector<double> res;
	for (int i = 0; i < operators.size(); ++i)
	{
		char op = operators[i];
		if (op == '+')                    res.push_back(x + y);
		else if (op == '-')	              { res.push_back(x - y);  res.push_back(y - x); }
		// be careful that subtraction and division do not commute, so we need to consider two orders
		else if (op == '*')               res.push_back(x * y);
		else if (op == '/' && x*y != 0)   { res.push_back(x / y);  res.push_back(y / x); }
	}
	return res;
}


// helper function to check if two doubles can be considered equal in this case
bool compareDouble(double x, double y);


bool try_two_pairs(int x1, int y1, int x2, int y2)
{
	vector<double> out_one = try_pair(x1, y1, "+-");
	vector<double> out_two = try_pair(x2, y2, "+-");

	for (int i = 0; i < out_one.size(); ++i)
		for (int j = 0; j < out_two.size(); ++j)
		{
			vector<double> temp = try_pair(out_one[i], out_two[j], "*/");
			for (int k = 0; k < temp.size(); ++k)
				if (compareDouble(temp[k], 24))
					return true;
		}
	return false;
}

bool try_pattern_two(vector<int>& nums)
{
	return (try_two_pairs(nums[0], nums[1], nums[2], nums[3]) ||
			try_two_pairs(nums[0], nums[2], nums[1], nums[3]) ||
			try_two_pairs(nums[0], nums[3], nums[1], nums[2]));
		
}

struct order
{
	int a;
	int b;
	int c;
	int d;
};

bool try_associative(int a, int b, int c, int d);

bool try_pattern_one(vector<int>& nums)
{
	const vector<order> perm = { {1, 2, 3, 4}, {1, 2, 4, 3}, {1, 3, 2, 4}, {1, 3, 4, 2}, {1, 4, 2, 3}, {1, 4, 3, 2},
								 {2, 3, 1, 4}, {2, 3, 4, 1}, {2, 4, 1, 3}, {2, 4, 3, 1}, {3, 4, 1, 2}, {3, 4, 2, 1} };

	for (auto it = perm.begin(); it != perm.end(); ++it)
	{	
		order curr = *it;
		if (try_associative(nums[curr.a - 1], nums[curr.b - 1], nums[curr.c - 1], nums[curr.d - 1]))
			return true;
	}
	return false;

}


bool try_associative(int a, int b, int c, int d)
{	
	vector<double> out_one, out_two;
	out_one = try_pair(a, b);
	for (int i = 0; i < out_one.size(); ++i)
	{
		vector<double> temp = try_pair(out_one[i], c);
		out_two.insert(out_two.end(), temp.begin(), temp.end());
	}
	// cerr << out_two[31] << out_two[32] << out_two[33];

	for (int j = 0; j < out_two.size(); ++j)
	{
		vector<double> temp = try_pair(out_two[j], d);
		for (int k = 0; k < temp.size(); ++k)
			if (compareDouble(temp[k], 24))
				return true;
	}
	return false;
}

bool compareDouble(double x, double y)
{
	double diff = x - y;
	return diff < 1e-5 && -diff < 1e-5;
}

int main()
{

	/*
	vector<int> test1 = {4, 1, 8, 7};
	vector<int> test2 = {1, 2, 3, 3};
	vector<int> test3 = { 1, 1, 1, 8 };
	vector<int> test4 = { 1, 1, 2, 6 };
	vector<int> test5 = {1, 2, 1, 7};
	cout << try_pattern_two(test1);
	cout << try_pattern_two(test2) << endl;
	cout << try_pattern_one(test3);
	cout << try_pattern_one(test4);
	cout << try_pattern_one(test5);
	cout << try_pattern_two(test5) << endl;
	*/
	
	cout << "the test for numbers 3, 3, 8, 8" << endl;;
	vector<int> test6 = { 3, 3, 8, 8 };
	cout << try_associative(3, 8, 3, 8) << endl;

	cout << "The test for numbers 1, 1, 7, 7" << endl;
	vector<int> test7 = { 1, 1, 7, 7 };
	cout << try_pattern_one(test7) << endl;
	
}

