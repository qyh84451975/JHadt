/**
 * id类型和void*类型的转换问题
 **/

#import <Foundation/Foundation.h>

extern void _objc_autoreleasePoolPrint(void);
extern uintptr_t _objc_rootRetainCount(id obj);

// 通过修改宏定义测试
#define ARC

#ifdef ARC

@interface Test : NSObject
@end

@implementation Test

-(void) dealloc
{
	NSLog(@"Test dealloc rc = %lu", _objc_rootRetainCount(self));
}
@end

int main(int argc, char const *argv[])
{

	@autoreleasepool {
		id obj = [Test new];
		NSLog(@"obj rc = %lu", _objc_rootRetainCount(obj));
		void *p = (__bridge void *)obj;
		id o = (__bridge id)p;
		NSLog(@"obj rc = %lu", _objc_rootRetainCount(obj));

		// retain之后，在清理pool的时候无法释放
		void *p1 = (__bridge_retained void *)obj;
		NSLog(@"obj rc = %lu", _objc_rootRetainCount(obj));
		id o2 = (__bridge id)p1;
		NSLog(@"obj rc = %lu", _objc_rootRetainCount(obj));

		// 将void*转为id，并且释放p1的持有
		id o3 = (__bridge_transfer id)p1;

		// 此处转换并释放了一个没有retian的对象，则程序崩溃
		// id o4 = (__bridge_transfer id)p;

		CFMutableArrayRef cfObject = NULL;
		{
			id obj = [[NSMutableArray alloc] init];
			cfObject = (CFMutableArrayRef)CFBridgingRetain(obj);
			CFShow(cfObject);
			printf("retain count = %ld\n", CFGetRetainCount(cfObject));
		}
		printf("retain count after the scope = %ld\n", CFGetRetainCount(cfObject));
		CFRelease(cfObject);
	}

	return 0;
}

#else

@interface Test : NSObject
@end

@implementation Test

-(void) dealloc
{
	NSLog(@"Test dealloc rc = %lu", _objc_rootRetainCount(self));
	[super dealloc];
}

@end

int main(int argc, char const *argv[])
{

	NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	// 可以随意转换
	id obj = [Test new];
	void *p = obj;
	id o = p;
	[o release];

	[pool drain];

	return 0;
}

#endif