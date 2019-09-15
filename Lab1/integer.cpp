#include <cmath>
#include "integer.hpp"

Integer::Integer() = default;
Integer::Integer(const Integer &val) = default;
Integer &Integer::operator=(const Integer &val) = default;

Integer::Integer(long long val)
{
  if (val < 0)
  {
    this->negetive = true;
    val *= -1;
  }

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

  if (val.front() == '-')
    this->negetive = true;
  else
    this->num.push_back(val.front());

  for (size_t i = 1; i < val.size(); i++)
  {
    this->num.push_back(val[i] - '0');
  }
  std::reverse(this->num.begin(), this->num.end());
}

Integer Integer::operator+(const Integer &val) const
{
  if (!this->negetive && !val.negetive)
    return sum(*this, val);
  else if (this->negetive && !val.negetive)
    return sub(val, *this);
  else if (!this->negetive && val.negetive)
    return sub(*this, val);
  else if (this->negetive && val.negetive)
  {
    auto res = sum(*this, val);
    res.negetive = true;
    return res;
  }
}

Integer Integer::operator-(const Integer &val) const
{
  if (!this->negetive && !val.negetive)
    return sub(*this, val);
  else if (this->negetive && !val.negetive)
  {
    auto tmp = sum(*this, val);
    tmp.negetive = true;
    return tmp;
  }
  else if (!this->negetive && val.negetive)
    return sum(*this, val);
  else if (this->negetive && val.negetive)
    return sub(val.negetive, this->negetive);
}

Integer Integer::operator*(const Integer &val) const
{
  Integer res;
  res.negetive = !this->negetive != !val.negetive;

  //Needs optimization
  res.num = std::vector<Byte>(this->num.size() + val.num.size());

  for (size_t i = 0; i < this->num.size(); i++)
  {
    int carry = 0;
    for (size_t j = 0; j < val.num.size() || carry; j++)
    {
      long long cur = res.num[i + j] + this->num[i] *
                                       (j < val.num.size() ? val.num[j] : 0) +
                      carry;

      res.num[i + j] = cur % 10;
      carry = cur / 10;
    }
  }

  while (res.num.size() > 1 && !res.num.back())
    res.num.pop_back();

  return res;
}


Integer Integer::operator/(long long val) const
{
  Integer res;
  res.negetive = !this->negetive != (val >= 0);
  val = std::abs(val);

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
  int res = 0;
  for (int i = this->num.size(); i >= 0; i--)
  {
    res += this->num[i]*std::pow(10, i);
  }
  if (this->negetive) res *= -1;

  return res;
}

Integer::operator std::string() const
{
  std::string res;

  for (auto a : this->num)
    res.push_back(a + '0');

  if (this->negetive) res.push_back('-');

  std::reverse(res.begin(), res.end());

  return res;
}


std::istream &operator>>(std::istream &in, Integer &val)
{
  std::string str;
  in >> str;

  val = Integer(str);

  return in;
}

std::ostream &operator<<(std::ostream &out, Integer val)
{
  out << std::string(val);

  return out;
}

Integer Integer::sum(const Integer &a, const Integer &b)
{
  Integer res;

  const size_t max_size = std::max(a.num.size(), b.num.size());
  res.num.reserve(max_size + 1);

  bool carry = false;

  for (int i = 0; i < max_size || carry; i++)
  {
    Byte ab = (i < a.num.size() ? a.num[i] : 0);
    Byte bb = (i < b.num.size() ? b.num[i] : 0);

    Byte sum = ab + bb + carry;

    carry = sum >= 10;
    if (carry) sum -= 10;

    res.num.push_back(sum);
  }

  return res;
}

Integer Integer::sub(const Integer &a_, const Integer &b_)
{
  const Integer *a, *b;
  Integer res;

  if (a_ > b_)
  {
    a = &a_;
    b = &b_;
  }
  else
  {
    a = &b_;
    b = &a_;
    res.negetive = true;
  }

  const size_t max_size = std::max(a->num.size(), b->num.size());
  res.num.reserve(max_size);

  bool carry = false;

  for (int i = 0; i < max_size; i++)
  {
    Byte ab = (i < a->num.size() ? a->num[i] : 0);
    Byte bb = (i < b->num.size() ? b->num[i] : 0);

    Byte sub = ab - bb - carry;

    carry = sub < 0;
    if (carry) sub += 10;

    if (sub || i != max_size - 1)
      res.num.push_back(sub);
  }

  return res;
}
