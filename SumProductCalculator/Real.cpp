#include <iostream>
#include <iomanip>
#include "Real.h"
#include <algorithm>

// Constructor
Real::Real()
{
  isPos = true;
  whole = "0";
  fractional = "0";
  number = "0.0";
}

// Copy constructor.
Real::Real(const Real & R)
{
  isPos = R.isPos;
  whole = R.whole;
  fractional = R.fractional;
  number = R.number;
}

// Constructor given two long longs.
Real::Real(long long W, long long D)
{
  string whole_comp = to_string(W);
  string fractional_comp = to_string(D);
  // Check if the number is positive or negative.
  if(W < 0)
    isPos = false;
  else
    isPos = true;

  // Get rid of the sign if there is one.
  if(whole_comp[0] == '-' || whole_comp[0] == '+')
    whole_comp = whole_comp.substr(1);

  // Get rid of trailing zeros of fractional component.
  int trail = 0;
  int frac_length = fractional_comp.length();

  // Count the number of trailing zeros that isn't the very first fractional digit (isn't right before the decimal point).
  if(frac_length > 1 && fractional_comp[frac_length-1] == '0')
    {
      trail++;
      // Start at 2nd last digit because we already know the last was a 0.
      for(int i = frac_length-2; i > 0; i--)
	{
	  // Check if current digit is a 0.
	  if(fractional_comp[i] == '0')
	    trail++;
	  else
	    break;
	}
      // Get the new fractional component without trailing zeros.
      fractional_comp = fractional_comp.substr(0, frac_length-trail);
    }

  // Set the whole and fractional component.
  whole = whole_comp;
  fractional = fractional_comp;
  // Set the full number.
  number = whole + '.' + fractional;
  
}

// Constructor given one double.
Real::Real(double D)
{
  string num_str = to_string(D);
  
  // Check if the number is positive or negative.
  if(D < 0)
    isPos = false;
  else
    isPos = true;

  // Get rid of the sign if there is one.
  if(num_str[0] == '-' || num_str[0] == '+')
    num_str = num_str.substr(1);
  
  // Find where the decimal appears.
  size_t found = num_str.find('.');

  // Check to see if there was no decimal point/fractional component (aka check for an integer).
  if(found == string::npos)
    {
      whole = num_str;
      fractional = "0";
    }
  else
    {
      // Check if the number begins with a decimal point.
      if(num_str[0] == '.')
	{
	  whole = "0";
	  // Get rid of decimal point from the fractional component.
	  fractional = num_str.substr(1);
	}
      else
	{
	  // Grab the integer component.
	  whole = num_str.substr(0, found);

	  // Grab the fracional components (exclude the decimal point)
	  fractional = num_str.substr(found+1);
	}
    }
  
  // Get rid of trailing zeros of fractional component.
  int trail = 0;
  int frac_length = fractional.length();

  // Count the number of trailing zeros that isn't the very first fractional digit (isn't right before the decimal point).
  if(frac_length > 1 && fractional[frac_length-1] == '0')
    {
      trail++;
      // Start at 2nd last digit because we already know the last was a 0.
      for(int i = frac_length-2; i > 0; i--)
	{
	  // Check if current digit is a 0.
	  if(fractional[i] == '0')
	    trail++;
	  else
	    break;
	}
      // Get the new fractional component without trailing zeros.
      fractional = fractional.substr(0, frac_length-trail);
    }
  // Set the full number.
  number = whole + '.' + fractional;
}


