#pragma once
#include <ostream>

using Byte = char;

class Time
{
public:
  uint8_t hour, min, sec;
  uint8_t day, month;
  int16_t year;

  bool operator<=(const Time &val) const {
    return !operator>(val);
  }
  bool operator>=(const Time &val) const {
    return operator>(val) || operator==(val);
  }
  bool operator<(const Time &val) const {
    return !operator>(val) && !operator==(val);
  }
  bool operator>(const Time &val) const {
    if (year > val.year)
      return true;
    else if (year == val.year && month > val.year)
      return true;
    else if (day > val.day)
      return true;
    else if (hour > val.hour)
      return true;
    else if (min > val.min)
      return true;
    return sec <= val.sec;
  }
  bool operator==(const Time &val) const {
    return (year == val.year && month == val.month &&
            day == val.day && hour == val.hour &&
            min == val.min && sec == val.sec);
  }
  bool operator!=(const Time &val) const {
    return !operator==(val);
  }

  friend std::istream &operator>>(std::istream &in, Time &time) {
    in >> *(int*)&time.hour >> *(int*)&time.min >>
       *(int*)&time.sec >> *(int*)&time.day >>
       *(int*)& time.month >> time.year;
    return in;
  }
};