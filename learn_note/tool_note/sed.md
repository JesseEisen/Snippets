sed
====


###Base

sed的基础语法是sed [option] {command} {filename}

####option 
常用的option有四个，分别是下面的。  
* -n 抑制自动打印pattern space中的内容，意思就是如果不加-n 那么会同一行输出两次。这点很重要。是pattern space的内容。

* -e 使用这个option可以执行多个命令，如果使用；分割开也是可以的。一般多是用-e

* -f 使用这个选项目的是将sed命令写到同一个脚本中，然后一起执行。使用-f就是和makefile一样，可以指定具体的执行的文件。

* -i 一般sed的执行不会更改原来的文件，所有如果我们想将我们执行sed后的效果更改到源文件，可以使用这个参数。一般建议使用-ibak,这样会将原来的文件做一个备份，这是在执行这类无法撤销的命令的通常做法。需要谨慎。

大体上的option就是这四个了。sed的重点不是在option上，因为sed 的cammand更加让人觉得高效。

####cammand
cammand很多，细数下来真的不少，但是我们使用sed大多数情况是用来做替换，做一些检索的。但是一些细小的命令有时候却是很关键。

1. 首先是p命令，p是print的意思。就是将文件的内容输出来，我们可以加上一些行控制，以及一些符号。例如

	sed 'p' filename  这将将原文原样输出两遍。
	sed '1p' filename 这将将第一行原样输出两遍。其他的原样输出
	sed -n '1p' filename 这将只输出第一行，其他的不输出。
	sed -n '2,$p' filename 输出第二行到最后一行。
	sed -n '2,+2p' filename 输出第二行以及之后的两行。
	sed -n '1~2p' filename ～是一个递增的输出1～2 就是输出1，3，5...
	sed -n '1,4p' filename ,是输出1到4行，-n抑制输出，不然使用p的效果不佳
	sed -n '/pattern/ p' filename 匹配到的行输出。

2. d命令，d是delete的意思。就是删除的意思，d使用方法和p的方法是差不多的。

3. w命令，w意思是write， 这个命令使用的不是太多。因为我们可以使用redirection来实现这个。

	sed 'w output' filename 将filename中的内容写到output中，
	sed '1,4 w output' filename 将filename的1到4行写入output中
	sed -n '/pattern/ w output' filename 将filename的匹配到pattern的那行写到output中，不在屏幕上显示。

4.s命令， s命令是substitute的意思，替换。这个是sed中使用的比较多的一个命令
sed的有很多的flag，正是有这些flag，s命令变得很强大。s命令支持re。但是是BRE，所以对于{} 需要转义，() 同样需要转义。 BRE支持的是. [ ] ^ $ 这五个通配符。

先说说flag

	* g ，g是global的意思，就是全局替换。这个和vim中的%s那个是一样的。具体的语法是 sed -n 's/parttern1/parttern2/g' filename 这样就将pattern1换成pattern2了，而且是所有的都换成了pattern2了。
	* number flag ，所谓的number flag就是指我们可以指定替换的pattern，这么说吧，我们不想替换全局的pattern1只想替换每一行的第一个或是第二个匹配的内容。我们就可以使用sed -n 's/pattern1/pattern2/2' filename 这就是将每行的第二个匹配到的内容替换掉，如果没有第二个匹配项的，这样行就跳过。不做任何处理
	* p 小写的p,这个flag的目的是用来打印我们的所匹配的。sed -n 's/p1/p2/p' filename. 这个操作标志很简单
	* w 这个标志其实可以类比w command。只是在s的基础上加以写入的，这样省去使用w命令了。
	* i 这是在GNU的标准下才有的，这个是忽略大小写的，看一例子。 sed -n 's/john/johnny/i' filename. 如果在filename中存在的是John，那么通样会执行替换。
	* e 这个也是在GNU上独有的一个命令，是表示执行的一个命令。所谓的执行，指的是匹配出来的那一行，如果是一个命令的话我们就可以执行，例如sed 's/^/ls -l/e' filename 我们将行首加上ls -l使其成为一个命令，然后执行这一行的命令，一般情况下只是单纯的将这个行首加上ls -l 不会有任何的执行

flag基本就是上述这些，我们可以组合这些flag，例如使用sed -n 's/p1/p2/gipw output' filename 这样的使用同样是支持的的一个用法。

接着说说s命令使用正则表达式的的一些例子。

s命令支持BRE，这是一个需要注意的点。接着说说比较好的一些点
	* &  这个是代替任何匹配，不论是原始的字符串还是从正则表达式匹配到的，都可以代替如 sed -n 's/^.*/<&>/' filename. 这就是代表匹配一整行，然后在这一行开始和结尾加上<>,& 是一个代替的作用。
	* \1 \2... 我们有时候如果使用了() 包裹我们所匹配的内容的话，这就将成为一个组。group，我们可以使用\1来表示我们匹配到的一个组，具体的使用是sed -n 's/\([^,]*\).*/\1/g' filename 意思就是在第一个逗号前面的内容作为我们的组，我们使用\1表示他，我们用这个来代替所匹配到的内容。
	* 分割符，在sed中使用的/叫做分割符，但是我们会发现有时候在做匹配的时候呢，同样会出现/，如匹配linux下面的目录的时候，那样显得很难读取，所以sed支持的其他分割符@ ! ^ | ，只要成对的使用就好了。

	* GNU 特有的一种代替字符串的标志。\l 将后面紧跟的那个字符变成小写的。\L将它后面的字符都变成小写的。\u 将紧跟在他后面的变成大写的，\U和\L是相反的。 而\E就会结束掉\U 或是\L的效果。，一般都是这样使用的"\Upattern\E anothercontext" 