// Constructor with string parameter.
Real::Real(const string & S)
{
  string temp;
  bool isValid = false;
  // Check for a + or - sign, if none are specified, the number is positive.
  if(S[0] == '-')
    {
      // Set the sign flag and then chop off the symbol.
      isPos = false;
      temp = S.substr(1,S.length()-1);
    }
  else if(S[0] == '+')
    {
      // The flag by default is true, setting flag for clarity.
      isPos = true;
      temp = S.substr(1,S.length()-1);
    }
  else
    {
      isPos = true;
      temp = S;
    }

  // Check to see if the string is valid (Only contains decimal point, numbers, +, and -).
  int period_count = 0, digit_count = 0;
  int length = temp.length();
  // Go through entire string and count decimal point and digit count. A valid number means that
  // there would be 1 decimal point and the rest as all numbers or all of the string is numbers.
  for(int i = 0; i < length; i++)
    {
      if(isdigit(temp[i]))
	{
	  digit_count++;
	}
      else if(temp[i] == '.')
	{
	  period_count++;
	}
      // Invalid symbol was found meaning that the string is invalid. Set to 0.0.
      else
	{
	  whole = "0";
	  fractional = "0";
	  number = "0.0";
	  isValid = false;
	  isPos = true;
	  break;
	}	      
    }

  // Check to see if decimal point count and digit counts are valid.
  if((digit_count == length) || (digit_count == length-1 && period_count == 1))
    {
      isValid = true;
    }
  else
    {
      whole = "0";
      fractional = "0";
      number = "0.0";
      isValid = false;
      isPos = true;
    }

  if(isValid)
    {
      // Find where the decimal appears.
      size_t found = temp.find('.');

      // Check to see if there was no decimal point/fractional component (aka check for an integer).
      if(found == string::npos)
	{
	  whole = temp;
	  fractional = "0";
	}
      else
	{
	  // Check if the number begins with a decimal point.
	  if(temp[0] == '.')
	    {
	      whole = "0";
	      // Get rid of decimal point from the fractional component.
	      fractional = temp.substr(1);
	    }
	  else
	    {
	      // Grab the integer component.
	      whole = temp.substr(0, found);

	      // Grab the fracional components (exclude the decimal point)
	      fractional = temp.substr(found+1);
	    }
	}
      number = whole + '.' + fractional;
    }
    // Get rid of trailing zeros of fractional component.
  int trail = 0;
  int frac_length = fractional.length();
  
  // Count the number of trailing zeros that isn't the very first fractional digit (isn't right before the decimal point).
  if(frac_length > 1 && fractional[frac_length-1] == '0')
    {
      trail++;
      // Start at 2nd last digit because we already know the last was a 0.
      for(int i = frac_length-2; i > 0; i--)
	{
	  // Check if current digit is a 0.
	  if(fractional[i] == '0')
	    trail++;
	  else
	    break;
	}
      // Get the new fractional component without trailing zeros.
      fractional = fractional.substr(0, frac_length-trail);
    }
  // Set the full number.
  number = whole + '.' + fractional;
  
}

// Destructor
Real::~Real()
{
  // Not allocating memory using "new" for anything.
}

// Assignment operator.
Real & Real::operator = (const Real & R)
{
  if(this == &R)
    {
      return *this;
    }
  
  isPos = R.isPos;
  whole = R.whole;
  fractional = R.fractional;
  number = R.number;

  return *this;
}

// Output stream
ostream & operator << (ostream & outs, const Real & R)
{

  // Check for a 0.0
  if(R.number == "0.0")
    outs << 0;
  // Check to see if a - sign needs to be printed first.
  else if(R.isPos)
    {
      // Check for a whole integer.
      if(R.fractional == "0")
	outs << R.whole;
      else
	outs << R.number;
    }
  else
    {
      // Check for a whole integer.
      if(R.fractional == "0")
	outs << '-' << R.whole;
      else
	outs << '-' << R.number;
    }
  return outs;
}

// Input
istream & operator >> (istream & ins, Real & R)
{
  
  ins >> R.number;
  R = Real(R.number);
  return ins;
}

