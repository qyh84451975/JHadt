#import <Foundation/Foundation.h>

typedef struct {
	float x;
	float y;
} CPoint;
@interface Body : NSObject
-(void) fun:(CPoint *) p;
@end
@implementation Body
-(void) fun:(CPoint *) p {
	NSLog(@"结构体数据是 %f %f", p->x, p->y);
}
@end
int main(int argc, const char * argv[]) {
	CPoint p;
	p.x = 20.1;
	p.y = 32.4;
	Body * body = [[Body alloc] init];
	[body fun:&p];
	return 0;
}