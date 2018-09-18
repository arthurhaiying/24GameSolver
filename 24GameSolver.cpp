
# include<iostream>
# include<string>
# include<vector>

// implementation of a 24 game solver using depth first search
// given four cards, determine whether a solution exists and return the solution

using namespace std;

struct card  // the definition of a card, a value and how this value is obtained
{
	double val;
	string msg;
};

// a recurrent solve24 function that uses the remained numbers and the result from previous operation 

bool Solve24_rec(vector<card>& nums, string& solution);

// the nums array contain four numbers from 1 to 9, 
// check if you can do arithmetic operations +, -, *, /, on these numbers and get twenty-four
bool Solve24(vector<int>& nums, string& solution)
{
	vector<card> input;
	for (int i = 0; i < nums.size(); ++i)
		input.push_back({ (double) nums[i], to_string(nums[i]) });

	return Solve24_rec(input, solution);
}


// helper function to check if a string contains some char
bool hasChar(string s, char c)
{
	for (int i = 0; i < s.size(); ++i)
		if (s[i] == c)
			return true;
	return false;
}

// helper function to check if a string contains a certain char not enclosed by parenthesis
bool has_unbound_operator(string msg, string op)
{
	string s;
	for (int i = 0; i < msg.size(); ++i)
		if (!(isdigit(msg[i]) || msg[i] == ' '))
			s += msg[i];
	
	bool res = false;
	for (int j = 0; j < op.size(); ++j)
		for (int k = 0; k < s.size(); ++k)
			if (s[k] == '(')
				k += 2;
			else if (s[k] == op[j])
				res = true;
	return res;

}


string update_message(string lhs, string rhs, char op)
{
	if (op == '+')
		return lhs + ' ' + op + ' ' + rhs;
	else if (op == '-')
	{
		// if the right operand contains an unbounded minus sign
		if (has_unbound_operator(rhs, "-"))
			rhs = '(' + rhs + ')';
		return lhs + ' ' + op + ' ' + rhs;
	}
	else if (op == '*')
	{
		if (has_unbound_operator(lhs, "+-"))
			lhs = '(' + lhs + ')';
		// need to add paranthensis if there is unbound plus or minus sign
		if (has_unbound_operator(rhs, "+-"))
			rhs = '(' + rhs + ')';
		// need to add paranthesis if there is unbound plus or minus sign
		return lhs + ' ' + op + ' ' + rhs;
	}

	else if (op == '/')
	{
		if (has_unbound_operator(lhs, "+-"))
			lhs = '(' + lhs + ')';
		if (has_unbound_operator(rhs, "+-/"))
			rhs = '(' + rhs + ')';
		return lhs + ' ' + op + ' ' + rhs;
	}
	else
		cerr << "There is invalid operation" << endl;
}


// check if two doubles can be considered equal in this problem
bool compareDouble(double x, double y)
{
	int diff = x - y;
	return diff < 1e-5 && -diff < 1e-5;
}

// We use a recurrent approach. First, we choose two numbers, try different operations
// and then check if we can get 24 with the rest numbers and one of the result
bool Solve24_rec(vector<card>& nums, string& solution)
{
	int n = nums.size();
	if (n == 0)
		return false;
	else if (n == 1 && compareDouble(nums[0].val, 24.0))
	{
		solution = nums[0].msg; // record how the answer is obtained
		return true;
	}
	else if (n == 1)
		return false;

	for (int i = 0; i < n; ++i)
		for (int j = i + 1; j < n; ++j)
		{
			card left = nums[i];
			card right = nums[j];

			vector<card> nums_rest;
			for (int k = 0; k < n; ++k)
				if (k != i && k != j)
					nums_rest.push_back(nums[k]);

			for (int k = 0; k < 6; ++k)
			{
				// try all possible six operations with the two numbers
				// notice that left - right and right - left, left / right and right / left are different operations
				vector<card> temp = nums_rest;
				if (k == 0) temp.push_back({ left.val + right.val, update_message(left.msg, right.msg, '+') });
				else if (k == 1) temp.push_back({ left.val - right.val, update_message(left.msg, right.msg, '-') });
				else if (k == 2) temp.push_back({ right.val - left.val, update_message(right.msg, left.msg, '-') });
				else if (k == 3) temp.push_back({ left.val * right.val, update_message(left.msg, right.msg, '*') });
				else if (k == 4 && right.val != 0) temp.push_back({ left.val / right.val, update_message(left.msg, right.msg, '/') });
				else if (k == 5 && left.val != 0) temp.push_back({ right.val / left.val, update_message(left.msg, right.msg, '/') });

				if (Solve24_rec(temp, solution))
					return true;
			}

		}

	return false;
}


int main()
{
	vector<int> test = {2, 1, 3, 8};
	vector<int> test1 = { 7, 6, 6, 5 };
	vector<int> test2 = { 1, 2, 3, 7 };
	vector<int> test3 = { 6, 6, 7, 7 };
	vector<int> test4 = { 1, 3, 10, 8};
	
	string method, method1, method2;
	bool out = Solve24(test, method);
	bool out1 = Solve24(test4, method1);
	cout << "the solution of 2, 1, 3, 8 is: " << out << ' ' << method << endl;
	cout << "the solution for 4, 4, 1, 3 is: " << out1 << ' ' << method1 << endl;
}