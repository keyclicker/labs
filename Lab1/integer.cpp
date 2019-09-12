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
    this->num.clear();
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

Integer Integer::operator+(const Integer &val) const
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


Integer Integer::operator-(const Integer &val) const
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

        if (sub || i != max_size - 1)
            res.num.push_back(sub);
    }

    return res;
}

Integer Integer::operator*(const Integer &val) const
{
    Integer res;

    //Needs optimization
    res.num = std::vector<Byte>(this->num.size() + val.num.size());

    for (size_t i = 0; i < this->num.size(); i++)
    {
        int carry = 0;
        for (size_t j = 0; j < val.num.size() || carry; j++)
        {
            long long cur = res.num[i+j] + this->num[i] *
                                (j < val.num.size() ? val.num[j] : 0) + carry;

            res.num[i+j] = cur % 10;
            carry = cur / 10;
        }
    }

    while (res.num.size() > 1 && !res.num.back())
        res.num.pop_back();

    return res;
}


Integer Integer::operator/(const long long val) const
{
    Integer res;

    //Needs optimization
    res.num = std::vector<Byte>(this->num.size());

    long long carry = 0;
    for (int i = this->num.size() - 1; i >= 0; i--)
    {
        long long cur = this->num[i] + carry * 10;

        res.num[i] = cur / val;
        carry = cur % val;
    }

    while (res.num.size() > 1 && !res.num.back())
        res.num.pop_back();

    return res;
}

bool Integer::operator>(const Integer &val) const
{
    if (this->num.size() != val.num.size())
        return this->num.size() > val.num.size();
    else
        for (int i = this->num.size(); i >= 0; i--)
            if (this->num[i] != val.num[i])
                return this->num[i] > val.num[i];

    return false;
}

bool Integer::operator<(const Integer &val) const
{
    if (this->num.size() != val.num.size())
        return this->num.size() < val.num.size();
    else
        for (int i = this->num.size(); i >= 0; i--)
            if (this->num[i] != val.num[i])
                return this->num[i] < val.num[i];

    return false;
}

bool Integer::operator>=(const Integer &val) const
{
    if (this->num.size() != val.num.size())
        return this->num.size() > val.num.size();
    else
        for (int i = this->num.size(); i >= 0; i--)
            if (this->num[i] != val.num[i])
                return this->num[i] > val.num[i];

    return true;
}

bool Integer::operator<=(const Integer &val) const
{
    if (this->num.size() != val.num.size())
        return this->num.size() < val.num.size();
    else
        for (int i = this->num.size(); i >= 0; i--)
            if (this->num[i] != val.num[i])
                return this->num[i] < val.num[i];

    return true;
}

bool Integer::operator==(const Integer &val) const
{
    if (this->num.size() != val.num.size())
        return false;
    else
        for (int i = this->num.size(); i >= 0; --i)
            if (this->num[i] != val.num[i])
                return false;

    return true;
}



Integer::operator int() const
{

}

Integer::operator std::string() const
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