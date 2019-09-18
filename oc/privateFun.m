#import <Foundation/Foundation.h>

@interface Foo : NSObject
{

}

@end

@implementation Foo
//仅仅在实现文件中使用而不想对外公开的方法应该放在调用该方法的方法之前(放在后面会给出警告)
-(void)somePrivateMethod
{
	NSLog(@"somePrivateMethodNice");
}

-(void)someOtherMethod
{
	[self somePrivateMethod];
}

@end

int main(int argc, const char * argv[]){
	@autoreleasepool{
		Foo * foo = [[Foo alloc]init];
		[foo someOtherMethod];
	}
	return 0;
}