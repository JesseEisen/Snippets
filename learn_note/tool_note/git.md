##Base


我们在提交的时候，如果觉得有些文件不想添加到我们的git仓库中，我们可以使用.gitignore 的文件进行过滤

* *.txt  过滤掉.txt结尾的文件
* /TODO  过滤掉文件夹的内容，只是存在于根目录下的
* build/ 过滤掉build目录下的所有文件
* doc/*.txt 注意只是一级目录下的，不会过滤掉doc/file/里面的.txt
* doc/**/*.txt  过滤掉doc下所有的文件

对于git有三个地方，第一个是本地的工作区，就是我们在写东西的地方，还有一个叫暂存区，就是我们执行了add之后。还有一个就是最终的一个执行了commit后的一个HEAD区。

我们通过执行
* git diff  是比较的我们工作区和暂存区的不同，
* git diff --cached 或是--staged 是暂存区和HEAD的比较
* git diff HEAD 是将工作区与HEAD 进行比较

我们同样可以通过执行git status 来简单的查看一下所做的改动,但是status的针对不是太明确的，只要着三个地方的有任何一处被修改了，那么就会有输出。


提交commit 
我们之前操作过add后，只是在暂存区里面保存着，并没有真正的保存好。所以我们还需要执行一步提交操作。

在执行提交的时候，我们需要加上-m 来表明这次提交的改动或是目的。如果我们使用了-a参数，那么我们就可以省略一步git add 的操作。使用-v操作就是将这次的提交详细内容显示在vi编辑器中。

大部分情况是我们取个别名。使用git config --global alias.ci "commit -a -v"这个是写入到了本地的~/.gitconfig 所以下次直接执行git ci就算是做了一个版本。

##删除文件
我们在git中删除文件有两种概念，第一个就是我们在我们本地删除文件。第二种就是我们在暂存区删除文件，或是提交后的仓库中删除数据

####本地删除数据
* 如果本地的数据已经做过一次提交，那么我们本地执行rm xxx 这个操作的效果是只是将本地的文件删除了，但是仓库中的内容还在，我们同样可以恢复，这也就是版本控制的好处所在

* 如果我们想要删除仓库中的东西，这个删除的结果就是这个东西永远的小时了，你是难以找回来的。所以这个操作需要格外的小心

具体的操作过程及效果

* 首先是在本地删除 rm xxx 效果就是本地的文件不见了
* 如果我们此时对我们的文件做了一次提交。git add test.c 现在我们对test.c执行了add。但是我们发现这个文件没有必要被提交到仓库中，只是一个测试文件。那么我们如何收回呢，让这个test.c 不会在commit的时候被提交上去呢?使用git rm --cached test.c 这样就将test.c 从当前的add中被删除了。效果就是本地的文件还在，commit的时候不会被加入HEAD中。 

还有一种情况是如果加入暂存区的文件，还没有commit但是本地又已经更更改了。那么就要使用git rm -f xxx 来删除这个文件。

* 如果我们直接执行的是git ci 也就意味着我们的test.c 已经在HEAD中了。我们可以使用git ls-files 查看会发现test.c 已经在里面了，那么我们如何删除呢？ 直接执行git rm test.c 这样就会删HEAD中的test.c了，效果就是本地的test.c 和HEAD中的test.c都被删除了。

####快速的删除
我们有时候只需要在本地将要删除的文件删除掉，然后使用git add -u就可以将所做的修改同步到HEAD中，无需使用git rm 写一长串的内容。

####删除的文件恢复
我们能够删除文件，有时候我们删除了HEAD中的文件。但是我们也许又后悔或是删错了。如何拯救呢？ 

* 第一个方法简单而粗暴，将我们这次的提交给throw掉。现在我们是这样的一种状态。我们将test.c执行过一次提交后，但是此时我们执行了git rm 但是我们发现操作错了。如何把这个test.c给找回来呢？ 那就是将此刻的先做一个提交。此时的提交是删除文件的操作。

现在我们静下来思考下，此时的状态是什么。我们之前的add test.c已经成了之前的版本了。现在的版本是没有test.c 的版本。好我们执行git reset --hard HEAD^ 意思就是重置当前的版本为之前一个。这样我们当前的提交没有了。回到了之前的版本了。随之而来的也就是test.c 也出现了。但是这个操作不好的就是那些我们不想要的也回来了。我们需要一个针对性比较好的。

