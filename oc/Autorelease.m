/**
 * __autorelesae修饰符
 * ARC有效: 无法直接使用autorelease和NSAutoreleasepool，但autorelease有效
 **/

#import <Foundation/Foundation.h>

@interface Test : NSObject
@end

@implementation Test
-(void) dealloc
{
	// arc无效
	// NSLog(@"ARC无效-dealloc");
	// [super dealloc];

	// arc 有效
	NSLog(@"ARC有效-dealloc");
}
@end


// 可通过注释代码块测试以下代码
int main(int argc, const char *argv[])
{

	// ARC无效
	// NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
	// id t = [[Test alloc] init];
	// // 如果不将t加入pool中时，无法在回收内存池的时候废弃对象，造成内存泄露
	// // 注释[t autorelease];则不会调用dealloc
	// [t autorelease];
	// [pool drain];

	// ARC有效
	@autoreleasepool {
		id __autoreleasing obj = [Test new];
		id __strong obj1 = [NSMutableArray array];// 自动将对象注册到autoreleasepool中

		id __autoreleasing obj3 = [Test new]; // 在pool结束之前，obj3指向的对象都不会废弃
		id __weak obj2 = obj3;

		/*
		NSObject **pObj =自动推导=> NSObject * __autoreleasing *pObj;
		NSError *error = nil;
		BOOL result = [obj performOperationWithError: &error];
		// 该方法声明为：
		-(BOOL) performOperationWithError:(NSError **)error;
		// 等同于
		-(BOOL) performOperationWithError:(NSError * __autoreleasing *)error;
		*/

		NSError *error = nil; // 默认都是强引用
		// 等同于 NSError __strong *error = nil;
		// 当赋值常量指针的时候，必须显示的指定所有权，此处应该为统一的__strong
		NSError * __strong *pError = &error;

		NSError __autoreleasing *error1 = nil;
		NSError *__autoreleasing*pError1 = &error1;

		// pointer to non-const type 'NSError *' with no explicit ownership
		// 一个常量指针，必须指定显示的所有权
		// NSError *error2 = nil;
		// NSError **pError2 = &error2;

		NSError __weak *error3 = nil;
		NSError *__weak*pError3 = &error3;
	}

	return 0;
}
