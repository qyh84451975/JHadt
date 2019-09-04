#import <Foundation/Foundation.h>

@interface QuickSort : NSObject
- (NSArray *) quick_sort:(NSArray*) unsortedArray;
@end

@implementation QuickSort
-(NSArray *) quick_sort:(NSArray *)unsortedArray{
	int count = (int)[unsortedArray count];
	if(count<=1){
		return unsortedArray;
	}
	//先找出中心点数据
    int pivot = [[unsortedArray objectAtIndex: (count/2)] intValue];
    NSMutableArray *smallerThanArray = [NSMutableArray array];
    NSMutableArray *largerThanArray = [NSMutableArray array];
    NSMutableArray *pivotArray = [NSMutableArray array];
    //一开始addObject在中间数组插入中心点数据
    [pivotArray addObject: @(pivot)];

    for (int e = 0; e < count; e++) {
    	//遍历原始数组
        int num = [[unsortedArray objectAtIndex:e] intValue];

        if (num < pivot) {
            [smallerThanArray addObject: @(num)];
        } else if (num > pivot) {
            [largerThanArray addObject: @(num)];

        } else if (e != (count/2) && pivot == num) {
            [pivotArray addObject: @(num)];
        }
    }

    NSMutableArray *returnArray = [NSMutableArray array];
    //这里开始把得到的smallerThanArray拿去再进行一遍quick_sort，直到count<=1
    [returnArray addObjectsFromArray: [self quick_sort: smallerThanArray]];
    [returnArray addObjectsFromArray: pivotArray];
    [returnArray addObjectsFromArray: [self quick_sort: largerThanArray]];

    return returnArray;
}
@end

int main(int argc, const char * argv[]) {
    @autoreleasepool {

        NSArray *quickSortData = @[@4, @3, @10, @44, @6, @4, @1, @7];

        QuickSort *qs = [[QuickSort alloc] init];
        NSArray *sortedNumbers = [qs quick_sort:quickSortData];
        NSLog(@"Sorted Numbers %@", sortedNumbers);

    }
    return 0;
}