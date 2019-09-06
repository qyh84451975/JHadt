#import <Foundation/Foundation.h>

typedef void (^completeBlock_t)(NSData *data);
typedef void (^errorBlock_t)(NSError *error);

@interface ASyncURLConnection : NSURLConnection
{
	NSMutableData *data_;
	completeBlock_t completeBlock_;
	errorBlock_t errorBlock_;
}

+(id) request: (NSString *) requestUrl
	completeBlock: (completeBlock_t) completeBlock
	errorBlock: (errorBlock_t) errorBlock;

-(id) initWithRequest: (NSString *)requestUrl
	completeBlock: (completeBlock_t) completeBlock
	errorBlock: (errorBlock_t) errorBlock;
@end

@implementation ASyncURLConnection

+(id) request: (NSString *) requestUrl
	completeBlock: (completeBlock_t) completeBlock
	errorBlock: (errorBlock_t) errorBlock
{
	return [[self alloc] initWithRequest:requestUrl completeBlock: completeBlock errorBlock: errorBlock];
}

-(id) initWithRequest: (NSString *) requestUrl
	completeBlock: (completeBlock_t) completeBlock
	errorBlock: (errorBlock_t) errorBlock
{
	NSURL *url = [NSURL URLWithString: requestUrl];
	NSURLRequest *request = [NSURLRequest requestWithURL:url];
	if (self = [super initWithRequest: request delegate: self startImmediately: NO]) {
		data_ = [[NSMutableData alloc] init];
		completeBlock_ = [completeBlock copy];
		errorBlock_ = [errorBlock copy];
		[self start];
	}
	return self;
}

-(void) connection:(NSURLConnection *) connection
	didReceiveResponse: (NSURLResponse *) response
{
	[data_ setLength: 0];
}

-(void) connection: (NSURLConnection *) connection
	didReceiveData: (NSData *) data
{
	[data_ appendData: data];
}

-(void) connectionDidFinishLoading: (NSURLConnection *) connection
{
	completeBlock_(data_);
}

-(void) connection: (NSURLConnection *) connection
	didFailWithError: (NSError *) error
{
	errorBlock_(error);
}


@end

int main(int argc, char const *argv[])
{

	@autoreleasepool {

		// concurrent dispatch queue
		dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
		// 会等待全部处理执行结束
		// @param param1 重复次数
		// @param param2 需要追加的queue
		// @param param3 block
		dispatch_apply(10, queue, ^(size_t index) {
			NSLog(@"%zu", index);
		});
		NSLog(@"done");

		NSArray *arr = @[@11, @22, @33, @44];
		dispatch_async(queue, ^{
			dispatch_apply([arr count], queue, ^(size_t index) {
				NSLog(@"%zu: %@", index, [arr objectAtIndex: index]);
			});
			// 等待apply执行完成，在主线程中打印done
			dispatch_async(dispatch_get_main_queue(), ^{
				NSLog(@"done");
			});
		});

/*
		dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);
		dispatch_time_t time = dispatch_time(DISPATCH_TIME_NOW, 1ull * NSEC_PER_SEC);
		long result = dispatch_semaphore_wait(semaphore, time);
		if (result == 0) {
			NSLog(@"0000");
		} else {
			NSLog(@"1111");
		}
*/

		NSString *url = @"http://imgm.gmw.cn/attachement/jpg/site215/20190906/2433636873080882217.jpg";
		[ASyncURLConnection request:url completeBlock: ^(NSData *data) {
			dispatch_queue_t queue = dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0);
			dispatch_async(queue, ^{
				dispatch_async(dispatch_get_main_queue(), ^{
					NSLog(@"main done");
				});
			});
		} errorBlock: ^(NSError *error) {
			NSLog(@"error %@", error);
		}];
	}


	return 0;
}