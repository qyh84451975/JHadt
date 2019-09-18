//
//  move.cpp
//  qyh
//
//  Created by 钱玉航 on 2019/9/18.
//  Copyright © 2019 钱玉航. All rights reserved.
//

#include "move.hpp"
#include <iostream>
using namespace std;
Move::Move(double a, double b)
{
    x = a;
    y = b;
}
void Move::showmove() const { cout << x << " " << y << endl; }
// Move Move::add(const Move &m) const
//{
//    Move move;
//    move.x = m.x + this->x;
//    move.y = m.y + this->y;
//    return move;
//}
//运算符重载定义
Move Move::operator+(const Move &m) const
{
    Move move;
    move.x = m.x + this->x;
    move.y = m.y + this->y;
    return move;
}
void Move::reset(double a, double b)
{
    x = a;
    y = b;
}
