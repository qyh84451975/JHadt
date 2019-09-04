#import <Foundation/Foundation.h>

int main(){

	NSArray *testArray = @[@4, @3, @10, @44, @6, @4, @1, @7];
	for (NSArray *foo in testArray){
		NSLog(@"%@", foo);
		//有个问题，这里怎么对foo进行操作，比如自增自减呢，你会给我答案吗？

	}
	return 0;
}