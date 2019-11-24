// Author Eric Gustin
// Assignment #2
// Description: Implementation of all 6 overloaded operators, unary-,
// binary + and -, such that they can handle and work with vectors.
// This is my integer.cpp file.

#include <iostream>

#include "integer.h"

Integer::Integer() : negative(false)
{
}

Integer::Integer(std::string val) : negative(false)
{
 int n = int(val.size());

 //empty string
 if (n == 0)
 {
  digits.push_back(0);
  return;
 }

 // leading zero
 if (val[0] == '0' && n > 1)
 {
  digits.push_back(0);
  return;
 }

 for (int i = n -1; i >= 0; --i)
 {
  char c = val[i];
  if (std::isdigit(c))
  {
   digits.push_back(c - '0');
  }

  else
  {
   digits.clear();
   digits.push_back(0);
   return;
  }
 }
}

Integer Integer::operator-() const
{
 Integer neg_integer = *this;
 //negate current state of negative value
 neg_integer.negative = !(this->negative);
 return neg_integer;
}


Integer Integer::operator+(const Integer& rhs) const
{
 Integer sum;
 //both negative. All cases.
 if (negative && rhs.negative)
 {
  sum.digits = add(digits, rhs.digits);
  sum = -sum;
 }
 //lhs is negative, rhs is positive
 if (negative && (!rhs.negative))
 {
  //lhs less than or equal to rhs
  if (*this <= rhs)
  {
   sum.digits = sub(rhs.digits, digits);
  }
  //lhs greater than rhs
  else
  {
   sum.digits = sub(digits, rhs.digits);
   sum = -sum;
  }
 }
 //lhs is positive, rhs is negative
 if (!(negative) && rhs.negative)
 {
  //lhs greater than or equal to rhs
  if (*this >= rhs)
  {
   sum.digits = sub(digits, rhs.digits);
  }
  //lhs less than rhs
  else
  {
   sum.digits = sub(rhs.digits, digits);
   sum = -sum;
  }
 }
 //both positive. All cases.
 if ((!negative) && (!rhs.negative))
 {
  sum.digits = add(digits, rhs.digits);
 }
 return sum;
}

Integer Integer::operator-(const Integer& rhs) const
{
 Integer difference;
 //both negative
 if (negative && rhs.negative)
 {
  //lhs less than or equal to rhs
  if (*this <= rhs)
  {
   difference.digits = sub(rhs.digits, digits);
   difference.negative = false;
  }
  //lhs greater than rhs
  else
  {
   difference.digits = sub(digits, rhs.digits);
   difference.negative = true;
  }
 }
 //lhs negative, rhs positive. All cases.
 if (negative && (!rhs.negative))
 {
  difference.digits = add(digits, rhs.digits);
  difference.negative = true;
 }
 //lhs positive, rhs negative. All cases.
 if (!negative && rhs.negative)
 {
  difference.digits = add(digits, rhs.digits);
 }
 //both positive
 if (!negative && (!rhs.negative))
 {
  //lhs greater than or equal to rhs
  if (*this >= rhs)
  {
   difference.digits = sub(digits, rhs.digits);
  }
  //lhs less than rhs
  else
  {
   difference.digits = sub(rhs.digits, digits);
   difference.negative = true;
  }
 }
 return difference;
}

bool Integer::operator<(const Integer& rhs) const
{
 return (less_than(digits, rhs.digits));
}

bool Integer::operator>(const Integer& rhs) const
{
 return less_than(rhs.digits, digits);
}

bool Integer::operator==(const Integer& rhs) const
{
 return !((*this < rhs) || (rhs > *this));
}

bool Integer::operator!=(const Integer& rhs) const
{
 return ((*this < rhs) || (rhs < *this));
}
bool Integer::operator<=(const Integer& rhs) const
{
 return !(rhs < *this);
}

bool Integer::operator>=(const Integer& rhs) const
{
 return !(*this < rhs);
}

