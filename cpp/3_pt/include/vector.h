//
//  vector.h
//  qyh
//
//  Created by 钱玉航 on 2019/9/19.
//  Copyright © 2019 钱玉航. All rights reserved.
//vect.h -- Vector class with <<, mode state

#ifndef vector_h
#define vector_h

#include <iostream>

namespace VECTOR {
    class Vector {
    public:
        enum Mode { RECT, POL };
        
    private:
        double x;
        double y;
        double mag;
        double ang;
        Mode mode;
        void set_mag();
        void set_ang();
        void set_x();
        void set_y();
        
    public:
        Vector();
        Vector(double n1, double n2, Mode form = RECT);
        void reset(double n1, double n2, Mode form = RECT);
        ~Vector();
        double xval() const { return x; }
        double yval() const { return y; }
        double magval() const { return mag; }
        double angval() const { return ang; }
        void polar_mode(); // set mode to POL
        void rect_mode();  // set mode to RECT
        Vector operator+(const Vector &b) const;
        Vector operator-(const Vector &b) const;
        Vector operator-() const;
        Vector operator*(double n) const;
        
        friend Vector operator*(double n, const Vector &a);
        friend std::ostream &operator<<(std::ostream &os, const Vector &v);
    };
} // namespace VECTOR

#endif /* vector_h */
