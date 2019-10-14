#include <iostream>

using namespace std;

class SuperVar
{
public:
	SuperVar(char ch);
	SuperVar(int ii);
	SuperVar(float ff);
	void print();

private:
	enum {
		character,
		integer,
		floating_point
	} vartype;
	union {
		char c;
		int i;
		float f;
	};
};

SuperVar::SuperVar(char ch)
{
	vartype = character;
	c = ch;
}

SuperVar::SuperVar(int ii)
{
	vartype = integer;
	i = ii;
}

SuperVar::SuperVar(float ff)
{
	vartype = floating_point;
	f = ff;
}

void SuperVar::print()
{
	switch (vartype) {
		case character:
			cout << "character: " << c << endl;
			break;
		case integer:
			cout << "integer: " << i << endl;
			break;
		case floating_point:
			cout << "floating_point: " << f << endl;
			break;
	}
}

/* 无法确定调用哪个构造，非法的
class Test
{
	Test();
	Test(int a = 0);
};

Test::Test()
{
	cout << "Test1" << endl;
}

Test::Test(int a)
{
	cout << "Test2" << endl;
}
*/

int main(int argc, char const *argv[])
{


	SuperVar A('c'), B(12), C(1.43f);
	A.print();
	B.print();
	C.print();

	return 0;
}
