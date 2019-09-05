/**
 * 这是一个测试循环引用概念的文件
 * oc在xcode4.2引入ARC机制，通过使用__strong修饰对象持有者
 **/

#import <Foundation/Foundation.h>

@interface Test : NSObject
{
	id __strong mobj;
}

-(void) setObject: (id __strong) obj;
@end

@implementation Test

-(void) setObject: (id __strong) obj
{
	mobj = obj;
}

-(id) init
{
	if (self = [super init]) {

	}

	return self;
}

-(void) dealloc
{
	NSLog(@"Test object dealloc!");
	// [super dealloc]; no-arc时添加
}

@end

// 使用弱引用解决循环引用问题
@interface TestX : NSObject
{
	id __weak mobj;
}

-(void) setObject: (id __strong) obj;

@end

@implementation TestX

-(void) setObject: (id __strong) obj
{
	mobj = obj;
}

-(id) init
{
	if (self = [super init]) {

	}
	return self;
}

-(void) dealloc
{
	NSLog(@"TestX object dealloc!");
}
@end

int main(int argc, const char *argv[])
{
	@autoreleasepool {
	// __strong的引入，是为了在持有对象的变量离开作用域的时，能正确的释放所指向的对象

		{///作用域X 开始
			id __strong t1 = [Test new]; // t1变量持有Test对象A
			id __strong t2 = [Test new]; // t2变量持有Test对象B
			[t1 setObject: t2]; // t1的mobj持有Test对象B
			[t2 setObject: t1]; // t2的mobj持有Test对象A

			// 当离开作用域X时
			// t1、t2会销毁，对象A、B仍然分别由t2-mobj、t1-mobj持有，无法调用dealloc
		}///作用域X 结束


		{
			// id __strong t4 = [Test new];
			// [t4 retain]; arc机制下，禁止使用retain/release
			// 回收pool的时候，统一遍历池子中的object检查是否需要回收
			id __strong t5 = [Test new];
			// 作用域结束会执行一次dealloc
		}

		// __weak属性
		// warning: assigning retained object to weak variable; object will be released after assignment
		// 不能将reatined对象赋值给weak的引用，这样会在赋值后，对象直接释放，因为没有强引用持有对象
		// id __weak t6 = [Test new];

		id __strong t7 = [Test new];
		id __weak t8 = t7;

		{
			id __strong t11 = [TestX new];
			id __strong t12 = [TestX new];
			[t11 setObject: t12];
			[t12 setObject: t11];
		}

		// __weak 当指向对象废弃时，__weak引用会置nil
		// __weak只能在iOS5以上和OS X Lion以上版本使用，之前需用__unsafe_unretained修饰，并且__unsafe_unretained修饰不会在对象废弃时置空
		id __weak obj1 = nil;
		{
			id __strong obj2 = [NSObject new];
			obj1 = obj2;
			NSLog(@"离开作用域之前: %@", obj1);
		}
		NSLog(@"离开作用域之后: %@", obj1);


	// 所有引用计数管理内存的模型，都会存在循环引用的情况
	}
}