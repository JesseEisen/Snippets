ssmtp
===

we can use ssmtp to send a mail in terminal. here is some tips below.


first we need to install ssmtp, just `sudo apt-get install ssmtp` and then we just need to configure our ssmtp.conf file
we use this order`gksu gedit /ect/ssmtp/ssmtp.conf`.you need to notice that if the gksu you never install please use 
`sudo apt-get install gksu`

here is the config file context: 

	
	# Config file for sSMTP sendmail
	#
	# The person who gets all mail for userids < 1000
	# Make this empty to disable rewriting.
		root=lkchan0719@gmail.com

	# The place where the mail goes. The actual machine name is required no 
	# MX records are consulted. Commonly mailhosts are named mail.domain.com
		mailhub=smtp.gmail.com:587

	# Where will the mail seem to come from?
	#rewriteDomain=

	# The full hostname
		hostname=JesseChen

		UseSTARTTLS=YES
		AuthUser=lkchan0719@gmail.com
		AuthPass=clk123456,

	# Are users allowed to set their own From: address?
	# YES - Allow the user to specify their own From: address
	# NO - Use the system generated From: address
		FromLineOverride=YES

	
if you complete this configure, please save and quit.


after we config all of this we can use ssmtp to send a mail.

###Example

	ssmtp to@domian.com
	From:me@gmail.com
	To:to@domian.com
	Subject: some context

	here is the main context.you can edit with youself.


if you want to send an accessory, you may need to install a tool named "uuencode"  we use `sudo apt-get install sharutils`

And we can use this order "uuencode accessory.extension accessory | ssmtp username@domain.com"



