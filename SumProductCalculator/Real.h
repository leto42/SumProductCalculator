#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Real
{
 public:
  Real();
  Real(const Real & R);
  Real(const string & S);
  Real (long long W, long long D);
  Real (double D);
  ~Real();
  Real & operator = (const Real & R);
  friend ostream & operator << (ostream & outs, const Real & R);
  friend istream & operator >> (istream & ins, Real & R);
  bool operator == (const Real & R) const;
  bool operator != (const Real & R) const;
  bool operator > (const Real & R) const;
  bool operator >= (const Real & R) const;
  bool operator < (const Real & R) const;
  bool operator <= (const Real & R) const;
  Real operator + (const Real & R) const;
  Real operator += (const Real & R);
  Real operator ++ ();
  Real operator ++ (int);
  Real operator - (const Real & R) const;
  Real operator -= (const Real & R);
  Real operator -- ();
  Real operator -- (int);
  Real operator * (const Real & R) const;
  Real operator *= (const Real & R);
 private:
  bool isPos;
  string whole;
  string fractional;
  string number;
};
