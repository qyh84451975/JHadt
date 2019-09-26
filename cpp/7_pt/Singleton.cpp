// Static member of same type, ensures that
//only one object of this type exists.
//Also referred to as the "singleton" pattern.

#include <iostream>
using namespace std;

class Egg{
    static Egg e;
    int i;
    Egg(int ii):i(ii) {}
    Egg(const Egg&);  //拷贝构造函数也设置为private
public:
    static Egg* instance() {return &e;}
    int val() const {return i;}
};

Egg Egg::e(47);

int main(){
   //! Egg x(1); 错误，构造函数私有。
   //通过下述方法调用唯一的Egg对象，即Egg类的静态成员对象e
   cout<<Egg::instance()->val()<<endl;
}
