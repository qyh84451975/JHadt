#import <Foundation/Foundation.h>

NSArray *map(NSArray *items, id(^block)(id item))
{
	NSMutableArray *result = [NSMutableArray array];
	for (id item in items)
	{
		[result addObject: block(item)];
	}
	return result;
}

int main() {

	NSArray *testArray = @[@4, @3, @10, @44, @6, @4, @1, @7];
	NSArray *array = [NSArray arrayWithObjects:
	                  @"Amir", @"Mishal", @"Irrum", @"Adam", nil];
	// for ( NSString *foo in testArray){
	// 	//以下都不行，什么玩意
	// 	// int v = [foo intValue];
	// 	// NSLog(@"%i", v);
	// 	// foo = [NSString stringWithFormat: @"%d", v++];
	// 	//有个问题，这里怎么对foo进行操作，比如自增自减呢，你会给我答案吗？
	// 	//我不会告诉你，因为我也不会。。难受
	// }
	// 以下是可行的，平了个方
	///////////////////////////////
	NSArray *mappedResults = map(testArray, ^id(id item) {
       return @(pow([item intValue],3));
    });
    NSLog(@"%@", mappedResults);
	///////////////////////////////
	for (NSString * foo in testArray) {
		int m = [foo intValue];
		NSLog(@"%d", ++m);
	}


	return 0;
}