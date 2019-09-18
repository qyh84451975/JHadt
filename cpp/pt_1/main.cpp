//
//  main.cpp
//  qyh
//
//  Created by 钱玉航 on 2019/9/18.
//  Copyright © 2019 钱玉航. All rights reserved.
//

#include "move.hpp"
#include <iostream>
using namespace std;
int main(int argc, const char *argv[])
{
    Move m0(12.2, 23.23);
    Move m1(123.234, 231.12);
    Move m2;
    m2.reset();
    m2 = m0 + m1;
    m2.showmove();
    //    m0.showmove();
    //    //m0 = m0.add(m1);
    //    m0.showmove();
    //    m0.reset();
    //    m0.showmove();
    return 0;
}
