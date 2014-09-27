今天安装了两个不错的工具，一个叫gimp，一个叫imagemagick。 

##gimp

安装： sudo apt-get install gimp

这是一个界面的工具，用来对图片进行裁减和处理的一个工具。有种photoshop的感觉。但是比photoshop的量级要小很多。这个工具的使用参看peter
的视频。

变色，colors->Desaturate很简单的


##imagemagick

安装： sudo apt-get install graphicsmagick-libmagick-dev-compat libmagickwand-dev imagemagick  graphicsmagick-imagemagick-compat

包比较多，所以安转比较费时，但是命令行的操作还是比较喜欢的。速度快

变色： convert origin.png -quantize GRAY -colors 256 dest.jpg

使用eog dest.jpg 查看图片 envice 用来查看pdf文档
