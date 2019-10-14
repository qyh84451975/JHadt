#include "Stash.h"
#include "require.h"

#include <iostream>
#include <cassert>

using namespace std;

const int increment = 100;

Stash::Stash(int sz)
{
	size = sz;
	quantity = 0;
	storage = 0;
	next = 0;
}

int Stash::add(const void *element)
{
	if (next >= quantity)
		inflate(increment);
	int startBytes = next * size;
	unsigned char *e = (unsigned char *)element;
	for (int i = 0; i < size; i++)
		storage[startBytes+i] = e[i];
	next++;
	return (next - 1);
}

void *Stash::fetch(int index)
{
	assert(0 <= index);
	if (index >= next)
		return 0;
	return &(storage[index * size]);
}

int Stash::count()
{
	return next;
}

void Stash::inflate(int increase)
{
	assert(increase > 0);
	int newQuantity = quantity + increase;
	int newBytes = newQuantity * size;
	int oldBytes = quantity * size;
	unsigned char *b = new unsigned char[newBytes];
	for (int i = 0; i < oldBytes; i++)
		b[i] = storage[i];
	delete []storage;
	storage = b;
	quantity = newQuantity;
}

Stash::~Stash()
{
	if (storage != 0) {
		cout << "freeing storage" << endl;
		delete []storage;
	}
}


#include <fstream>
#include <string>
int main(int argc, char const *argv[])
{

	Stash intStash(sizeof(int));
	for (int i = 0; i < 100; i++)
		intStash.add(&i);
	for (int j = 0; j < intStash.count(); j++)
		cout << "intStash.fetch(" << j << ") = "
			 << *(int *)intStash.fetch(j) << endl;

	const int bufsize = 80;
	Stash stringStash(sizeof(char) * bufsize);
	ifstream in("/Users/kaffee/workspace/github/JHadt/c/cpp/Stash.cpp");
	string line;
	while (getline(in, line))
		stringStash.add(line.c_str());
	int k = 0;
	char *cp;
	while ((cp = (char*)stringStash.fetch(k++)) != '\0')
		cout << "stringStash.fetch(" << k << ") = " << cp << endl;

	return 0;
}