// Overload + operator.
Real Real::operator + (const Real & R) const
{
  Real result;
  // 4 Scenarios (+ +), (+ -), (- +), (- -).
  
  // First positive, second negative (+ -).
  // Call subtraction overload R1 + -R2 => R1 - R2.
  if(isPos == true && R.isPos == false)
    {
      Real right = Real(R.number);
      result = *this - right;
            
      // Need to track the sign because we'll always be passing in two positive numbers.
      // If the second number is larger than the first, the result is negative.
      if(*this < right)
	result.isPos = false;
      else
	result.isPos = true;
      return result;
    }

  // First negative, second positive (- +).
  // Call subraction overload -R1 + R2 => R2 - R1;
  else if(isPos == false && R.isPos == true)
    {
      // Creating new objects ensures flags will be set to true.
      Real left = Real(number);
      Real right = Real(R.number);
      result = right - left;
      
      // Need to track the sign because we'll always be passing in two positive numbers.
      // If the second number is larger than the first, the result is negative.
      if(left <= right)
	result.isPos = true;
      else
	result.isPos = false;
      return result;
    }
  
  string left_whole = whole;
  string right_whole = R.whole;
  string left_frac = fractional;
  string right_frac = R.fractional;

  // Pad (leading zeros) whole component so they are equal length.
  if(whole.length() > R.whole.length())
    {
      // The first number is bigger. Pad the second number.
      for(int i = 0; i < whole.length() - R.whole.length(); i++)
        {
          right_whole = '0' + right_whole;
        }
    }
  else if(whole.length() < R.whole.length())
    {
      // The second number is bigger. Pad the first number.
      for(int i = 0; i < R.whole.length() - whole.length(); i++)
        {
          left_whole = '0' + left_whole;
        }
    }
  
  // Pad (trailing zeros) fractional component so they are equal length.
  if(fractional.length() > R.fractional.length())
    {
      // The first number is bigger. Pad the second number.
      for(int i = 0; i < fractional.length() - R.fractional.length(); i++)
	{
	  right_frac += '0';
	}
    }
  else if(fractional.length() < R.fractional.length())
    {
      // The second number is bigger. Pad the first number.
      for(int i = 0; i < R.fractional.length() - fractional.length(); i++)
	{
	  left_frac += '0';
	}
    }

  int left_val;
  int right_val;
  int sum;
  string sum_str;
  int carry = 0;
  // Add fractional component first
  // Current index being added, starting from the very last index.
  for(int i = left_frac.length()-1; i >= 0; i--)
    {
      // Add the digits of the current index.
      left_val = (int)left_frac[i] - '0';
      right_val = (int)right_frac[i] - '0';
      // Include the previous carry into the sum and then reset the carry.
      sum = left_val + right_val + carry;
      carry = 0;
      // Get carry (this preserves the last carry for the whole component as well).
      carry = sum / 10;
      // Get string version of the sum.
      sum_str = to_string(sum);
      // If there was a carry, set the current position value to the digit in the ones place.
      if(carry == 1)
	{ 
	  left_frac[i] = sum_str[1];
	}
      // Otherwise, set the current position value to the sum.
      else
	{
	  left_frac[i] = sum_str[0];
	}
      // Reset the sum.
      sum = 0;    
    }

  // Set the result from the fractional component.
  result.fractional = left_frac;
      
  // Pad the carry with leading 0's if needed (so it can be added with the whole component).
  string strCarry = to_string(carry);
  int carry_length = strCarry.length();
  for(int i = 0; i < whole.length() - carry_length; i++)
    {
      strCarry = '0' + strCarry;
    }

  // Add the whole component.
  // Current index being added, starting from the very last index.
  for(int i = left_whole.length()-1; i >= 0; i--)
    {
      // Add the digits of the current index.
      left_val = (int)left_whole[i] - '0';
      right_val = (int)right_whole[i] - '0';
      // Include the previous carry into the sum and then reset the carry.
      sum = left_val + right_val + carry;
      carry = 0;
      // Get carry (this preserves the last carry for the whole component as well).
      carry = sum / 10;
      // Get string version of the sum.
      sum_str = to_string(sum);
      // If we're at the last position and there's a carry, concat the carry to the whole number.
      if(i == 0 && carry == 1)
	{
	  left_whole[i] = sum_str[1];
	  left_whole = '1' + left_whole;
	  break;
	}
      // If there was a carry, set the current position value to the digit in the ones place.
      else if(carry == 1)
	{
	  left_whole[i] = sum_str[1];
	}
      // Otherwise, set the current position value to the sum.
      else
	{
	  left_whole[i] = sum_str[0];
	}
      // Reset the sum.
      sum = 0;
    }
  // Set the result from the whole component.
  result.whole = left_whole;
  // Set the full number.
  result.number = result.whole + '.' + result.fractional;
  // Find whether the number is positive or negative.
  if(isPos)
    result.isPos = true;
  else
    result.isPos = false;
  
  // Get rid of trailing zeros of fractional component.
  int trail = 0;
  string frac = result.fractional;
  int frac_length = frac.length();

  // Count the number of trailing zeros that isn't the very first fractional digit (isn't right before the decimal point).
  if(frac_length > 1 && frac[frac_length-1] == '0')
    {
      trail++;
      // Start at 2nd last digit because we already know the last was a 0.
      for(int i = frac_length-2; i > 0; i--)
	{
	  // Check if current digit is a 0.
	  if(frac[i] == '0')
	    trail++;
	  else
	    break;
	}
      // Get the new fractional component without trailing zeros.
      result.fractional = frac.substr(0, frac_length-trail);
      // Update the full number.
      result.number = result.whole + '.' + result.fractional;
    }
  
  return result;

}