* 第二种方法就是的。直接恢复某一个具体的文件。还是刚才的那个状态，有test.c的那是之前的一个版本。那么我们只要执行 git cat-file HEAD~1:test.c > test.c
或git checkout HEAD~1 -- test.c  效果就是只恢复test.c 文件，而这个恢复的文件已经处于添加状态了。


对于删除我们可使用glob模式的，但是要注意转义的操作。\*～ 如这样的，匹配到了所有以～结尾的缓存文件。


####文件的移动
git mv 

git会很聪明的分辨这是重命名还是其他的操作。比如使用git mv test.c Test.c 
你在做版本提交的时候，回提示是rename 

git mv是三个操作 ，mv xxx1 xxx2 , git rm xxx1 ,git add xxx2 

如果想测试下git有多聪明，我们可以使用分步的操作，将更改后的文件更改一下。再做提交的时候，会发现有一个相似度的显示。但是同样是显示的rename 还是很很聪明的。

####查看提交历史
可以使用git的工具tig

git log 是查看总共提交了多少次。提交人，时间以及哈希值等
git log -p -2 -p是用来查看具体的提交差异。-2是表示显示最近的两次。
git log --stat 能够显示每次改动的行数，其他的没有什么输出
git log --pretty=oneline 只显示提交时的信息，这个使用tig最直接了。
git log -pretty=format:"%h - %an, %ar:%s"  可以自定义一些log的输出。
在使用-pretty=oneline 或是format的时候 可以配合使用--graph 能够形象的输出很并提交等操作。

git log 还提供一些操作来显示具体某个时间之前的提交，某个时间之后的提交，指定的作者，指定的提交着 我们可以使用 --since --until --author --committer 后面用上=接上一些具体的值。如果--since="2014-7-28" 就可以实现筛选

##撤销操作
当我们在提交结束后，发现我们还有一个文件没有提交，但是又不想再做一个单独的版本，我们只要使用 git commit --amend 就可以将此次将遗漏的那个文件加到刚才的那个版本里面去。

git reset HEAD XXXX 使用这个操作，可以将add操作中的文件给取消暂存。此时取消的暂存的文件，我们可以使用git status -s 看到前面的M是在第二列，表明这个是和暂存区中的文件不一样，如果出现在第一列表明和版本库中的不一样。

git checkout -- test.c 会将你现在所修改的内容给抹去，回到你没有提交的版本，这个命令慎用。

##远程仓库
git remote 显示远程的仓库 如果使用git remote -v会看更加详细的仓库的内容

添加远程库
git remote add origin ..... 这是在github上初始的时候所要做的。
git remote add xxx1 xxx2 其中xxx1是指代了对应的仓库的地址。 
如果要抓取对应的库的内容 使用git fetch xxx1 


git pull不同于git fetch 前者的效果是将远程的库直接拉取过来，然后合并到本地的仓库分支中，后者需要手动的合并这些。

git push [remote-name] [branch-name] 这是基础的命令语法
我们在克隆某个仓库的时候，可以使用git remote show origin 查看远程库的详细信息

git remote rename xxx1 xxx2 可以用来更改远程的仓库的名字。
git remote rm xxx1 删除远端的仓库，这样我们就没法进行提交了，以及其他的一些相关操作。


###分支

我们有时候在开发的时候，已经发布了一个稳定的版本了，但是想继续添加一个新的功能，此时我们可以开辟一个新的分支。在这个分支上所做的一些修改对原来的分支没有任何的影响，当我们的开发完成后，可以将这个分支合并过去。


创建分支 git branch xxx  
切换到该分支 git checkout xxx 
也可以直接一步将上面的两个操作一并完成 git checkout -b xxx 

当我们在新建的分支上开发的时候，突然master分支上要要打一个补丁了。那么我们切回master分支，git checkout master 

接着补丁打完了，推送过去了后接着继续做新功能的开发。 最后完成了，那么我们就开始很并了，但是有时后会出现一个问题就是我们在合并的时候会有一个冲突，当我们在两个分支下修改了同一个文件的时候，需要我们手动的去选择保留还是放弃，最后执行下add操作，然后提交。分支就算是合并好了。
