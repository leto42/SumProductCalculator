#include <iostream>
#include <fstream>
#include "Real.h"
using namespace std;

vector<string> getInput(char * filename);
Real getSum(vector<string> nums);
Real getProduct(vector<string> nums);

int main (int argc, char * argv[])
{
        if (argc < 2)
        {
	  printf ("format: %s <filename>\n", argv[0]);
	  exit (1);
        }

	// Get contents from the file.
	vector<string> contents = getInput(argv[1]);
	// Get the sum of the numbers and print them.
	Real sum = getSum(contents);
	cout << "Sum of the contents: " << sum << endl;
	// Get the product of the numbers and print them.
	Real product = getProduct(contents);
	cout << "Product of the contents: " << product << endl;
        return 0;
}

// Get the contents from the file.
vector<string> getInput(char * filename)
{
  ifstream input;
  string num;
  vector<string> str;
  input.open(filename);
  if (input.fail())
    {
      cout << "File " << filename << " not found\n";
      exit (0);
    }
  while(input >> num)
    {
      str.push_back(num);
    }

  return str;
}


// Get the sum of the entire file.
Real getSum(vector<string> nums)
{
  Real sum("0.0");
  for(int i = 0; i < nums.size(); i++)
    {
      sum += (Real)nums[i];
    }
  return sum;
}

// Get the product of the entire file.
Real getProduct(vector<string> nums)
{
  Real product("1.0");
  for(int i = 0; i < nums.size(); i++)
    {
      product *= (Real)nums[i];
    }
  return product;
}