// Overload - operator.
Real Real::operator - (const Real & R) const
{
  Real result;
  int first_value;
  int second_value;
  string left_frac = fractional;
  string right_frac = R.fractional;
  string left_whole = whole;
  string right_whole = R.whole;
  string temp;
  
  // 4 Scenarios (+ +), (+ -), (- +), (- -).

  // First positive, second negative (+ -). Use the + operator.
  if(isPos == true && R.isPos == false)
    {
      // R1 - -R2 => R1 + R2
      // Turn the second number into a positive.
      Real second = R;
      second.isPos = true;
      result = *this + second;
      return result;
    }
  // First negative, second positive. Use the + operator.
  else if(isPos == false && R.isPos == true)
    {
      // -R1 - R2 => -R1 + -R2
      // Turn the second number into a negative.
      Real second = R;
      second.isPos = false;
      result = *this + second;
      return result;
    }
  
  Real left = Real(number);
  Real right = Real(R.number);
  // This will be the isPos for the result.
  bool newSign = true;
  // If the values are the same, we can just return "0.0", the default constructor.
  if(left == right)
    {
      return result;
    }
  // Compare the aboslute value of both numbers.
  // If second value is greater, make it the left operand.
  if(left < right)
    {
      temp = left_frac;
      left_frac = right.fractional;
      right_frac = temp;

      temp = left_whole;
      left_whole = right_whole;
      right_whole = temp;

      // If both results are positive, the result will be negative
      if(isPos == true && R.isPos == true)
	newSign = false;
      // If both results are negative, the result will be positive.
      else if(isPos == false && R.isPos == false)
	newSign = true;
    }

  int l_length = left_whole.length();
  int r_length = right_whole.length();
  int desired;
      
  // Pad (leading zeros) whole component so they are equal length.
  if(l_length > r_length)
    {
      desired = l_length;
      // The first number is bigger. Pad the second number.
      for(int i = 0; i < desired - r_length; i++)
	{
	  right_whole = '0' + right_whole;
	}
    }
  else if(l_length < r_length)
    {
      desired = r_length;
      // The second number is bigger. Pad the first number.
      for(int i = 0; i < desired - l_length; i++)
	{
	  left_whole = '0' + left_whole;
	}
    }

  l_length = left_frac.length();
  r_length = right_frac.length();
  // Pad (trailing zeros) fractional component so they are equal length.
  if(l_length > r_length)
    {
      desired = l_length;
      // The first number is bigger. Pad the second number.
      for(int i = 0; i < desired - r_length; i++)
	{
	  right_frac += '0';
	}
    }
  else if(l_length < r_length)
    {
      desired = r_length;
      // The second number is bigger. Pad the first number.
      for(int i = 0; i < desired - l_length; i++)
	{
	  left_frac += '0';
	}
    }
      
  vector<int> leftValues;
  vector<int> rightValues;
  vector<int> resultValues;
  int value;
  int hold;
  int diff;
      
  // Get whole number values.
  for(int i = 0; i < left_whole.length(); i++)
    {
      value = (int)left_whole[i] - '0';
      leftValues.push_back(value);
      value = (int)right_whole[i] - '0';
      rightValues.push_back(value);
    }

  // Get fractional values.
  for(int i = 0; i < left_frac.length(); i++)
    {
      value = (int)left_frac[i] - '0';
      leftValues.push_back(value);
      value = (int)right_frac[i] - '0';
      rightValues.push_back(value);
    }

  // Subtract the numbers starting from the last index.
  for(int i = leftValues.size()-1; i >= 0; i--)
    {
      diff = leftValues[i] - rightValues[i];
      // Check if the last index can be subtracted without a carry.
      if(diff > -1)
	{
	  // Push the result back if the difference wasn't negative.
	  resultValues.push_back(diff);
	}
      else
	{
	  // Look for a borrow starting from the left index (i-1).
	  for(int j = i-1; j >= 0; j--)
	    {
	      // Can only borrow if the value is > 0.
	      if(leftValues[j] > 0)
		{
		  int hold = j;
		  j = -1;
		  for(int k = hold; k < i; k++)
		    {
		      // Subtract one from the borrow.
		      leftValues[k] -= 1;
		      // Add 10 to the next index (j+1) until we reach the index that needed the borrow.
		      leftValues[k+1] += 10;
		    }
		}
	    }
	  // Get the diff now that there was a borrow.
	  diff = leftValues[i] - rightValues[i];
	  resultValues.push_back(diff);
	}
    }

  // Reverse the vector to count the leading zeros.
  reverse(resultValues.begin(), resultValues.end());

  string resultString = "";
  string no_lead_result = "";
  int lead_count = 0;
  // Count number of leading zeros.
  if(resultValues[0] == 0)
    {
      lead_count++;
      for(int i = 1; i < resultValues.size(); i++)
	{
	  // Check if current and previous index are zeros.
	  if(resultValues[i] == 0 && resultValues[i-1] == 0)
	    lead_count++;
	  else
	    break;
	}
    }

  // Construct the final result without the leading zeros.
  for(int i = lead_count; i < resultValues.size(); i++)
    {
      no_lead_result += to_string(resultValues[i]);
    }

  // Reverse the string so that we can place the decimal point.
  reverse(no_lead_result.begin(), no_lead_result.end());
  for(int i = 0; i < no_lead_result.length(); i++)
    {
      resultString += no_lead_result[i];
      if(i == right_frac.length()-1)
	resultString += '.';
    }

  // Reverse the string one more time to get the final result.
  reverse(resultString.begin(), resultString.end());
  result = Real(resultString);
  result.isPos = newSign;
  
  // Get rid of trailing zeros of fractional component.
  int trail = 0;
  string frac = result.fractional;
  int frac_length = frac.length();

  // Count the number of trailing zeros that isn't the very first fractional digit (isn't right before the decimal point).
  if(frac_length > 1 && frac[frac_length-1] == '0')
    {
      trail++;
      // Start at 2nd last digit because we already know the last was a 0.
      for(int i = frac_length-2; i > 0; i--)
	{
	  // Check if current digit is a 0.
	  if(frac[i] == '0')
	    trail++;
	  else
	    break;
	}
      // Get the new fractional component without trailing zeros.
      result.fractional = frac.substr(0, frac_length-trail);
      // Update the full number.
      result.number = result.whole + '.' + result.fractional;
    }
  return result;
}

