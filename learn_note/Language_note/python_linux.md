2014-09-07

##切片

对于想要获取list的内容的不需要使用遍历，直接使用切片操作就可以了。例如用这样一个list `L=range(101)` 如果要取出第30-40之间的数。简单的使用就是
`L[30:40]` 返回的结果就是我们想要的。下面举几个例子：

	L[30:40:2] 30到40之间，每隔两个取出来，结果就是`[30 32 34 36 38]`
	L[-10:] 就是取出最后的十个
	L[:10] 取出最前面额十个
	L[:] 取出所有的value

##迭代
迭代就是所谓的for循环遍历，python中对于list和tuple以及其他的可迭代的数据都可以实施迭代。下面是一些例子,我们对字典`d = {'a': 1, 'b': 2, 'c': 3}`
作为例子来进行：

	for key in d:
		print key

默认情况下，dict迭代的是key。如果要迭代value，可以用`for value in d.itervalues()`，如果要同时迭代key和value，可以用`for k, v in d.iteritems()`

如果我们要判断这个元素是否是可迭代的使用collections模块的Iterable类型判断。 如这样`isinstance('abc', Iterable)`

如果想让list也能够有下标的索引，我们可以使用`for i ,x in enumrate(['a','b','c'])` 这样就能建立一个索引了

同样在直接使用`for x, y in [(1,1),(2,2),(3,3)]` 也可做到一一对应的


##函数参数

1.


##列表生成式

这是一个很cool的操作，体现出python的一个很简洁得一个地方，就是说如果要创建一个列表的话，我们可以有很多的形式创建我们想要的那种形式。如下

1.创建一个乘方的list `[x * x for x in range(1,11)]` 这就创建出一个`[1, 4, 9, 16, 25, 36, 49, 64, 81, 100]`

2.上面的创建其实还可加入一些判断的语句，例如`[x * x for x in range(1,11) if x % 2 == 0]` 这就将得出偶数乘方的结果。

3.我们可以使用列表生成式来实现一个全排列的效果如`[x+y for x in 'abc' for y in 'xyz']` 这将得出九个元素，两两排列的。

4.在引入os这个库的时候，我们遍历出本地文件夹下的所有文件和文件夹。例如`import os   [d for d in os.listdir('.')]` 

5.可以使用列表生成式直接将dict改成键值等于的形式`[key + '=' + value for key value in d.iteritems]`

6.同样可以使用函数放入到列表生成式中，如`[s.lower() for s in l]` 

7.对于list中数据类型杂乱无章的我们上面对于数字的lower就会报错，因此可以使用`isinstrance(x, str)` 看x的类型是不是string，需要添加判断语句进行判断。


##生成器


生成器和列表生成式的差别就在于后者使用的是`[]` 而前者则是使用的`()` 生成器的调用需要使用自带的方法`next()`来打印调用。这只是表面上的一个差别。本质上的差别就是如果对于很多的数据的话使用列表生成式比较显得浪费内存，因为有时候有些数据用不到，而使用生成器就能做到这一点了，要用的时候就能够取出，如何做到这一点的呢？ 就是生成器保存来算法，下次要这个数据的时候，直接算出这个结果就行了。

1.简单的一例，使用的`g=(x * x for x in range(1,11))` 结果就是提示我们这是一个生成器。不是和list一样。我们可以使用for循环来迭代的显示出结果。

2.generator可以实现成一个函数，我们用最经典的fib直接使用函数来实现这个生成器

	 
	#!/usr/python
	#-*- coding: utf-8 -*-


	def fib(Max):
		n, a, b = 0, 0 ,1
		while n < Max:
			yield b
			a, b = b, a+b
			n = n + 1



	print 'This is a fib program, you need to input a number'
	num =int(raw_input("number:"))

	print 'Result:'
	for i in fib(num):
		print i

上面值得注意的就是`yield`这个关键字的存在就有一个表明，就是这个函数就是一个generator了，我们就要for来迭代显示了.还有一个就是`a,b = b, a+b` 这个就是类似于元组的赋值方式，契合了fib的算术规律。


