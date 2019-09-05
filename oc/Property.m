#import <Foundation/Foundation.h>

extern void _objc_autoreleasePoolPrint(void);
extern uintptr_t _objc_rootRetainCount(id obj);

@interface Test : NSObject
@end

@implementation Test
+(id) array
{

	return [[NSMutableArray alloc] init];
	// return [NSMutableArray array];//有问题的返回
}
-(void) dealloc
{
	NSLog(@"dealloc!");
}
@end

int main(int argc, char const *argv[])
{
	// 与下面的t1比较
	id __strong o1 = [Test array];
	NSLog(@"o1 rc = %lu", _objc_rootRetainCount(o1));

	id o2 = [Test new];
	NSLog(@"o2 rc = %lu", _objc_rootRetainCount(o2));

	// 不在autoreleasepool中，无法正确的释放
	// autoreleasepool是针对__autoreleasing修饰符的
	// 对于__weak、__strong都是根据作用域，和持有者判断的
	id __autoreleasing o3 = o2;

	@autoreleasepool {

		id __strong obj = [[NSObject alloc] init];
		NSLog(@"obj rc = %lu", _objc_rootRetainCount(obj));

		id __strong t1 = [Test array];
		NSLog(@"t1 rc = %lu", _objc_rootRetainCount(t1));

		id __strong obj1 = [NSMutableArray array];
		NSLog(@"obj1 rc = %lu", _objc_rootRetainCount(obj1));

		id obj3 = [Test new];
		id __weak obj4 = obj3;
		NSLog(@"obj4 %@", [obj4 class]);
		NSLog(@"%@", obj4);

		_objc_autoreleasePoolPrint();
	}



	return 0;
}