bool Integer::less_than(const digit_list& lhs, const digit_list& rhs) const
{
 //lhs contains less digits than rhs
 if (lhs.size() < rhs.size())
 {
  return true;
 }
 //lhs and rhs contain same number of digits as rhs
 if (lhs.size() == rhs.size())
 {
  //iterate through each digit of both vectors, starting at the big endian, & compare
  for (int i = lhs.size()-1; i >= 0; --i)
  {
   if (lhs[i] < rhs[i])
   {
    return true;
   }
   if (lhs[i] > rhs[i])
   {
    return false;
   }
  }
 }
 //lhs has more digits than rhs OR lhs has same number of digits as rhs, but has a higher value
 //i.e. lhs is bigger than rhs
 return false;
}

digit_list Integer::add(const digit_list& lhs, const digit_list& rhs) const
{
 digit_list sum_vctr; 
 //when lhs[i] and rhs[i] sum to greater than 10, then carried will equal 1, and it will
 //be added to the next bigger endian
 int carried = 0;
 int curr_sum = 0;
 const digit_list* shorter = &lhs;
 const digit_list* longer = &rhs;
 if (lhs.size() > rhs.size())
 {
  shorter = &rhs;
  longer = &lhs;
 }
 
 for (long unsigned int i = 0; i < shorter->size(); ++i)
 {
  curr_sum = lhs[i] + rhs[i] + carried;
  if (curr_sum >= 10)
  {
   //append the remainder of dividing by 10 and then carry the 1.
   sum_vctr.push_back(curr_sum % 10);
   carried = 1;
  }
  else
  {
   sum_vctr.push_back(curr_sum);
   carried = 0;
  }
 }
 // appends the remaining digits of the larger
 // original vector to the new sum vector.
 if (longer->size()!= shorter->size())
 {
  for (long unsigned int i = shorter->size(); i < longer->size(); ++i)
  {
   curr_sum = (*longer)[i] + carried;
   if (curr_sum >= 10)
   {
    sum_vctr.push_back(curr_sum % 10);

    carried = 1;
   }
   else
   {
    sum_vctr.push_back((*longer)[i]);
    carried = 0;
   }
  }
 }

 //if lhs and rhs have same length, but the for loop ended with carried = 1, 
 //then append the 1 to the sum vector
 if (carried != 0)
 {
  sum_vctr.push_back(carried);
 }

 return sum_vctr;
}

digit_list Integer::sub(const digit_list& lhs, const digit_list& rhs) const
{
 digit_list diff_vctr;
 const digit_list* longer = &lhs;
 const digit_list* shorter = &rhs;
 //if the current number being subtracted is less than the current subtractor, 
 //then borrow will equal 1. As a result, the current number being subtracted will gain 10
 //and the next number being subtracted will be reduced by 1.
 int borrowed = 0;
 int curr_diff = 0;


 if (lhs.size() < rhs.size())
 {
  longer = &rhs;
  shorter = &lhs;
 }

 for (long unsigned int i = 0; i < shorter->size(); i++)
 {
  if ((lhs[i] - borrowed) >= rhs[i])
  {
   curr_diff = (lhs[i] - borrowed) - rhs[i];
   borrowed = 0;
  }
  else
  {
   //borrow from its neighbor, adding 10 to its value, and reducing 1 from its neighbor
   curr_diff = ((lhs[i] - borrowed) + 10) - rhs[i];
   borrowed = 1;
  }
  diff_vctr.push_back(curr_diff);
 }

 // appends the remaining digits of the larger
 // original vector to the new sum vector.
 if (longer->size()!= shorter->size())
 {
  for (long unsigned int i = shorter->size(); i < longer->size(); ++i)
  {
   curr_diff = (*longer)[i] - borrowed;
   if (curr_diff > 0)
   {
    diff_vctr.push_back(curr_diff);
    borrowed = 0;
   }

  }
 }

//for-loop that removes the zeros at the beginning of the large digit (if applicable)
//for example changes 0001 to 1. 0000 will turn to 0 because loop stops before the final element
for (int j = diff_vctr.size()-1; j > 0; --j)
{
 if (diff_vctr.back() == 0)
 {
  diff_vctr.pop_back();
 }
}
 return diff_vctr;
}

std::ostream& operator<<(std::ostream& out, const Integer& val)
{
 //prepends a minus sign to show that it is negative (if applicable)
 if (val.negative)
 {
  out << "-";
 }
 for (int i = val.digits.size()-1; i >= 0; --i)
 {
  out << val.digits[i];
 }
 return out;
}