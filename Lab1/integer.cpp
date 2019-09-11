#include "integer.hpp"

Integer::Integer() = default;

Integer::Integer(const Integer &val)
{
	this->num = val.num;
}

Integer& Integer::operator=(const Integer &val)
{
	this->num = val.num;
}

Integer::Integer(long long val)
{
	while (val)
	{
		this->num.push_back(val % 10);
		val /= 10;
	}
}

Integer::Integer(const std::string &val)
{
    this->num.reserve(val.size());
	for (auto a : val)
	{
		this->num.push_back(a - '0');
	}
	std::reverse(this->num.begin(), this->num.end());
}

Integer Integer::operator+(const Integer &val)
{
    Integer res;

    const size_t max_size = std::max(this->num.size(), val.num.size());
    res.num.reserve(max_size + 1);

    bool carry = false;

    for (int i = 0; i < max_size || carry; i++)
    {
        Byte a = (i < this->num.size() ? this->num[i] : 0);
        Byte b = (i < val.num.size() ? val.num[i] : 0);

        Byte sum = a + b + carry;

        carry = sum >= 10;
        if (carry) sum -= 10;

        res.num.push_back(sum);
    }

    return res;
}


Integer Integer::operator-(const Integer &val)
{
    Integer res;

    const size_t max_size = std::max(this->num.size(), val.num.size());
    res.num.reserve(max_size);

    bool carry = false;

    for (int i = 0; i < max_size; i++)
    {
        Byte a = (i < this->num.size() ? this->num[i] : 0);
        Byte b = (i < val.num.size() ? val.num[i] : 0);

        Byte sub = a - b - carry;

        carry = sub < 0;
        if (carry) sub += 10;

        if (!sub && i == max_size - 1)
            res.num.push_back(sub);
    }

    return res;
}

Integer Integer::operator*(const Integer &val) {
    return Integer();
}


Integer Integer::operator/(const Integer &val)
{

}

Integer::operator int()
{

}

Integer::operator std::string()
{
	std::string res;

	for (auto a : this->num)
		res.push_back(a + '0');

    std::reverse(res.begin(), res.end());

	return res;
}


std::istream & operator>>(std::istream &in, Integer &val)
{
    std::string str;
    in >> str;

    val = Integer(str);

    return in;
}

std::ostream & operator<<(std::ostream &out, Integer val)
{
    out << std::string(val);

    return out;
}