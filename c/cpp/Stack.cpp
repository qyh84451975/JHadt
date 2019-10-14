#include "Stack.h"
#include "require.h"

using namespace std;

Stack::Link::Link(void *dat, Link *nxt)
{
	data = dat;
	next = nxt;
}

Stack::Link::~Link()
{
}

Stack::Stack()
{
	head = 0;
}

void Stack::push(void *dat)
{
	head = new Link(dat, head);
}

void *Stack::peek()
{
	require(head!=0, "Stack empty");
	return head->data;
}

void *Stack::pop()
{
	if (head==0) return 0;
	void *result = head->data;
	Link *oldHead = head;
	head = head->next;
	delete oldHead;
	return result;
}

Stack::~Stack()
{
	require(head==0, "Stack not empty");
}

#include <fstream>
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{

	ifstream in("/Users/kaffee/workspace/github/JHadt/c/cpp/Stack.cpp");
	Stack textlines;
	string line;
	while (getline(in, line))
		textlines.push(new string(line));
	string *s;
	// pop的时候，会删除栈中的节点（被释放）
	// pop出的指针指向读入的字符串（没有被释放）
	while ((s=(string*)textlines.pop()) != 0) {
		cout << *s << endl;
		delete s;
	}

	return 0;
}