s差不多就是这些了。实际上s的使用真的是太灵活了。需要在实际中慢慢体会了。

5. a命令，a就是append 添加，注意这边的添加是添加在指定行或是具体匹配行的后面，如 sed -n '1 a here is what you add' filename  这就是我们在第一行的后面添加上一句话，就是a后面的那句 sed -n '/partern/ a here is what you add' filename 就是在又pattern的那行的下一行添加

6. i命令 i就是insert 插入，这边的插入是在匹配到的行前面进行插入。这个和a有点相反，但是用法确实一样的。

7. c命令 c就是change 更改，我们上面说过d命令，是将那一行删除掉，而现在是将那一行删除，并修改为我们想要他变成的那一行，和上面的i a是差不多的，但是这次匹配到是那行，就修改那一行，没有前后的分别。

8. l命令 l可以打印出一些隐含的字符，就如同cat -A 一样，打印出所有的字符，包括\t $等之类的。 l还有一个功能就是在l后面加上数字，表示输出的时候本行有几个字符。举两个例子： sed -n l filename 这是第一个 sed -n 'l 20' filename 一行输出20个字符.

9. =命令 显示行号，行号和内容是分开的。如果使用了-n那么只会显示行号了。还有一点就是可以输出具体某一行的行号，可以使用/../做匹配。有一点比较重要，就是我们想把行号和内容在同一行显示的话，可以使用N命令来实现，后面介绍

10. y 用来转换的，我们可以类比他为tr的用法。sed -n 'y/abc/ABC/' filename .他会让文件中所有的abc变成ABC转换而已

11. q quit退出命令。在执行到某个点的时候退出，如sed '5 q' filename 读到第五行的时候停止。sed退出。又如sed '/Manager/ q' filename 读到又Manager的时候退出。

12. r read命令， 就是将r后内容插入到某一行的后面，我们可以指定行号，可以指定具体匹配到某一行。然后执行插入文本的操作，这个可以类比vi中的将文件导入。

###some hard

*  n 也许会合-n所联系到一起，对-n是抑制pattern space输出，而n是将pattern space输出。所以使用sed -n n filename就会看到啥也没有。n的细节是
打印当前的pattern space，然后clear掉，接着从文件中读取下一行。接着操作。

上面提到一些pattern space 和hold space，这边具体的说下
> pattern space：是sed的一个缓冲区，sed执行的时候放置以及修改的地方。所得到的行是从输入文件中读取的。
> hold space:是sed用来放临时数据的。sed 允许将数据从hold space 到pattern space之间相互移动，但是不可在hold space中执行任何的sed操作。而pattern space会在每次循环后被删除，而hold space 不会，他会一直保存着。

有了上述的这个概念后，接下来的一些命令就好懂了。

* H 将Pattern space 中的内容追加到hold space中。举个例子就是此时pattern space是line1，而hold space中是line2,那么执行H，在hold中就是line2\nline1 很好理解吧

* h 将pattern space中的内容复制到hold space中，还是上面那个例子，执行了h后，pattern中是line1，hold中也是line1， 原来的line2被覆盖了。

* x 将pattern space和hold space互换。还是原来的例子，执行了x后，pattern中是line2，hold中是line1，但是x需要配合其他的命令，如n一般是{x;n}

* g 将hold space的内容复制到pattern space中。还是原来的例子，执行g后就变成pattern中是line2，hold中依然是line2.

* G 将hold space的内容追加到pattern space中。接着那个例子，执行G后就变成了pattern中line1\nline2，hold中是line2

* N 将新的一行加到pattern space中。这个效果就是将偶数行加到奇数行的后面。举个例子就是sed '{N;s/\n/:/g}' filename 这样就会发现第二行的内容接到了第一行的后面，而且两行直接是用：隔开的。

* P 将前面的一行输出，当遇到了\n的时候就执行之前的那个操作。一般和N一起使用会只打印出第一行。

* D 当遇到\n的时候，将那一行删除。当删除后，D会放弃D后面的一些sed命令，从头开始继续执行。所以这边形成了一个小的循环。

* b 分支于标签，当执行b的时候，满足条件就会跳转到标签处，执行那边的命令，这样可以跳过一些操作，具体的实现是
	sed '/Manager/! b  end \
	     s/^/*/ \
		 :end \
		 p'
可以看到end是一个标签,当那一行没有/Manager/的时候就跳到:end处，如果包含的就执行下一行的s/^/*/命令。


上述就是sed的大体内容，算是比较全面的了。还有一些sed 的表现形式，我们可以多用脚本来实现就行了。
	
