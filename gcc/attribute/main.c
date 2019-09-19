// noreturn属性告诉编译程序该函数不会返回到调用者，这样优化器就会忽略在函数返回时通常会执行的所有代码。
void fatal_error() __attribute__ ((noreturn));

void fatal_error(char *msg)
{
	fprintf(stderr, "FATAL ERROR: %s\n", msg);
	exit(1);
}