// Overload * operator
Real Real::operator * (const Real & R) const
{
  // If one of the numbers is "0.0", just return "0.0"
  if(number == "0.0" || R.number == "0.0")
    return Real();
     
  string left_whole = whole;;
  string left_frac = fractional;
  string right_whole = R.whole;
  string right_frac = R.fractional;

  // Vector that will contain all numbers that will need to be added to obtain the product.
  vector<string> toAdd;
  vector<int> leftValues;
  vector<int> rightValues;
  vector<int> resultValues;
  int value;

  // Get whole number values for left operand.
  for(int i = 0; i < left_whole.length(); i++)
    {
      value = (int)left_whole[i] - '0';
      leftValues.push_back(value);
    }

  // Get whole number values for right operand.
  for(int i = 0; i < right_whole.length(); i++)
    {
      value = (int)right_whole[i] - '0';
      rightValues.push_back(value);
    }

  // Get fractional values for left operand.
  for(int i = 0; i < left_frac.length(); i++)
    {
      value = (int)left_frac[i] - '0';
      leftValues.push_back(value);
    }

  // Get fractional values for right operand.
  for(int i = 0; i < right_frac.length(); i++)
    {
      value = (int)right_frac[i] - '0';
      rightValues.push_back(value);
    }

  // Max length that will be used for padding for adding string values together.
  int max = 0;
  int carry = 0;
  string idx_product = "";

  // Multiply each digit from the left operand with each of the digits of the right operand
  // starting from the right-most digit.
  for(int i = rightValues.size()-1; i >= 0; i--)
    {
      // If the current right operand digit is a 0, ignore current iteration.
      if(rightValues[i] == 0)
	continue;

      // Concatenate 0 depending on what iteration we are on.
      for(int k = 0; k < rightValues.size()-1 - i; k++)
        {
	  idx_product += '0';
        }

      for(int j = leftValues.size()-1; j>=0; j--)
        {
	  // Multiply digits being looked at and add the carry.
	  value = (leftValues[j] * rightValues[i]) + carry;
	  // Get the new carry.
	  carry = value/10;

	  // If we're at the very last index of the LEFT operand, concatenate the entire value.
	  if(j == 0)
            {
	      idx_product = to_string(value) + idx_product;
	      carry = 0;
            }
	  // Otherwise, concatenate the one's digit only to the current index product.
	  else
            {
	      idx_product = to_string(value % 10) + idx_product;
            }
        }
      // Check if there's a new maximum string length.
      if(max < idx_product.length())
        {
	  max = idx_product.length();
        }
      // Store and then reset the index product.
      toAdd.push_back(idx_product);
      idx_product = "";
    }

  // Pad all the numbers.
  int curSize;
  for(int i = 0; i < toAdd.size(); i++ )
    {
      curSize = toAdd[i].length();
      for(int j = 0; j < max - curSize; j++)
        {
	  toAdd[i] = '0' + toAdd[i];
        }
    }

  // Add all the numbers.
  int indexSum = 0;
  string result = "";
  // String version on the index sum.
  string ofIndex;
  carry = 0;

  // This indexing to a particular part of the string in the array toAdd[][i]
  for(int i = max-1; i >= 0; i--)
    {
      // Include the previous carry and then reset it.
      indexSum += carry;
      carry = 0;

      // This is indexing to which string str[j][]
      // Start from the very last index of the string.
      for(int j = 0; j < toAdd.size(); j++)
        {
	  // Add all the indices together.
	  value = (int)toAdd[j][i] - '0';
	  indexSum += value;
	  // Check for a carry when all indices have been added and update the result
	  if(j == toAdd.size()-1)
            {
	      carry = indexSum / 10;
	      // Get the index sum in string form.
	      ofIndex = to_string(indexSum);
	      // Add the last value of the sum to the result.
	      result = ofIndex.back() + result;
            }
        }
      // Reset index sum.
      indexSum = 0;
      // If we're at the last index, concatenate the carry to the result.
      if(i == 0)
        {
	  // Get the index sum in string form.
	  ofIndex = to_string(indexSum);
	  // If there's a carry, concatenate it to the result.
	  if(carry > 0)
	    result = to_string(carry) + result;
        }
    }
  string no_lead_result = "";
  string final_result = "";

  int lead_count = 0;
  // Count number of leading zeros.
  if(result[0] == '0')
    {
      lead_count++;
      for(int i = 1; i < result.length(); i++)
        {
	  // Check if current and previous index are zeros.
	  if(result[i] == '0' && result[i-1] == '0')
	    lead_count++;
	  else
	    break;
        }
    }

  // Construct the final result without the leading zeros.
  for(int i = lead_count; i < result.length(); i++)
    {
      no_lead_result += result[i];
    }
  // Reverse the string so that we can place the decimal point.
  reverse(no_lead_result.begin(), no_lead_result.end());

  for(int i = 0; i < no_lead_result.length(); i++)
    {
      final_result += no_lead_result[i];
      if(i == left_frac.length() + right_frac.length() - 1)
	final_result += '.';
    }

  // Reverse the string one more time to get the final result.
  reverse(final_result.begin(), final_result.end());

    
  Real product = Real(final_result);
  if((isPos == true && R.isPos == false) || (isPos == false && R.isPos == true))
    product.isPos = false;
  else
    product.isPos = true;
  // Get rid of trailing zeros of fractional component.
  int trail = 0;
  string frac = product.fractional;
  int frac_length = frac.length();

  // Count the number of trailing zeros that isn't the very first fractional digit (isn't right before the decimal point).
  if(frac_length > 1 && frac[frac_length-1] == '0')
    {
      trail++;
      // Start at 2nd last digit because we already know the last was a 0.
      for(int i = frac_length-2; i > 0; i--)
	{
	  // Check if current digit is a 0.
	  if(frac[i] == '0')
	    trail++;
	  else
	    break;
	}
      // Get the new fractional component without trailing zeros.
      product.fractional = frac.substr(0, frac_length-trail);
      // Update the full number.
      product.number = product.whole + '.' + product.fractional;
    }
  return product;  
}

