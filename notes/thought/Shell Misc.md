# shell基础

# 基础

## 容易忽略的地方

一切皆表达式。

list 就是若干个使用管道，；，&，&&，||这些符号串联起来的 shell 命令序列，结尾可以；，&或换行结束。

当多个命令用管道串联起来的时候，shell会将整个list看作一个执行体，这个list的返回值是**整个list中最后一个命令的返回值**。

在 bash 中，使用`$[]`以得到一个算数运算（只支持整数）的值。则并不是一个shell命令，而是特殊字符。

`if`中的方括号`[]`，也是命令，等同于test命令。写的时候是需要空格的，即`if [ list ]`。

## sh和bash

sh并不是bash。bash本身是兼容sh的，但bash本身的某些特性在sh上会有不可预期的行为。

## Shebang

即文件开头的`#!/bin/bash`，作用是告诉shell使用哪个解释器来运行脚本。

为了可移植性，写为`#!/usr/bin/env bash`，因为不同发行版的bash可能会在不同的位置，最好是写作这样的形式。

## 通配符

bash 的通配符和正则表达式完全没有关系。

`*`是匹配任何字符串，`?`是匹配所有单个字符。

## I/O重定向

有3个默认文件：

* stdin，键盘
* stdout，屏幕
* stderr，输出到屏幕的错误信息

他们的文件描述符分别为0，1，2。对于额外打开的文件，剩下的描述符为3到9。

输出时，
* `>`，重定向到文件，如果文件不存在则创建，否则覆盖。
* `>>`，重定向到文件，如果文件不存在则创建，否则追加到文件末尾。

# 变量

定义以及使用，

```bash
v = "hello"
echo $v
```

## 单引号和双引号

双引号中，变量会扩展为它本身值，而在单引号中不会。

```bash
v = "hello"

# 以下三种方式都等价
echo '$v='"$v"
echo '$v='$v
echo "\$v=$v"
```

## 用括号保护变量名

```bash
v = "hello"

echo $vworld # no output
echo ${v}world
```

`$v`其实是`${v}`的简写形式。

# if

`if`后面是一个命令(严格来说是list)。

```bash
if list; then list; elif list; then list; ... else list; fi
# 也等价于
if list
then
	list
elif list
then
	list
...
else
	list
fi
```

而`if`中的方括号`[]`，也是命令，等同于`test`命令。写的时候是需要空格的，即`if [ list ]`。

```bash
# 下面两种形式等价
if [ operand1 ]
if test operand1
```

`[[]]`是对`[]`的扩展，[可见参考](http://stackoverflow.com/questions/669452/is-preferable-over-in-bash-scripts)。

由于`if`后跟list，然后判断这个list的返回值，因此`if`后面不必拘泥于`[]`。

```bash
DIR="/etc"
ls -l $DIR &> /dev/null
ret=$?

if [ $ret -eq 0 ]
...

# best practice
if ls -l $DIR &> /dev/null
...
```

# test操作符

# while do和until

```bash
while list-1; do list-2; done
until list-1; do list-2; done
# 也等价于
while list-1
do
	list-2
done

until list-1
do
	list-2
done
```

# case和for

```bash
case word in [ [(] pattern [ | pattern ] ... ) list ;; ] ... esac
# 也等价于
case $1 in
        pattern)
        list
        ;;
        pattern)
        list
        ;;
        pattern)
        list
        ;;
esac

for name [ [ in [ word ... ] ] ; ] do list ; done
```

# select和for

```bash
select name [ in word ] ; do list ; done
for (( expr1 ; expr2 ; expr3 )) ; do list ; done
```

# references

1. [SHELL 编程之语法基础](http://www.v2ex.com/t/278920)