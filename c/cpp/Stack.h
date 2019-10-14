#ifndef stack_h
#define stack_h

class Stack
{
public:
	Stack();
	void push(void *dat);
	void *peek();
	void *pop();
	~Stack();

private:
	struct Link {
		void *data;
		Link *next;
		Link(void *data, Link *nxt);
		~Link();
	} *head;
};

#endif /* stack_h */