// Overload > Operator
bool Real::operator > (const Real & R) const
{
  int first_value;
  int second_value;
  string left_frac = fractional;
  string right_frac = R.fractional;
  // 4 Scenarios (+ +), (+ -), (- +), (- -).
  
  // First positive, second negative (+ -).
  if(isPos == true && R.isPos == false)
    {
      return true;
    }
  // First negative, second positive (- +).
  else if(isPos == false && R.isPos == true)
    {
      return false;
    }

  // Both positive (+ +).
  else if(isPos == true && R.isPos == true)
    {
      // Check length of whole number portion.
      if(whole.length() > R.whole.length())
	{
	  return true;
	}
      else if(whole.length() < R.whole.length())
	{
	  return false;
	}
      // This means whole number length are the same. Start comparing each digit of the whole component.
      for(int i = 0; i < whole.length(); i++)
	{
	  // The integers of the current position.
	  first_value = (int)whole[i] - '0';
	  second_value = (int)R.whole[i] - '0';
	  if(first_value > second_value)
	    {
	      return true;
	    }
	  else if(first_value < second_value)
	    {
	      return false;
	    }
	}
      // If this point is passed, that means the whole component is equal to one another.
      // Pad the fractional component so both lengths match.
      int L_frac_length = fractional.length();
      int R_frac_length = R.fractional.length();
      
      if(L_frac_length > R_frac_length)
	{
	  // The first number is bigger. Pad the second number.
	  for(int i = 0; i < L_frac_length - R_frac_length; i++)
	    {
	      right_frac += '0';
	    } 
	}
      else if(L_frac_length < R_frac_length)
	{
	  // The second number is bigger. Pad the first number.
	  for(int i = 0; i < R_frac_length - L_frac_length; i++)
	    {
	      left_frac += '0';
	    }      
 	}

      // Now compare the fractional component.
      for(int i = 0; i < L_frac_length; i++)
	{
	  first_value = (int)left_frac[i] - '0';
	  second_value = (int)right_frac[i] - '0';
	  if(first_value > second_value)
	    {
	      return true;
	    }
	  else if(first_value < second_value)
	    {
	      return false;
	    }
	}
      
      // The numbers are equal.
      return false;
    }
  
  // Both negative (- -).
  else
    {
      // Check length of whole number portion.
      if(whole.length() > R.whole.length())
	{
	  return false;
	}
      else if(whole.length() < R.whole.length())
	{
	  return true;
	}
      
      // This means whole number length are the same. Start comparing each digit of the whole component.
      for(int i = 0; i < whole.length(); i++)
	{
	  // The integers of the current position.
	  first_value = (int)whole[i] - '0';
	  second_value = (int)R.whole[i] - '0';
	  if(first_value > second_value)
	    {
	      return false;
	    }
	  else if(first_value < second_value)
	    {
	      return true;
	    }
	}
      // If this point is passed, that means the whole component is equal to one another.
      // Pad the fractional component so both lengths match.
      int L_frac_length = fractional.length();
      int R_frac_length = R.fractional.length();

      if(L_frac_length > R_frac_length)
	{
	  // The first number is bigger. Pad the second number.
	  for(int i = 0; i < L_frac_length - R_frac_length; i++)
	    {
	      right_frac += '0';
	    } 
	}
      else if(L_frac_length < R_frac_length)
	{
	  // The second number is bigger. Pad the first number.
	  for(int i = 0; i < R_frac_length - L_frac_length; i++)
	    {
	      left_frac += '0';
	    }      
 	}

      // Now compare the fractional component.
      for(int i = 0; i < L_frac_length; i++)
	{
	  first_value = (int)left_frac[i] - '0';
	  second_value = (int)right_frac[i] - '0';
	  if(first_value > second_value)
	    {
	      return false;
	    }
	  else if(first_value < second_value)
	    {
	      return true;
	    }
	}
      // The numbers are equal.
      return false;
    }
}

