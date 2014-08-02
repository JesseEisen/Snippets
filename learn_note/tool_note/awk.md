awk
===

###base 

awk -F(separator) '/pattern/ {action}' inputfile

awk的标准形式包含三个块，BEGIN body END.这三个部分至少有一个。
* BEGIN 在这一块我们可以做一些初始的工作，或是制作header。在这一块会用到很多的buildin variable.
* body 在这一块我们用的比较多的是模式匹配，然后做一些处理，print等等
* END 在这一块我们做一些处理工作。或者制作footer

首先得明白两个概念
> record 这是指的我们的文本一行或是几行，符合一定的规则的。每个记录之间的形式基本一样。

> field 这是包含在record中的，一条记录有好几个field。我们经常操作的是field。

基础的一些命令 -F 指定了separator。形式可以是是-F; -F";" 我们有时候在BEGIN中使用FS这个变量来指定分隔符。如果一个文件中使用了多中符号如@:,等，我们就需要使用FS=[@:,] 这样这三种分隔符就相当是一个了。

####内置变量

* FS   指的读取的文件的分割符，
* OFS  指输出文本的分割符，
* RS   指的是每个record之间的分隔符。常见的是\n,要视具体的情况而言
* ORS  这个很明了了，就是输出时的record的分隔符。
* NF   这是field的总量，$NF的意思是最后一个field。
* NR   这是record的总量，但是这个也可以说是record的号，可以作为行号来用
* FILENAME  输出的是当前文件的名字
* FNR  如果单纯的使用NR 再多文件的时候就不会分清具体哪个文件，而会一直统计下去的。使用FNR就能分清具体的文件。统计的是具体的哪一文件的行数或是record数

awk的数学计算和C语言的基本上一样的，所不一样的是在awk的一个特色就是匹配上，我们一般是使用$1=="xxx".这样使用的话，awk做的是一个完全匹配，就是等于后面的那块必须在文件中field1的一模一样，但有时我们不需要这样，想匹配到一部分就算是成功匹配到了。

所以我们使用～来标志模式匹配开始，这样就能解决部分的问题。 !~表示不匹配后面。

awk中的branch以及loop和C语言中的使用基本一样，但是awk没有switch。还有就是for的用法有两种，一是和c一样，另一个是
`for(a in array)` 这是awk与c中不同的部分

####数组
数组是一个比较不错的内容在awk中，但是awk中的数组是associative。所以支持使用字符串作index。需要说明的是数组的下标不需要是连续的，不连续一样可以的。

比较有意思的是如果我们有这样一个`x = item[55]` item[55]并没有被赋值，那么就直接将55这个下标作为item[55]的值，如果就这么直接的使用item[101]那么这个就不会执行上述的操作。

遍历数组可以使用for的两种形式，使用类似C的那种的话会顺序输出。

删除数组使用delete arrayname[index] ,通样只有数组名，那就是删除了数组

