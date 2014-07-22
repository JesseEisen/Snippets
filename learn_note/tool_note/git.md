git
====

when we execute `git push -u origin master`, we need to input our username and password, this is very unconvinent. How can we configure git and make it auto verfiy. 


we only create a file named ".netrc", in this file we just input some thing below

	machine github.com
	login  JesseEisen  #this is my username
	password yourpasswd #this is my password 

so after we saved and quit. we exectue `git push -u orgin master` we can see that we never need to input out username and passwd. 


