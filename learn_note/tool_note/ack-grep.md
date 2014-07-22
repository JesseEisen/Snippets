##ack-grep 

	this is a tool like grep, but it is very userful and easy than grep.

####install
	
	sudo apt-get install ack-grep
	sudo ln -s `which ack-grep` /bin/ack    ---- create a softlink

####use   
	
	ack partten
	ack --filetype partten
	ack --nofiletype partten
	ack -a partten


####vim plugin

	download ack.vim
	cd .vim 
	cd bundle
	mkdir ack-grep
	cd ack-grep
	tar -xvzf ~/Downlaod/ack.tar.gc -C .

####use in vim

	Ack partten
	Ack --filetype patten
	.....

	vim will open fixfox and we can use direction key to choose 



##happygrep

	this is a personal tool, wirten by happypeter.     
	we just need to clone this repo and execute **make** and **sudo make install**   
	this tool is conviente,but it is based on curses.so we need to install ncurses environment.   

	`sudo apt-get install libncursesw5 libncursesw5-dev`  

	this way must be done first.



	


