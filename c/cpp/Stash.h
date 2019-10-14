#ifndef stash_h
#define stash_h

class Stash
{
public:
	Stash(int sz);
	~Stash();
	int add(const void *element);
	void *fetch(int index);
	int count();

private:
	int size;
	int quantity;
	int next;
	unsigned char *storage;
	void inflate(int increase);
};

#endif /* stash_h */