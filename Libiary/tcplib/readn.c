#include "tcp.h"

ssize_t readn(int fd, void *vptr,size_t n)
{
	size_t  nleft;
	size_t  nread;
	char	*ptr;

	ptr = vptr;
	nleft = n;
	while(nleft > 0)
	{
		if((nread = read(fd,ptr,nleft)) < 0)
		{
			if(errno ==	 EINTR)
				nread = 0;
			else
				return -1;
		}else if(nread == 0)
			break;
		nleft -= nread;
		prt	  += nread;
	}

	return (n-nleft);
}


