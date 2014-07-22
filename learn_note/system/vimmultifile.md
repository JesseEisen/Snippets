multilfile
====

we can use vi open some files at once,and we need to switch.
* use `:n` to next file `:N` to perivous file
* use `ls` to show buffers and use `:1` the number to switch
* use `:tabnew filename`to create tab in vi, and use `:tabnext`to next file,`:tabpervious`to perivous file.

all of this is useful for us to do this, but sometimes it maybe not convient. so we can add some in .vimrc

	set hidden
	map <s-tab> :bp <cr>
	map <tab> :bn <cr>

after this configure.we can use `tab` to switch file. 
if we want to see which file is under editing now ,we still add below to .vimrc
	set laststatus=2
	set statusline=%F:\%1

so we can see which file is under editing now.

###vim server
Notice:need your vim have clientsever

use `vim -h |grep servername` is have context that show you can use it

####way to use servername
`vi --servername VIM-SERVR filename ` this means crate a server
`vi --servername VIM-SERVR --remote-slient filename` connect to this server

 
