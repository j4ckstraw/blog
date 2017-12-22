---
layout: post
title: advanced bash learning record
tags: bash tips
key: 20171222
category: record
date: 2017-12-22 14:30:00 +08:00
---

本blog是我的学习记录，只是记录我不熟悉的命令。完整介绍请查看文末链接。

## 特殊字符
### . 

"点"命令[句点, 即.]. 等价于source命令. 这是一个bash的内建命令(builtin).

{% highlight console %}
$type .
. is a shell builtin
{% endhighlight %}

### \`
命令替换. \`command\`结构可以将命令的输出赋值到一个变量中去. 

{% highlight console %}
$d=`date`
$echo $d
2017年 12月 22日 星期五 14:36:45 CST
{% endhighlight %}

### :
空命令[冒号, 即:]. 等价于"NOP" ,主要做占位符用. 也可以被认为与shell的内建命令true作用相同. ":"命令是一个bash的内建命令, 它的退出码(exit status)是"true"(0).

做循环中的占位符
{% highlight console %}
while :
do 
    ...
done
{% endhighlight %}

在一个二元命令中提供一个占位符
{% highlight console %}
$ : ${username=`whoami`}
$ ${username=`whoami`} 			# 如果没有开头的":"的话, 将会给出一个错误
j4ckstraw: command not found
$ echo $username 				# bash会将`whoami`的结果当作命令执行
j4ckstraw
{% endhighlight %}

也可能用来作为注释行, 虽然不推荐这么做. 使用#来注释的话, 将关闭剩余行的错误检查, 所以可以在注释行中写任何东西. 然而, 使用:的话将不会这样.

{% highlight console %}
: This is a comment that generates an error, ( if [ $x -eq 3] ).
{% endhighlight %}

在与>重定向操作符结合使用时, 将会把一个文件清空, 但是并不会修改这个文件的权限. 如果之前这个文件并不存在, 那么就创建这个文件.

{% highlight console %}
$ : > data.xxx   # 文件"data.xxx"现在被清空了.  与 cat /dev/null >data.xxx 的作用相同 然而,这并不会产生一个新的进程, 因为":"是一个内建命令. 
{% endhighlight %}

从来不知道‘:’有这么多用途 :) 还可以做表情。

### $
变量替换
这个不用多说
{% highlight console %}
$ name=Tom
$ echo Hello $name !
{% endhighlight %}

### ${}
参数替换
{% highlight text%}
${parameter}
${parameter-default}, ${parameter:-default}
${parameter-default} -- 如果变量parameter没被声明, 那么就使用默认值
${parameter:-default} -- 如果变量parameter没被设置, 那么就使用默认值.

${parameter=default}, ${parameter:=default}
${parameter=default} -- 如果变量parameter没声明, 那么就把它的值设为default.
${parameter:=default} -- 如果变量parameter没设置, 那么就把它的值设为default.

${parameter+alt_value}, ${parameter:+alt_value}
${parameter+alt_value} -- 如果变量parameter被声明了, 那么就使用alt_value, 否则就使用null字符串.
${parameter:+alt_value} -- 如果变量parameter被设置了, 那么就使用alt_value, 否则就使用null字符串.

${parameter?err_msg}, ${parameter:?err_msg}
${parameter?err_msg} -- 如果parameter已经被声明, 那么就使用设置的值, 否则打印err_msg错误消息.
${parameter:?err_msg} -- 如果parameter已经被设置, 那么就使用设置的值, 否则打印err_msg错误消息.
{% endhighlight %}

这里有点乱，使用的时候可以来查。

### $$
进程ID变量. 这个$$ 变量 保存了它所在脚本的进程 ID

### ()
命令组
{% highlight console %}
$ (a=hello; echo $a)
hello
{% endhighlight %}

在括号中的命令列表, 将会作为一个子shell来运行.
在括号中的变量,由于是在子shell中,所以对于脚本剩下的部分是不可用的. 父进程, 也就是脚本本身, 将不能够读取在子进程中创建的变量, 也就是在子shell中创建的变量.
{% highlight console %}
$ a=123
$ ( a=321; )	      
$ echo "a = $a"
a = 123
{% endhighlight %}

初始化数组
{% highlight console %}
Array=(element1 element2 element3)
{% endhighlight %}


除了 命令替换\` 变量替换$ 参数替换${} 还有 进程替换 () 
{% highlight console %}
$ cat <(whoami) 		# whoami命令作为cat的输入
{% endhighlight %}

### >|
强制重定向(即使设置了noclobber选项 -- 就是-C选项). 这将强制的覆盖一个现存文件.
这个还真没用过 :)

### -
先前的工作目录. cd -将会回到先前的工作目录. 它使用了$OLDPWD 环境变量.
很方便实用 :)

### ~
home目录[波浪号, 即~]. 相当于$HOME内部变量. ~bozo是bozo的home目录, 并且ls ~bozo将列出其中的内容. ~/就是当前用户的home目录, 并且ls ~/将列出其中的内容.

## 控制字符
### Ctrl-D
从一个shell中登出(与exit很相像).
"EOF"(文件结束). 这也能从stdin中终止输入.
在console或者在xterm窗口中输入的时候, Ctl-D将删除光标下字符. 当没有字符时, Ctl-D将退出当前会话, 在一个xterm窗口中, 则会产生关闭此窗口的效果.

再也不输入exit或者logout退出shell了

### Ctrl-L
清屏(清除终端的屏幕显示). 在终端中, 与clear命令的效果相同. 当发送到打印机上时, Ctl-L会让打印机将打印纸卷到最后.

你还在输入clear清屏吗？

### Ctrl-S
挂起(XOFF).
在一个终端中冻结stdin. (使用Ctl-Q可以恢复输入.)

还记得shell突然死了的情况吗，输入什么都没反应，也许是你不小心按了Ctrl-S

### Ctrl-Q
恢复(XON).
在一个终端中恢复stdin.

哈哈 这个可以恢复，不用关闭shell再开的。

还有很多控制字符，感觉记不过来，用的也不多，就没有在这里列出来。

## 参考
[高级Bash脚本编程指南](http://www.linuxplus.org/kb/)

<!--more-->