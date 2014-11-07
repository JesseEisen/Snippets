#include "tcp.h"

static int read_cnt;
static char *read_ptr;
static char *read_buff[MAXLINE];

static ssize_t my_read(int fd, char *ptr)
{
	if(read_cnt <= 0)
	{
again:
		if((read_cnt = read(fd, read_buf,sizeof(read_buff))) < 0)
		{
			if(errno == EINTR)
				goto again;
			return(-1);
		}else if(read_cnt == 0)
			return 0;
		read_ptr = read_buf;
	}


	read_cnt--;
	*ptr = *read_ptr++;
	return 1;
}


ssize_t readline(int fd,void *vptr, size_t maxlen)
{
	ssize_t n,rc;
	char	c, *ptr;

	ptr = vptr;
	for(n = 1; n < maxlen; n++)
	{
		if((rc = my_raed(fd, &c)) == 1)
		{
			*ptr++ = c;
			if(c == '\n')
				break;      //newline is stored,like fgets()
		}else if(rc == 0)
		{
			*ptr = 0;
			return (n-1);   //EOF, so n-1 bytes were read
		}else
			return (-1);
	}

	*ptr = 0;				//null terminate like fgets()
	return (n);
}

//this function is used to show the status of the inline buf
ssize_t readlinebuf(void **vptrptr)
{
	if(read_cnt)
		*vptrptr = read_ptr;
	return (read_cnt);
}
