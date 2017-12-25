---
layout: post
title: The C implementation of the python keyword yield
tags: python yield C
key: 20171224
category: blog
date: 2017-12-24 20:30:00 +08:00
---

## 起因
之前在看丹大师（Dannis M.Ritchie）的《The C Programing Language》的时候，在第8章第6节有一个程序示例——Listing Directories。
其中有一个函数readdir的实现让我忽然想起了python中的yield关键字。

## yield
yield是python的关键字。用于构造生成器。
以下是生成器的一个简单的例子

{% highlight python %}
doubles = [2 * n for n in range(50)]
{% endhighlight %}

这是一个使用yield的例子

{% highlight python %}
# a generator that yields items instead of returning a list
def firstn(n):
    num = 0
    while num < n:
        yield num
        num += 1

sum_of_first_n = sum(firstn(1000000))
{% endhighlight %}

生成器，每次调用时，才计算新的结果，内存中只保留最新的结果，不必生成列表占用大量内存。
节省内存，缺点是只能遍历一次。我没有看过python中generator的实现，但是看到readdir函数时，我忽然觉得这就是yield的C实现。

## readdir
这是The C Programing Language书中的一个程序示例Listing Directories。
{% highlight C %}
/* readdir: read directory entries in sequence */
Dirent *readdir(DIR *dp)
{
    struct direct dirbuf; /* local directory structure */
    static Dirent d; /* return: portable structure */
    while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf))
            == sizeof(dirbuf)) {
        if (dirbuf.d_ino == 0) /* slot not in use */
            continue;
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0'; /* ensure termination */
        return &d;                 //return一个"局部变量"，让我很震惊
    }
    return NULL;
}
{% endhighlight %}

我们知道不能return一个局部变量，因为局部变量保存在栈上，函数退出后栈上的变量就销毁了，引用失效。
但是这里可以return &d，是因为d是static静态变量，并没有保存在栈上，而在.bss段。

我模仿readdir写了yield
{% highlight C %}
// yield.c
#include <stdio.h>

int * yield()
{
    static int d;                  // return 的值 不能是临时变量 故为static
    static int num = 5; 
    // int num = 5;
    while (num-- > 0){             // num-- 使得每次num的值发生变化 不会死循环
        // printf("num now is %d\n",num);
        d = num;
        return &d;
    }
    return NULL;                   // 结束时返回NULL,作为判断结束的标志
}


int main(void)
{
    int *d;
    while((d = yield()) != NULL)
         printf("d is %d\n",*d);

    return 0;
}
{% endhighlight %}
我认为应该注意的点已经在注释中标出。
这个yield程序具备了python中生成器的一些特性，比如可以多次调用，返回迭代后的值。但是还不能传参，所以有了下面的yield2

{% highlight C %}
#include <stdio.h>

int *yield2(int * num)
{
    static int d;
    // static int num = 5;                 // num作为参数传递过来
    // int num = 5;
    while ((*num)-- > 0){
        // printf("num now is %d\n",*num);
        d = *num; 
        return &d;
    }
    return NULL;
}


int main(void)
{
    int *d;
    int num = 5; 
    while((d = yield2(&num)) != NULL)
         printf("d is %d\n",*d);
    
    return 0;
}

{% endhighlight %}

前面python例子的firstn实现如下：

{% highlight C %}
#include <stdio.h>

#define NULL -1                         // NULL 就是 ((void *)0) 而第一次返回num刚好是0，所以这里把NULL重新define一下

int firstn(int *n)
{
    static int num = 0;
    while(num < *n){
        return num++;
    }
    return NULL;
}

int main()
{
    int n = 100;
    int res;
    int sum = 0;
    while((res = firstn(&n))!=NULL)
        sum += res;
    printf("sum is %d\n",sum);
    return 0;
}

{% endhighlight %}

这里只是从原理上说了一下我认为的生成器的C实现原理，全部的yield的功能肯定不是这么简单，具体还请看python源码。

## 想法

在调试The C programming language中的Listing Directories时遇到了一些问题，编译没问题，输出却不是预计的输出。

{% highlight console %}
$./fsize /home
4096 /home
$./fsize
4096 .
{% endhighlight %}
每次结果只有一项，
使用strace跟踪发现read返回-EISDIR错误。

{% highlight console %}
$ strace ./fsize  /home
...
munmap(0x7fb9257a9000, 100628)          = 0
stat("/home", {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
open("/home", O_RDONLY)                 = 3
fstat(3, {st_mode=S_IFDIR|0755, st_size=4096, ...}) = 0
brk(NULL)                               = 0x17ad000
brk(0x17ce000)                          = 0x17ce000
read(3, 0x7ffc33f43680, 280)            = -1 EISDIR (Is a directory)             # read返回出错了
close(3)                                = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 4), ...}) = 0
write(1, "    4096 /home\n", 15    4096 /home
)        = 15
exit_group(0)                           = ?
+++ exited with 0 +++
{% endhighlight %}

猜想新的内核版本应该是对read做了限制，只能通过readdir来读取目录的inode。
这里附上源程序，望指教。
[main.c](https://github.com/j4ckstraw/blog/tree/master/_data/20171224/main.c)
[fsize.c](https://github.com/j4ckstraw/blog/tree/master/_data/20171224/fsize.c)
[dirent.h](https://github.com/j4ckstraw/blog/tree/master/_data/20171224/dirent.h)


在写firstn的C实现时，我也写了引用传递的版本，编译发现代码竟然惊人的相似，看汇编深究了一下C预言的参数传递，我认为C语言中参数的传递只有值传递一种。指针传递和引用传递都是编译器玩的花样。

TLDR

{% highlight C %}
#include <stdio.h>

#define NULL -1

int firstn(int &n)
{
    static int num = 0;
    while(num < n){                                //可以直接使用n而不必使用*了
        return num++;
    }
    return NULL;
}

int main()
{
    int n = 100;
    int res;
    int sum = 0;
    while((res = firstn(n))!=NULL)                 //引用传值不需要&取址了
        sum += res;
    printf("sum is %d\n",sum);
    return 0;
}

{% endhighlight %}


写blog真的很不错，为了解释说明一个问题，要查阅很多资料，blog上的程序要一个一个的测试，遇到问题，就解决问题，学到了不少东西。

Thank you, my blog.

Post on single dog's Christmas Eve 

## 参考
[Python Generator](https://wiki.python.org/moin/Generators)

[The Python yield keyword explained](https://pythontips.com/2013/09/29/the-python-yield-keyword-explained/)

[Understanding Python's "for" statement](http://effbot.org/zone/python-for-statement.htm)

Kernighan, B. and Ritchie, D. The C programming language.
