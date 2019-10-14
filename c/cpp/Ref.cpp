/**
 * 在C中，想要改变指针本身而不是它所指向的内容，函数声明可能为：
 * void f(int**);
 * int i = 47;
 * int *ip = &i;
 * f(&ip);
 */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// 引用了一个int*的指针，所以i++是对指针做加法
void increment(int*& i) {i++;}

class HowMany
{
	static int objectCount;
public:
	HowMany() {objectCount++;}
	static void print(const string &msg = "")
	{
		if (msg.size() != 0) cout << msg << ": ";
		cout << "ObjectCount = " << objectCount << endl;
	}
	~HowMany()
	{
		objectCount--;
		print("~HowMany()");
	}
};

int HowMany::objectCount = 0;
HowMany f(HowMany x)
{
	x.print("x argument inside f()");
	return x;
}


int main()
{
	int *i=0;
	cout << "i = " << i << endl;
	increment(i);
	cout << "i = " << i << endl;

	HowMany h;
	HowMany::print("after consturction of h");
	// h2 是从f的返回值创建的，也就是从一个现有的对象(f返回的对象)创建一个新对象
	// 此时进行了位拷贝，并没有调用HowMany构造函数
	HowMany h2 = f(h);
	HowMany::print("after call to f()");
}