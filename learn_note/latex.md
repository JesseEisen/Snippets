latex
====


* 安装letex，使用sudo apt-get install texlive 比较大，需要一会儿时间

* 安转中文字体的支持， sudo apt-get install ttf-arphic-uming 但是需要添加一个源

* 添加源 
	sudo gedit /etc/apt/sources.list
	deb http://us.archive.ubuntu.com/ubuntu saucy main universe
	sudo apt-get update
* 安装其他支持
	sudo apt-get install texlive-latex-extra  同样很大，需要一段时间

使用的编译命令是 xelatex  xxx.tex

查看pdf的命令是evince xxx.pdf	



