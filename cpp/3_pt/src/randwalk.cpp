//
//  randwalk.cpp
//  qyh
//
//  Created by 钱玉航 on 2019/9/19.
//  Copyright © 2019 钱玉航. All rights reserved.
//

#include "vector.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;
using VECTOR::Vector;
int main()
{
    srand(time(0));
    double direction;
    Vector step;
    Vector result(0.0, 0.0);
    unsigned long steps = 0;
    double target;
    double dstep;
    cout << "输入目标距离(q to quit): ";
    while (cin >> target) {
        cout << "输入单步步长: ";
        if (!(cin >> dstep))
            break;
        while (result.magval() < target) {
            direction = rand() % 360;
            step.reset(dstep, direction, Vector::POL);
            result = result + step;
            steps++;
        }
        cout << "After " << steps
        << " steps, the subject has the following location: " << endl;
        cout << result << endl;
        result.polar_mode();
        cout << " or\n" << result << endl;
        cout << "Average outward distance per step = "
        << result.magval() / steps << endl;
        steps = 0;
        result.reset(0.0, 0.0);
        cout << "输入目标距离(q to quit): ";
    }
    cout << "再见！" << endl;
    cin.clear();
    while (cin.get() != '\n') {
        continue;
    }
    return 0;
}
