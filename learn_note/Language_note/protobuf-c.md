protobuf-c 
===


 &emsp;protobuf是一个将结构化的数据序列化(serializing structured data). 我们可以用在通信协议上面，一方面将我们要发的消息打包(pack)分发出去，一方面我们可以将相同格式的包解包(unpacked).获取其中的消息。有这样一个工具让我们觉得很方便.
 
 &emsp;官方的protobuf支持三种语言，C++，python，Java， 唯独却一个C语言版本的，但是第三方给出一个比较不错的protobuf-c，基本的原理是一样的，但是在编译上有所不同，调用就按照一般的c语法进行。   
 &emsp;[protobuf-c](https://code.google.com/p/protobuf-c/wiki/Main_Page)在官方网站上比较难找，这里面提供了一些example和lib。对于想看基本语法的可以点[这里](https://developers.google.com/protocol-buffers/docs/overview)。下面是我自己的一些精简整理。
 
 基础语法
 ---
 1.三个字段的定义
 * required   定义后就必须赋值，不然会报错
 * optional   定义后可以给其赋值或是不赋值
 * repeated   定义后我们可以给其一个大小，因为使用的时候，这个是一个大小为size的数组
 
2. 写一个`.proto` 文件   
要使用protobuf，就必须先写一个`.proto`类型的文件。因为通过这个文件，我们编译后就会自动生成我们编程所需的`.c`,`.h`文件。   

**一个实例**
```proto
    message amessage
    {
        required  int32 a=1;
        optional  int32 b=2;
    }
```
 这是一个很简单的一个实例，定义了两个字段(field),一个是`required`类型，一个是`optional`类型。 后面的编号赋值是字段的编号。对于编号还想简单的说一下[TODO]
 
 
 **编译**  
 我们将写好的`.proto`文件编译，得到我们所需的文件。不过在这之前，我们需要搭建一个小环境，protobuf-c的是依赖在protobuf2.3.0版本上的，最新的版本，不太支持protobuf-c。   
1.安装protobuf步骤：
```
wget http://protobuf.googlecode.com/files/protobuf-2.3.0.tar.gz   //下载protobuf的tar包
tar zxvf protobuf-2.3.0.tar.gz    //解压
cd protobuf-2.4.1
./configure --prefix=/usr/
make
sudo make install
/sbin/ldconfig -v    //设置共享库的位置
```
最后一步比较重要，这一步不操作，一般就会出现安装protobuf-c共享库的报错
2.安装protobuf-c
```
wget http://protobuf-c.googlecode.com/files/protobuf-c-0.15.tar.gz
tar zxvf protobuf-c-0.15.tar.gz
cd protobuf-c-0.15
./configure --prefix=/usr/
make
sudo make install
```
按照上述的步骤安装好protobuf-c。耗时大约十分钟左右吧，需要耐心一点。  
3.测试是否成功
```
cd ..
protoc-c --c_out=./ protobuf-c-0.15/src/test/test.proto
```
如果编译没有问题，那么就表示安装成功， 如果想看结果，就到protobuf-c-0.15/src/test/test.proto里面查看文件test.pb-c.h/.c

----
上面的工作已经做好的，那就进行这一步，编译刚才`.proto`文件  
**编译命令** `protoc-c --c_out=. filename.proto`  
**解释说明**这是编译的.proto文件，用的protoc-c  ，等号右边的点，代表的是当前目录，你也可以像测试一样，使用`./`来指定一个路径，路径包含的是这个`.proto`文件的具体位置。

---

**使用protobuf编码**  
编译成功后会得到两个文件，`.h .c`，我们在编码的时候需要参考的是`.h`文件。这里面一般是一些函数和变量的定义。接着上面的那个例子，我们编译成功后，`.h`里面有一个`Amessage`的结构体。

    struct _Amessage
    {
        PortobufCMessage base;
        int32_t a;
        ptotobuf_C_boolen has_b;
        int32_t b;
    }
我们可以发现，定义为`required`的变量a没有`has_a`。定义为`optional`的变量b，上面有一个bool型的`has_b`,我们通过这个值的赋值来指定b是否存在。这就是`optional`变量的不同之处，但是只是在这种情况下，其他的情况，`has_b`不一定是存在的。看具体的`.h`文件的定义。

1.编写serialized_message.c  
在这个文件里面我们去编写一个将消息打包起来的函数，从命令行(CLI)读入数据，将数据写到标准输出上(stdout)。 
```
    Amessage msg = AMESSAGE__INIT; //define a amessage struct
    void *buf;     //buf to store the serialized data
    unsigned len;
```
我们一般只需要定义这么多的变量，接下来要做的就是将消息填进去，我们将消息保存在buf中，所以需要对buf分配内存空间，分配多大？我们通过`.h`里面的函数来实现
```
    len = amessage__get_packed_size(&msg);
    buf = malloc(len);
```
我们采用的是从命令行获取的参数，那么参数应该是保存在argv[]这个数组中，但是都是char*类型的。所以我们需要进行转换，`atoi`函数，对于这个函数我曾经写过一篇详细的[介绍](http://www.cnblogs.com/JesseEisen/p/3456537.html)。
```
    msg.a = atoi(argv[1]);
    if(argc == 3)
    {    
        msg.has_b = 1;
        msg.b = argv[2];
    }
```
这就将我们需要发送的值放入到了msg这个结构体中，我们需要将这个结构体pack起来。
```
 amessage__pack(&msg,buf);
```
现在消息就存放在buf中了，我们将消息写到标准输出中。可以想象成将这个包给发送出去了。
```
 fwrite(buf,len ,1, stdout);
```
利用的是标准的读写流函数，我们接下来做一些**清理工作**，因为我们对buf进行了malloc操作，需要释放掉在他在堆中的空间，节约内存。

2.编译serialized_message.c  
需要注意的是，我们此时需要加上-lprotobuf-c,需要将`amessage.pb-c.c`包含进来，为什么你应该清楚的，我们`.h`中的函数实现都在`.c`中。我们还要注意一点就是，-lprotobuf-c需要放在最后，具体的原因不太清楚，我的机器的OS是`deepin`。也许是操作系统不一样，你可以试试。
```
    gcc serialized_message.c amessage.pb-c.c -o serialized_message -lprotobuf-c
```
3.测试运行的结果  
我们可以测试下，经过pack后，输出来的是什么？还是不是原始的数据了。
```
    ./serialized_message 1 3 
```
我们会发现，输出的是一些乱码，也就是说，这个消息格式需要解析，终端是无法识别的，这也就表明，这个简单的协议是可以的，下面就是解包的操作，看能否将数据正确的解析出来。

4.编写deserialize_amessage.c  
我们接收这个消息是从标准输入(stdin)来的.所以我们需要一开始就得将数据读取保存到buf(不是上面的那个buf)中。我们这边使用的是fread读取nobj个size的数(nobj,size是fread函数定义中的，都是size_t类型)。
```
static size_t
read_buffer(unsigned max_length, uint8_t *out)  //使用uint8是`.h`中函数的定义中使用的类型
{
    size_t cur_len=0;
    uint8_t nread;
    
    while((nraed = fread(out+cur_len,1,max_length-cur_len, stdin)))
    {
        cur_len += nread;
        if(cur_len >= MAX_MSG_SIZE)
        {
            .... //出错处理
        }
    }
    return cur_len;
}
```
获取到了数据，我们需要对数据进行解包。不过这之前我们需要做一些变量的定义，如下：
```
    Amessage *msg;
    uint8_t buf[MAX_MSG_SIZE];
    size_t msg_len = read_buffer(MAX_MSG_SIZE,buf);
```
接下来调用解包函数
```
 msg = amessage__unpack(NULL,msg_len,buf);
```
刚才的数据已经在msg中了， 我们要做的就是将msg这个结构体的内容打印出来，具体的操作就是最简单的c语言操作了，在打印好了后，现在我们需要对msg进行清理了。
```
    amessage__free_unpacked(msg,NULL);
```
protobuf提供一个清理函数，所以我们直接调用他就好了，要了解具体的实现，那就去看`.c`文件里面的实现。

2.编译deserialize_message.c   
```
    gcc deserialize_message.c amessage.pb-c.c -o deserialized_message -lprotobuf-c
```
3.测试运行   
此时我们需要利用管道机制(piping)将数据传过来，进行一些解析。
```
    ./serialized_message 1 3 | ./deserialize_message 
```
我们可以看到1、3成功的出现在屏幕上，结合上面说的，我们发现刚才没有使用解包函数的时候，显示的乱码，现在将1 3 原样的输出了，说明我们这个解包函数是正确的。也许这么一点没能解释完全protobuf的全部使用，但是通过一个例子，至少能直到一个流程，

----
&emsp;对于最后一个字段`repeated`我们还没有接触，但是接下来的几篇将会涉及到，我们没有涉及到的还有子消息(submessage),已经枚举(enmu),你也可以自己去官网(上面有链接)看这些。也可以自行[google](www.goog.sinaapp.com)(无需翻墙，相对比较稳定),看一些[云风](http://blog.codingnow.com/2011/12/protocol_buffers_for_c.html)大神的提供的一套不错的protobuf-c。
