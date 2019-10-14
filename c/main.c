#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct T1 {
	int c;
};
struct T
{
	struct T1 *t;
	int a;
	int *b;
};

int main(int argc, char const *argv[])
{

	int n = 0;
	loop: if (getchar() != '\n') {
		n++;
		goto loop;
	}
	printf("%d\n", n);

	// const char *str = "abcde";
	// printf("sizeof = %lu strlen = %lu\n", sizeof(*str), strlen(str));

	// printf("%c\n", 108);
	// for (int i = 0; i < 5; i++) {
		// struct T t;
		// struct T t1;
		// struct T *t2 = (struct T *)malloc(sizeof(struct T));
		// printf("%p %p %p\n", &t, &t1, t2);
		// printf("%d %p\n", t2->a, t2->b);
		// printf("%d\n", (&t)->a);
		// printf("%d\n", t.a);
		// printf("%p\n", t.b);
		// printf("%d\n", (&t)->a);
		// printf("%p\n", (&t)->b);
		// printf("%p\n", t.t);
	// }

	// 弃用
	// char buffer[50];
	// char *ptr;
	// tmpnam(buffer);
	// printf("tmp name1 %s\n", buffer);
	// ptr = tmpnam(NULL);
	// printf("tmp name2 %s\n", ptr);

	// int fd;
	// char template[] = "template-XXXXXX";
	// fd = mkstemp(template);
	// printf("template = %s\n", template);
	// close(fd);

	// fprintf(stderr, "%s\n", "msg", fflush(stderr));
	// const char *str = "abcd3f";
	// fwrite(str, sizeof(char), strlen(str), stdout);
	// fwrite("\n", sizeof(char), 1, stdout);

	// FILE *f = fopen("readme.md", "r");
	// printf("f = %p\n", f);

	return 0;
}