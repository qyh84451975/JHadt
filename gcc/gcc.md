### gcc -E -M main.c
> -E 指示编译程序去激活预处理程序，然后不需要编译或连接就终止
> -M 指示预处理程序输出完整的依赖行
```
gcc -E main.c -o mian.i

```

### gcc main.c -o output_name
> -o 指定编译程序输出的可执行程序名
> -c 会明确指示GCC去编译源代码，但不会在硬盘上留下目标文件，且跳过将目标文件连接到可执行程序这一步。这种情况下默认输出文件名和输入文件名一样，但以.o为后缀。也可以使用-o指定输出名
> -S 指示编译程序生成汇编语言代码，然后停止。
```
gcc -S main.c
```

### gcc -xc main.c -o main
> -x 如果不是.c后缀的文件也可以通过-x为该语言重写默认规则。

## __attribute__
> 可用于为函数或数据声明赋值属性值
> 给函数分配属性主要目的让编译程序可以执行优化处理


## C程序中的文件后缀名
扩展名 | 文件内容
--- | ---
.a | 静态对象库
.c | 需要预处理的C语言源代码
.h | C源源代码的头文件
.i | 无需预处理的C语言源代码。该类文件是编译过程的中间产物
.o | 目标文件，格式和应用的连接相符。该类文件是编译过程的中间产物
.s | 汇编语言代码。该类文件是编译过程的中间产物
.so | 共享对象库

## 静态库
> 是一些.o文件的集合。静态库的另一个名字叫文档(archive)。管理这些文档内容的工具叫ar
```
gcc -c hello1.c hello2.c
ar -r libhello.a hello1.o hello2.o
gcc main_test.c libhello.a -o main_test
# -l 不能指明路径，但可以指示编译程序在系统库中查找
gcc main_test.c -lhello -o main_test(此处无法编译)
```

## 共享库
> -fpic 使得输出的对象模块是按照可重定位地址方式生成。(position independent code <-> 位置独立代码)
```
1.gcc -c -fpic sharehello1.c sharehello2.c
2.gcc -shared sharehello1.o sharehello2.o -o hello.so
1+2=>3
3.gcc -fpic -shared sharehello1.c sharehello2.c -o hello.so

```