// Overload < operator.
bool Real::operator < (const Real & R) const
{
  int first_value;
  int second_value;
  string left_frac = fractional;
  string right_frac = R.fractional;
  // 4 Scenarios (+ +), (+ -), (- +), (- -).
  
  // First positive, second negative (+ -).
  if(isPos == true && R.isPos == false)
    {
      return false;
    }
  // First negative, second positive (- +).
  else if(isPos == false && R.isPos == true)
    {
      return true;
    }

  // Both positive (+ +).
  else if(isPos == true && R.isPos == true)
    {
      // Check length of whole number portion.
      if(whole.length() > R.whole.length())
	{
	  return false;
	}
      else if(whole.length() < R.whole.length())
	{
	  return true;
	}
      
      // This means whole number length are the same. Start comparing each digit of the whole component.
      for(int i = 0; i < whole.length(); i++)
	{
	  // The integers of the current position.
	  first_value = (int)whole[i] - '0';
	  second_value = (int)R.whole[i] - '0';
	  if(first_value > second_value)
	    {
	      return false;
	    }
	  else if(first_value < second_value)
	    {
	      return true;
	    }
	}
      // If this point is passed, that means the whole component is equal to one another.
      // Pad the fractional component so both lengths match.
      int L_frac_length = fractional.length();
      int R_frac_length = R.fractional.length();
      
      if(L_frac_length > R_frac_length)
	{
	  // The first number is bigger. Pad the second number.
	  for(int i = 0; i < L_frac_length - R_frac_length; i++)
	    {
	      right_frac += '0';
	    } 
	}
      else if(L_frac_length < R_frac_length)
	{
	  // The second number is bigger. Pad the first number.
	  for(int i = 0; i < R_frac_length - L_frac_length; i++)
	    {
	      left_frac += '0';
	    }      
 	}

      // Now compare the fractional component.
      for(int i = 0; i < L_frac_length; i++)
	{
	  first_value = (int)left_frac[i] - '0';
	  second_value = (int)right_frac[i] - '0';
	  if(first_value > second_value)
	    {
	      return false;
	    }
	  else if(first_value < second_value)
	    {
	      return true;
	    }
	}
      
      // The numbers are equal.
      return false;
    }
  
  // Both negative (- -).
  else
    {
      // Check length of whole number portion.
      if(whole.length() > R.whole.length())
	{
	  return true;
	}
      else if(whole.length() < R.whole.length())
	{
	  return false;
	}
      
      // This means whole number length are the same. Start comparing each digit of the whole component.
      for(int i = 0; i < whole.length(); i++)
	{
	  // The integers of the current position.
	  first_value = (int)whole[i] - '0';
	  second_value = (int)R.whole[i] - '0';
	  if(first_value > second_value)
	    {
	      return true;
	    }
	  else if(first_value < second_value)
	    {
	      return false;
	    }
	}
      // If this point is passed, that means the whole component is equal to one another.
      // Pad the fractional component so both lengths match.
      int L_frac_length = fractional.length();
      int R_frac_length = R.fractional.length();

      if(L_frac_length > R_frac_length)
	{
	  // The first number is bigger. Pad the second number.
	  for(int i = 0; i < L_frac_length - R_frac_length; i++)
	    {
	      right_frac += '0';
	    } 
	}
      else if(L_frac_length < R_frac_length)
	{
	  // The second number is bigger. Pad the first number.
	  for(int i = 0; i < R_frac_length - L_frac_length; i++)
	    {
	      left_frac += '0';
	    }      
 	}

      // Now compare the fractional component.
      for(int i = 0; i < L_frac_length; i++)
	{
	  first_value = (int)left_frac[i] - '0';
	  second_value = (int)right_frac[i] - '0';
	  if(first_value > second_value)
	    {
	      return true;
	    }
	  else if(first_value < second_value)
	    {
	      return false;
	    }
	}
      // The numbers are equal.
      return false;
    }
}

