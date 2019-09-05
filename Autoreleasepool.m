/**
 * @autoreleasepool 概念
 **/

#import <Foundation/Foundation.h>

// 定义在m中的非公开函数
extern void _objc_autoreleasePoolPrint(void);
extern uintptr_t _objc_rootRetainCount(id obj);

// 通过修改宏定义测试
#define ARC

#ifdef ARC

/**
 * ARC遵守的规则
 * 1. 不能使用 retain/release/retainCount/autorelease
 * 2. 不能使用 NSAllocateObject/NSDeallocateObject
 * 3. 必须遵守内存管理的方法命名规则(alloc/copy/mutableCopy/new持有对象)
 * 4. 不需要显示的dealloc
 * 5. 使用@autoreleasepool代替NSAutoreleasePool
 * 6. 不能使用区域(NSZone)
 * 7. 对象型变量不能作为C语言结构体(struct/union)的成员
 * 8. 显示转换id和void*
 */

@interface Test : NSObject
@end

@implementation Test

-(void) dealloc
{
	NSLog(@"Test dealloc");
}

@end


int main(int argc, const char *argv[])
{
	@autoreleasepool {
		@autoreleasepool {

			id t2 = nil;
			id t3 = nil;
			id t1 = [Test new]; // t1持有对象
			NSLog(@"t1 curr rc: %lu", _objc_rootRetainCount(t1));
			t2 = t1; // t2、t1都持有对象
			t3 = t2; // t3、t2、t1都持有对象
			NSLog(@"t2 curr rc: %lu", _objc_rootRetainCount(t2));
			t2 = nil;
			t3 = nil;
			NSLog(@"t1 curr rc: %lu", _objc_rootRetainCount(t1));

			_objc_autoreleasePoolPrint();
		}
	}
}


#else

@interface Test : NSObject
@end

@implementation Test

-(void) dealloc
{
	NSLog(@"Test dealloc");
	[super dealloc];
}

@end

// ARC无效也可以使用@autoreleasepool
int main(int argc, const char *argv[])
{
	NSAutoreleasePool *pool1 = [[NSAutoreleasePool alloc] init];

		NSAutoreleasePool *pool2 = [[NSAutoreleasePool alloc] init];

			NSAutoreleasePool *pool3 = [[NSAutoreleasePool alloc] init];

				id obj = [[NSObject alloc] init];
				[obj autorelease];
				id obj1 = [[NSObject alloc] init];
				[obj1 autorelease];
				NSLog(@"obj1 ref count: %lu", _objc_rootRetainCount(obj1));

				// id t1 = [Test new];
				// [t1 autorelease]; // 当清理pool的时候，会自动释放。如果不添加，则不回释放
				// id t2 = nil;
				// id t3 = nil;
				// t2 = t1;
				// t3 = t1;
				// NSLog(@"t1 ref count: %lu", _objc_rootRetainCount(t1));

				id t5 = [Test new];
				NSLog(@"t5 ref count: %lu", _objc_rootRetainCount(t5));
				id t6 = nil;
				[t5 retain];
				NSLog(@"t5 ref count: %lu", _objc_rootRetainCount(t5));
				t6 = t5;
				NSLog(@"t6 ref count: %lu", _objc_rootRetainCount(t6));
				[t6 release];
				NSLog(@"t6 ref count: %lu", _objc_rootRetainCount(t6));
				[t5 release];

				_objc_autoreleasePoolPrint();

			[pool3 drain];

		[pool2 drain];

	[pool1 drain];
}

#endif

