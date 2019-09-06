#import <Foundation/Foundation.h>

/*
// id 类型能够在C语言中声明

struct objc_class {
	Class isa;
};

typedef struct objc_class *Class;

typedef struct objc_object  {
	Class isa;
} *id;

struct class_t {
	struct class_t *isa;
	struct class_t *superclass;
	Cache cache;
	IMP *vtable;
	uintptr_t data_NEVER_USE;
};

struct __block_impl {
	void *isa;
	int Flags;
	int Reserved;
	void *FuncPtr;
};

static struct __main_block_desc_0 {
	size_t reserved;
	size_t Block_size;
} __main_block_desc_0_DATA = {0, sizeof(struct __main_block_impl_0)};

struct __main_block_impl_0 {
	struct __block_impl impl;
	struct __main_block_desc_0 *Desc;
	__main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, int flags=0) {
		impl.isa = &_NSConcreteStackBlock;
		impl.Flags = flags;
		impl.FuncPtr = fp;
		Desc = desc;
	}
};
//__main_block_impl_0==>展开
// struct __main_block_impl_0 {
// 	void *isa;
// 	int Flags;
// 	int Reserved;
// 	void *FuncPtr;
// 	struct __main_block_desc_0 *Desc;
// }

static void __main_block_func_0(struct __main_block_impl_0 *__cself) {
	printf("Hello Block\n");
}

int main(int argc, char const *argv[])
{
	void (*blk) (void) = ((void (*)())&__main_block_impl_0((void *)__main_block_func_0, &__main_block_desc_0_DATA));
	// 1.在栈上生成结构体
	struct __main_block_impl_0 tmp = __main_block_impl_0(__main_block_func_0, &__main_block_desc_0_DATA);
	// 2.将结构体指针赋值给blk
	struct __main_block_impl_0 *blk = &tmp;
	((void (*)(__block_impl *))((__block_impl *)blk)->FuncPtr)((__block_impl *)blk);
	// (*blk->impl.FuncPtr)(blk);
}
*/

typedef void (^blk_t)(void);
@interface Test : NSObject
{
	blk_t blk_;
}
@end

@implementation Test

-(id) init
{
	if (self = [super init]) {
		// 通过Block语法生成的Block会从栈复制到堆上
		// Block持有self，self持有Block
		// blk_ = ^{NSLog(@"self = %@", self);};
		id __weak tmp = self;
		blk_ = ^{NSLog(@"self = %@", tmp);};
	}

	return self;
}

-(void) dealloc
{
	NSLog(@"dealloc");
}

@end

int main(int argc, char const *argv[])
{
	// void (^blk) (void) = ^{printf("Hello Block\n");};
	// blk();

	id o = [[Test alloc] init];
	NSLog(@"%@", o);

	return 0;
}