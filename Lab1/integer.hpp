#ifndef INTEGER_H
#define INTEGER_H

#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>


using Byte = char;

class Integer
{
private:
	std::vector<Byte> num;

public:
	Integer();
	Integer(const Integer &val);
	Integer & operator=(const Integer &val);

	Integer(long long val);
	Integer(const std::string &val);

	operator std::string();
	operator int();

	Integer operator+(const Integer &val);
	Integer operator-(const Integer &val);
	Integer operator*(const Integer &val);
	Integer operator/(const Integer &val);

    friend std::istream & operator>>(std::istream &in, Integer &val);
    friend std::ostream & operator<<(std::ostream &out, Integer val);
};

#endif // INTEGER_H
