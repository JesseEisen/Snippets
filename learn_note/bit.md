bit option
====

##branch 
positive number has the same true form and complement. but the nagetive number complement is the onescomplementcode plus 1. 

so we can see that -5 complement is 11111111 11111111 11111111 11111001. this form is saved in phycial 

##bit move  
####right move
positive number is add 0 at the left, nagitive number is add 1 at the left.


##abs option 

	mask = v << sizeof(int) \* CHAR_BIT - 1
	r = (v + mask) ^ mask

we can write it with macro definition. r is the result, this option is very fast.

##Min and Max

	r = y ^ (y ^ x) & -(x < y)  //min(x,y)
	r = x ^ (y ^ x) & -(x < y)  //max(x,y)

##get sign bit

	sign = -(int)((unsigned int)((int)v) >> sizeof(int) \* CHAR_BIT - 1)

if the v is nagitive then sign equal 1 else sign is 0



	
