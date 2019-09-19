//
//  time.cpp
//  qyh
//
//  Created by 钱玉航 on 2019/9/19.
//  Copyright © 2019 钱玉航. All rights reserved.
//

#include "../include/time.hpp"
Time::Time() { hours = minutes = 0; }
Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

void Time::addMin(int m)
{
    minutes += m;
    hours += minutes / 60;
    minutes %= 60;
}

void Time::addHr(int h) { hours += h; }

void Time::reset(int h, int m)
{
    hours = h;
    minutes = m;
}

Time Time::operator+(const Time &t) const
{
    Time sum;
    sum.minutes = minutes + t.minutes;
    sum.hours = hours + t.hours + sum.minutes / 60;
    sum.minutes %= 60;
    return sum;
}

Time Time::operator-(const Time &t) const
{
    Time diff;
    int tot1, tot2;
    tot1 = t.minutes + 60 * t.hours;
    tot2 = minutes + 60 * hours;
    diff.minutes = (tot2 - tot1) % 60;
    diff.hours = (tot2 - tot1) / 60;
    return diff;
}

Time Time::operator*(double mult) const
{
    Time result;
    long totalminutes = hours * mult * 60 + minutes * mult;
    result.hours = (int)totalminutes / 60;
    result.minutes = totalminutes % 60;
    return result;
}

std::ostream &operator<<(std::ostream &os, const Time &t)
{
    os << t.hours << "小时, " << t.minutes << " 分钟";
    return os;
}
