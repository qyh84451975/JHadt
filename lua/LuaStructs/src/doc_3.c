#include <stdio.h>

/**
 * printf标准输出
 */
/**
 * sprintf将格式化数据写入某个字符串，并返回该字符串长度。
 */
/**
 * int fprintf(FILE *stream, char *format, [argument]);
 */
/**
 * stdout 标准输出设备，默认是行缓冲，遇到\n会立刻刷新缓冲区
 */
/**
 * stderr 无缓冲，直接输出
 */
/**
 * 满缓冲输出条件：1.缓冲区满；2.刷新缓冲区(fflush)；3.关闭文件
 * 行缓冲输出条件：1.遇到换行符；2.缓冲区满；3.刷新缓冲区；4.关闭文件
 */

#ifdef TEST_3
int main(int argc, char const *argv[])
{

	char str[80];
	int len = sprintf(str, "%s", "hello");
	printf("%d %s\n", len, str);

	FILE * f;
	f = fopen("test.txt", "w");
	if (f != NULL) {
		fprintf(f, "%s\n", str);
	}
	fclose(f);

	return 0;
}
#endif
