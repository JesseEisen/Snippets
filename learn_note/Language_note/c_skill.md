C_skill
====


###array

我们如果有一个数组"arr[10]",我们可以用如下的方法给它赋值。

	arr[10]={0};  //we assign 0 to every array memeber

上面的效果就是arr[0] ... arr[9] = 0;   

如果我们使用下面的赋值方法
	
	arr[10]={1,1}; 

上面的效果就是arr[0]=arr[1]=1, arr[2] ... arr[9]=0;

如果我们使用下面的赋值方法的话

	arr[10]={[3]=1};

上面的效果就是arr[3]=1, 其他的都等于0

同样我们还可以使用如下的方法赋值

	arr[10]={[2 ... 6]=1,[7 ... 9]=2 };

上面的效果就是arr[0]= arr[1] =0, arr[2] ... arr[6] = 1, arr[7] ...arr[9]=2;

但是如果我们使用`arr[10]={1}`，这个的效果就是将arr[0]赋值为1，其他依然是0.


###数组名和下标
有下面的代码snippet

	int main(int argc, char *argv[])
	{
		char arr[]="abcdef";
		printf("%c",2[arr]);
		return 0;
	}

我们编译不会出错，也可运行成功。原因在于我们的数组arr[b]被看作是*(arr+b),因此使用2[arr],同样的被扩展为*(2+arr)。
这样的写法比较不直观，但是原理还是一样的。

###数组的强制转换
	
	int main(int argc, char *argv[])
	{
		printf("%d\n",((int[]){1,2,3,4})[2]);
		return 0;
	}

编译运行后的结果是我们的3，我们将强制转换出一个数组出来。输出了数组的第三个数。

###结构体对齐

我们知道在结构体中，结构体的大小随着我们的定义会有着不同的大小。看如下的snippets

	struct foo
	{
		char c1;
		int  a;
		char c2;
	};

	struct bar
	{
		int  a;
		char c1;
		char c2;
	};

我们对上述的两个元素基本相同的两个结构体进行sizeof操作，会发现foo的大小是12， 而bar的大小是8.  
原因是内存的对齐，对于foo而言，c1被扩展为4位的，而a原本就是4位的，c2被扩展成4位存储。  
而对于bar而言，a原本是4位，但是c1和c2两个内存连在一块然后扩展成4位，后面如果还有c3，c4大小还是8位。

###函数的参数

	void foo(){}
	void foo1(void){}

	int main(int argc, char *argv[])
	{
		foo(1);
		foo1(1;)
	}

在这个代码中，我们会发现第二个函数编译的时候报错。因为void的定义，表明函数不可接受任何的参数，而不指定表明参数的类型未知

###main(x)
	
	int main(x)
	{
		printf("%d\n",x);
		return 0;
	}

x代表的是接收到参数的个数。相当于argc。


###编译时输入c代码

	#include "/dev/tty"

我们将上述的内容保存到一个c文件中，只有这一行，那么我们执行编译的时候，就是需要我们自己输入内容。   
同样可以使用的是/dev/stdin

###printf中使用*

	float b=1.234556;
	printf("%.*f\n",4,b);

我们打印出来的就是1.2345,使用*来动态控制%f的输出。

###从文件中加载数组

	arr.txt

	{1,2,3},
	{4,5,6}

	arr.c

	int main(int argc, char *argv[])
	{
		int arr[][3]={
			#include "arr.txt";
			}
		printf("%d\n",arr[1][2]);
		return 0;
	}

执行后输出6，我们引用了文件中的arr定义。

###warning宏

在编写我们的代码的时候可以在代码中加入 #warning: xxxxx 在编译的时候会跳出这个warning的提示   
同样使#error也是会有相同的效果。这在代码调试的时候有些用处。



