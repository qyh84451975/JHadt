//
//  time.hpp
//  qyh
//
//  Created by 钱玉航 on 2019/9/19.
//  Copyright © 2019 钱玉航. All rights reserved.
//
//利用友元函数对类的私有数据成员访问，优化重载
#ifndef time_hpp
#define time_hpp

#include <iostream>

class Time {
private:
    int hours;
    int minutes;
    
public:
    Time();
    Time(int h, int m = 0);
    void addMin(int m);
    void addHr(int h);
    void reset(int h = 0, int m = 0);
    Time operator+(const Time &t) const;
    Time operator-(const Time &t) const;
    Time operator*(double n) const;
    friend Time operator*(double m, const Time &t) { return t * m; }
    friend std::ostream &operator<<(std::ostream &os, const Time &t);
};

#endif /* time_hpp */
