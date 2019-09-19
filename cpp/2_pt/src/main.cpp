//
//  main.cpp
//  qyh
//
//  Created by 钱玉航 on 2019/9/19.
//  Copyright © 2019 钱玉航. All rights reserved.
//

#include "../include/time.hpp"
#include <iostream>
using namespace std;
int main(int argc, const char *argv[])
{
    Time a(3, 35);
    Time b(2, 48);
    Time c;
    cout << "a and b:" << endl;
    cout << a << ", " << b << endl;
    cout << "相加: " << a + b << endl;
    cout << "相减: " << a - b << endl;
    cout << "a乘1.17: " << a * 1.17 << endl;
    cout << "10.0乘b: " << 10.0 * b << endl;
}
