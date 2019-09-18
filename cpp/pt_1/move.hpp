//
//  move.hpp
//  qyh
//
//  Created by 钱玉航 on 2019/9/18.
//  Copyright © 2019 钱玉航. All rights reserved.
//

#ifndef move_hpp
#define move_hpp

#include <stdio.h>

class Move {
private:
    double x;
    double y;
    
public:
    Move(double a = 0, double b = 0);
    void showmove() const;
    // Move add(const Move &m) const;
    //运算符重载
    Move operator+(const Move &m) const;
    void reset(double a = 0, double b = 0);
};

#endif /* move_hpp */
