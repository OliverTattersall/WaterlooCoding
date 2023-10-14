#ifndef EXTENDEDNUM_H_
#define EXTENDEDNUM_H_
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

struct extendedNum {
  /* Add your data fields and constructor here*/
  bool special;
  string word;
  int val;

  extendedNum(bool special = false, string word = "", int val = 0):
        special {special}, word {word}, val {val} {}

  extendedNum operator+(const extendedNum &rhs) const;
  extendedNum operator-(const extendedNum &rhs) const;
  extendedNum operator*(const extendedNum &rhs) const;
  extendedNum operator/(const extendedNum &rhs) const;
  extendedNum operator-() const;
};

// struct extendedNum;

std::ostream &operator<<(std::ostream &out, const extendedNum &rat);
std::istream &operator>>(std::istream &in, extendedNum &rat);

#endif
