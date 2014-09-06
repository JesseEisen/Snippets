windows下记事本文件是使用的GBK的编码，而在gedit中优先是使用的utf-8编码，但是如何修改呢?

sudo apt-get install gconf-editor
我们使用gconf-editor来修改，大众的修改是  左边树 /apps/gedit-2/preferences/encodings  添加value为 GB18030 将其放到第一位

如果gconf-editor中没有找到gedit， 可以使用ctrl + f 来搜索。  可以使用sudo apt-get install dconf-geditor 
->org->gnome->gedit->preferences->encodings
添加 auto-detected 的value 如上


如果想要截图显示阴影可以使用 

这招能让你用Alt+PrintScreen键截图后，让图片有各种效果。定位到“/apps/gnome-screenshot”，在右 侧，boder_effect的值改一下，默认是none，改成“shadow”就是有阴影效果了，black-line的话，截图周围就有黑线了

ubuntu 13.10 alt-prtscreen 失效的解决办法, dconf-editor  找到ORG>Integrated>Show HUD.['']. Changed ” to ‘Disabled’  