到了多维数组了，item["1,1"] 表示第一行第一列。如果不加“”（quotes）就item[1,1]那么将被扩展为item[1#1] \034插入到中间去。我们一般是SUBSEP来指定分割符，然后都不加quotes


####一些内置函数
asort 将对数组排序，单纯的使用asort(arrayname) 就将会将数组的内容给更改了。所以一般是使用asort(oldarray,newarray) 这样保留原来的数组的内容，新的序列保留在newarray中。

对于asort我们的index已经变得是随机的了，所以使用for(xx;xx;xx)这样的形式进行输出就会是原来的数据。

asorti 这是对index进行排序，排序的结果是index作为内容写入了数组中。同样保险起见我们使用asorti(old,new)

####打印
print是支持上述的那些内置命令的，但是printf不支持，因为printf可以自定义格式输出，诸如\t \n \b 等和c差不多，但是到了具体的数据类型的时候就有所不同了。

%g 如果使用了g，那么在使用%.4g那将只输出四个字符，这与%s不同的是，如果我们使用%6s即使我们的string内容超过了6个那依然会将我们的string输出。而不是像%g一样只输出指定的数目个。但是使用%.6s之后我们使用的我们指定的数目输出了。如果使用%05s会在前面不足的地方补上0. 当然%g需要在使用OFMT的时候才是这样

%f %c %d %e %x %o 这些都是很c语言中意思相同的。基础的用法也是差不多的。

当我们使用absolute输出的时候可以是哟呢substr这个函数来指定，substr(string,start,end)指定了长度打印，更加灵活了。

上面说的.操作，也是一种限制的操作，我们使用%.4f那么效果就是f会在小数点后面保留四位，这一点和c语言还是很相近的。


我们可以在BEGIN的结尾处使用>>来进行重定向，但是我们可以在执行的时候使用>看具体的情况来实现。

###内嵌函数

* int() 取整 去尾的方法取整
* log() 对于-1显示的nan
* sqrt() 开方
* exp()  ln函数
* sin() cos() atan() 

* rand()  随机数的，但是只是返回的在0-1之间的数，需要自己去扩展然。
* srand() 设置种子,这个和c语言很像
* index() 测试某个数组元素的位置，没有这个值就返回0
* length() 测试的是一个string的长度，使用的是character的长度。
* split()  split(input,array,separator) 将input分割成一块一块。然后保存在array中。
* substr() 获取指定长度的string，上面提到过。

GAWK支持

* sub(original-string,replace-stirng,input) origianl-string 指的是在input中可能出现的，一般使用RE来做匹配，replace就是用来指定匹配到后，用来替换的。做后的结果是保存到了input中，sub的返回是0或1

* gsub() 用法和sub一样，但是用来替换所有符合条件的。

* match(string,searchstring). 用来验证是否在string中包含searchstring。 一般给出两个变量RSTART RLENGTH.这两个代表的是searchstring在string的起始位置和长度，此时使用substr刚好将其输出。

* tolower() toupper() 这两个很简明的，将字母变换大小。

* ARGC ARGV这两个变量和c语言中的一样，都是表示命令行参数，以及调用的。 不同的是还有一个是ARGIND,我们使用ARGV[ARGIND]就是指代的文件的文件名。回想FINENAME

* OFMT这个指定了打印时候的使用指定的格式，如OFMT="%.4g"那么接下来的打印都是按照这个输出的。

* 环境变量ENVIRON环境变量数组，可以输出的一些环境变量。
* IGNORECASE 这是表示忽略大小写，=1则为打开忽略，=0则为关闭忽略。用在BEGIN中
* ERRNO  打印错误信息

#####pgwak
使用pgwak会有一个.out的输出文件。在这个文件中我们可以看到的是某些行的左边和右边都有数字，左边的表示这行excute了多少次，右边的表示success了多少次

如果想指定.out pgawk --profile=myprofiler.out -f xxxxx xxxx

###bit option

* and(xx,xx)
* or (xx,xx)
* xor(xx,xx) 异或
* compl 取反 
* lshift(xx,xx)
* rshift(xx,xx)

这些只有gawk支持，原生的awk不支持

###function
	function functionname()
	{
		xxxxx
	}

我们可以做一个debug的函数，用于调试。

###international

在一个大的项目中，多语言输出的话，需要一个能够翻印的东西，就是将中文的软件翻译成英文的，以及其他的，我们不可能一个一个的改，这时就要用到现在的这个。一共四步。简单而又方便

* step 1
在BEGIN中包含TEXTDOMAIN=“XXX” bindtextdomain("directory") .然后在每个print打印的string前面加上"_" 表示这个是可以被替换的。

*step2
使用gawk --gen-po -f xxx xxx > xxx.po 创建.po文件，在这个.po文件中msgstr这是你可修改的，改成你想要变成的语言。

*step3
创建一个message，使用msgfmt -v xxx.po 会生成一个message的文件。然后在你bindtextdomain所指定的文件夹下创建如下如下的文件夹
mkdir -p EN_US/LC_MESSAGES 然后将刚才的message移动到刚才的创建的文件夹中，名字必须是你TEXTDOMAIN所指定的后缀是.mo

*setp4
执行gwak -f xxx xxx 接着查看一些效果，应该是更改完成了。


###多进程操作
使用|& 使用的步骤一般也是那几个
* 我们可以指定一个命令 command=“xxxx” 
* 接着我们使用 awk command|& command 让这个命令执行。
* 执行起来后我们关闭to的这一端，使用close(command，“to”)
* 我们使使用getline来读取将执行的结果保存到tmp这一个变量中
* 最后关闭这个command

我们同样可以使用system函数来执行多进程的。

介绍几个函数 systime() 返回的是秒数，我们可以使用strftime来格式化下我们的秒，一般是strftime("%c",systime()) ,%c输出完整的日期。%F 是2014-08-01这样的。


getline函数

单独使用如awk -F, '{getline; print$0;}' xxx 只会打印偶数行。因为getline是读取下一行，会覆盖掉awk读的那一行。如果使用变量保存就不会出现这样了，如awk -F, '{print $0; getline tmp; print $tmp}' 就会完整的输出了。

可以使用getline的多文件穿插打印，如awk -F, '{print $0; getline < file2;print $0}' file1 这样就会将file2的内容和file1的内容穿插着输出的。

awk也就是这些了。还有很多的技巧，慢慢补充。