// Overload == operator.
bool Real::operator == (const Real & R) const
{
  if((*this < R == false) && (*this > R == false))
    return true;
  return false;
}

// Overload != operator.
bool Real::operator != (const Real & R) const
{
  if(*this == R)
    return false;
  return true;
}


// Overload <= operator.
bool Real::operator <= (const Real & R) const
{
  if((*this < R == true) || (*this > R == false))
    return true;
  return false;

}

// Overload >= operator.
bool Real::operator >= (const Real & R) const
{
  if((*this > R == true) || (*this == R == true))
    return true;
  return false;

}

// Pre-increment.
Real Real::operator ++()
{
  // Add 1 to the number and return it.
  *this = *this + Real("1.0");
  return *this;
}

// Post-increment
Real Real::operator ++(int)
{
  // Save the old number, add 1 to it, and then return the old number.
  Real old = *this;
  *this = *this + Real("1.0");
  return old;
}

// Pre-decrement.
Real Real::operator --()
{
  // Subtract 1 to the number and return it.
  *this = *this - Real("1.0");
  return *this;
}

// Post-decrement
Real Real::operator --(int)
{
  // Save the old number, subtract 1 to it, and then return the old number.
  Real old = *this;
  *this = *this - Real("1.0");
  return old;
}

// Addtion compound assignment operator.
Real Real::operator += (const Real & R)
{
  Real result = *this + R;
  *this = result;
  return result;
}

// Subtraction compound assignment operator.
Real Real::operator -= (const Real & R)
{
  Real result = *this - R;
  *this = result;
  return result;
}

// Multiplication compound assignment operator.
Real Real::operator *= (const Real & R)
{
  Real result = *this * R;
  *this = result;
  return result;
}
